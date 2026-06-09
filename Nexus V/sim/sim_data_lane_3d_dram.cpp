#include "Vtb_nvisc_data_lane_3d_dram.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vtb_nvisc_data_lane_3d_dram* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static void zero_wide_words(WData* words, int count) {
    for (int i = 0; i < count; ++i) {
        words[i] = 0;
    }
}

static bool expect(bool cond, const char* label) {
    std::cout << "[DATA-3D-DRAM] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_data_lane_3d_dram* top) {
    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    top->req_is_write_i = 0;
    top->req_paddr_i = 0;
    top->req_wdata_i = 0;
    top->req_size_bytes_i = 8;
    zero_wide_words(top->req_id_i, 5);
    top->flush_3d_i = 0;
}

static bool wait_resp(Vtb_nvisc_data_lane_3d_dram* top, int max_cycles = 64) {
    for (int i = 0; i < max_cycles; ++i) {
        if (top->resp_valid_o || top->fault_o) {
            return true;
        }
        tick(top);
    }
    return false;
}

static bool data_store(Vtb_nvisc_data_lane_3d_dram* top, uint64_t addr, uint64_t data) {
    std::cout << "[DATA-3D-DRAM] Case DATA store through L1D -> 3D -> DRAM" << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_write_i = 1;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    top->req_size_bytes_i = 8;
    tick(top);

    bool pass = true;
    bool saw_lower_hierarchy =
        (top->dbg_l1d_miss_o == 1) ||
        (top->dbg_3d_store_o == 1) ||
        (top->dbg_dram_busy_o == 1);

    set_defaults(top);

    bool got = false;
    for (int i = 0; i < 64; ++i) {
        if (top->dbg_l1d_miss_o || top->dbg_3d_store_o || top->dbg_dram_busy_o) {
            saw_lower_hierarchy = true;
        }

        if (top->resp_valid_o || top->fault_o) {
            got = true;
            break;
        }

        tick(top);
    }

    pass &= expect(saw_lower_hierarchy, "store enters lower hierarchy");
    pass &= expect(got, "store response observed");
    pass &= expect(top->resp_valid_o == 1, "store response valid");
    pass &= expect(top->resp_write_ack_o == 1, "store write ack");
    pass &= expect(top->fault_o == 0, "store no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool data_load(Vtb_nvisc_data_lane_3d_dram* top, uint64_t addr, uint64_t expected, const char* label) {
    std::cout << "[DATA-3D-DRAM] Case " << label << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_size_bytes_i = 8;
    tick(top);

    set_defaults(top);

    bool got = wait_resp(top);
    bool pass = true;
    pass &= expect(got, "load response observed");
    pass &= expect(top->resp_valid_o == 1, "load response valid");
    pass &= expect(top->resp_rdata_o == expected, "load data");
    pass &= expect(top->fault_o == 0, "load no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool flush_3d(Vtb_nvisc_data_lane_3d_dram* top) {
    std::cout << "[DATA-3D-DRAM] Case flush 3D cache" << std::endl;

    set_defaults(top);
    top->flush_3d_i = 1;
    tick(top);

    set_defaults(top);
    tick(top);

    return expect(true, "3D flush issued");
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_data_lane_3d_dram;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->resp_valid_o == 0, "reset clears response");
    pass &= expect(top->fault_o == 0, "reset clears fault");

    top->rst_n = 1;
    tick(top);

    const uint64_t addr = 0x0000000080000040ULL;
    const uint64_t data = 0x13579BDF2468ACE0ULL;

    pass &= data_store(top, addr, data);
    pass &= data_load(top, addr, data, "DATA load hits L1D after store");

    pass &= flush_3d(top);

    // L1D may still hold the line, so this validates upper cache hierarchy keeps
    // the value. Later we can add an L1D flush to force 3D/DRAM refill.
    pass &= data_load(top, addr, data, "DATA load after 3D flush");

    delete top;

    if (!pass) {
        std::cerr << "[DATA-3D-DRAM] FAIL: DATA lane 3D/DRAM test failed." << std::endl;
        return 1;
    }

    std::cout << "[DATA-3D-DRAM] PASS: DATA lane 3D/DRAM test completed." << std::endl;
    return 0;
}
