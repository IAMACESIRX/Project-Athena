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
    std::cout << "[DATA-FLUSH] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
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

    top->flush_l1d_i = 0;
    top->flush_3d_i = 0;
}

static bool wait_resp(Vtb_nvisc_data_lane_3d_dram* top, int max_cycles = 96) {
    for (int i = 0; i < max_cycles; ++i) {
        if (top->resp_valid_o || top->fault_o) {
            return true;
        }
        tick(top);
    }
    return false;
}

static bool store_value(Vtb_nvisc_data_lane_3d_dram* top, uint64_t addr, uint64_t data) {
    std::cout << "[DATA-FLUSH] Case store value" << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_write_i = 1;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    tick(top);

    set_defaults(top);

    bool got = wait_resp(top);
    bool pass = true;
    pass &= expect(got, "store response observed");
    pass &= expect(top->resp_valid_o == 1, "store response valid");
    pass &= expect(top->resp_write_ack_o == 1, "store ack");
    pass &= expect(top->fault_o == 0, "store no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool load_expect(
    Vtb_nvisc_data_lane_3d_dram* top,
    uint64_t addr,
    uint64_t expected,
    const char* label,
    bool require_l1d_miss,
    bool require_3d_miss_or_fill
) {
    std::cout << "[DATA-FLUSH] Case " << label << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    tick(top);

    bool saw_l1d_miss = top->dbg_l1d_miss_o;
    bool saw_l1d_hit  = top->dbg_l1d_hit_o;
    bool saw_3d_hit   = top->dbg_3d_hit_o;
    bool saw_3d_miss  = top->dbg_3d_miss_o;
    bool saw_3d_fill  = top->dbg_3d_fill_o;
    bool saw_dram     = top->dbg_dram_busy_o;

    set_defaults(top);

    bool got = false;
    for (int i = 0; i < 128; ++i) {
        saw_l1d_miss |= top->dbg_l1d_miss_o;
        saw_l1d_hit  |= top->dbg_l1d_hit_o;
        saw_3d_hit   |= top->dbg_3d_hit_o;
        saw_3d_miss  |= top->dbg_3d_miss_o;
        saw_3d_fill  |= top->dbg_3d_fill_o;
        saw_dram     |= top->dbg_dram_busy_o;

        if (top->resp_valid_o || top->fault_o) {
            got = true;
            break;
        }

        tick(top);
    }

    bool pass = true;
    pass &= expect(got, "load response observed");
    pass &= expect(top->resp_valid_o == 1, "load response valid");
    pass &= expect(top->resp_rdata_o == expected, "load data");
    pass &= expect(top->fault_o == 0, "load no fault");

    if (require_l1d_miss) {
        pass &= expect(saw_l1d_miss, "observed L1D miss");
    } else {
        pass &= expect(saw_l1d_hit || saw_l1d_miss, "observed L1D activity");
    }

    if (require_3d_miss_or_fill) {
        pass &= expect(saw_3d_miss || saw_3d_fill || saw_dram, "observed 3D/DRAM refill path");
    } else {
        pass &= expect(saw_3d_hit || saw_3d_miss || saw_3d_fill || saw_dram || saw_l1d_hit, "observed hierarchy activity");
    }

    set_defaults(top);
    tick(top);

    return pass;
}

static bool flush_l1d(Vtb_nvisc_data_lane_3d_dram* top) {
    std::cout << "[DATA-FLUSH] Case flush L1D" << std::endl;

    set_defaults(top);
    top->flush_l1d_i = 1;
    tick(top);
    tick(top);

    set_defaults(top);
    tick(top);
    tick(top);

    return expect(true, "L1D flush issued");
}

static bool flush_l1d_and_3d(Vtb_nvisc_data_lane_3d_dram* top) {
    std::cout << "[DATA-FLUSH] Case flush L1D + 3D" << std::endl;

    set_defaults(top);
    top->flush_l1d_i = 1;
    top->flush_3d_i = 1;
    tick(top);
    tick(top);

    set_defaults(top);
    tick(top);
    tick(top);

    return expect(true, "L1D + 3D flush issued");
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

    const uint64_t addr = 0x0000000080000080ULL;
    const uint64_t data = 0xCAFED00D12345678ULL;

    pass &= store_value(top, addr, data);

    pass &= load_expect(
        top,
        addr,
        data,
        "load after store",
        false,
        false
    );

    pass &= flush_l1d(top);

    pass &= load_expect(
        top,
        addr,
        data,
        "load after L1D flush",
        true,
        false
    );

    pass &= flush_l1d_and_3d(top);

    pass &= load_expect(
        top,
        addr,
        data,
        "load after L1D + 3D flush",
        true,
        true
    );

    delete top;

    if (!pass) {
        std::cerr << "[DATA-FLUSH] FAIL: DATA hierarchy flush test failed." << std::endl;
        return 1;
    }

    std::cout << "[DATA-FLUSH] PASS: DATA hierarchy flush test completed." << std::endl;
    return 0;
}
