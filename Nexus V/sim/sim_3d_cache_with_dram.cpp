#include "Vtb_nvisc_3d_cache_with_dram.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vtb_nvisc_3d_cache_with_dram* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[3D+DRAM] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_3d_cache_with_dram* top) {
    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    top->req_is_write_i = 0;
    top->req_paddr_i = 0;
    top->req_wdata_i = 0;
    top->req_size_bytes_i = 8;
    top->req_id_i = 0;
    top->flush_i = 0;
}

static bool wait_resp(Vtb_nvisc_3d_cache_with_dram* top, int max_cycles = 40) {
    for (int i = 0; i < max_cycles; ++i) {
        if (top->resp_valid_o || top->fault_o) {
            return true;
        }
        tick(top);
    }
    return false;
}

static bool cache_store(Vtb_nvisc_3d_cache_with_dram* top, uint64_t addr, uint64_t data) {
    std::cout << "[3D+DRAM] Case cache write-through store" << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_write_i = 1;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    top->req_size_bytes_i = 8;
    top->req_id_i = 0x31;
    tick(top);

    bool pass = true;
    pass &= expect(top->dbg_cache_store_o == 1, "3D cache store observed");

    set_defaults(top);

    bool got = wait_resp(top);
    pass &= expect(got, "store response observed");
    pass &= expect(top->resp_valid_o == 1, "store response valid");
    pass &= expect(top->resp_write_ack_o == 1, "store write ack");
    pass &= expect(top->resp_id_o == 0x31, "store response id");
    pass &= expect(top->fault_o == 0, "store no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool cache_read_hit(Vtb_nvisc_3d_cache_with_dram* top, uint64_t addr, uint64_t expected) {
    std::cout << "[3D+DRAM] Case cache read hit" << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_size_bytes_i = 8;
    top->req_id_i = 0x32;
    tick(top);

    bool pass = true;
    pass &= expect(top->dbg_cache_hit_o == 1, "3D cache hit");
    pass &= expect(top->resp_valid_o == 1, "read hit response valid");
    pass &= expect(top->resp_rdata_o == expected, "read hit data");
    pass &= expect(top->resp_id_o == 0x32, "read hit response id");
    pass &= expect(top->fault_o == 0, "read hit no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool flush_cache(Vtb_nvisc_3d_cache_with_dram* top) {
    std::cout << "[3D+DRAM] Case flush cache" << std::endl;

    set_defaults(top);
    top->flush_i = 1;
    tick(top);

    set_defaults(top);
    tick(top);

    return expect(true, "flush issued");
}

static bool cache_read_miss_fill_from_dram(Vtb_nvisc_3d_cache_with_dram* top, uint64_t addr, uint64_t expected) {
    std::cout << "[3D+DRAM] Case read miss fills from DRAM" << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_size_bytes_i = 8;
    top->req_id_i = 0x33;
    tick(top);

    bool pass = true;
    pass &= expect(top->dbg_cache_miss_o == 1, "3D cache miss");

    set_defaults(top);

    bool saw_fill = false;
    bool got_resp = false;

    for (int i = 0; i < 48; ++i) {
        if (top->dbg_cache_fill_o) {
            saw_fill = true;
        }
        if (top->resp_valid_o || top->fault_o) {
            got_resp = true;
            break;
        }
        tick(top);
    }

    pass &= expect(saw_fill || top->dbg_cache_fill_o == 1, "3D cache fill observed");
    pass &= expect(got_resp, "read miss response observed");
    pass &= expect(top->resp_valid_o == 1, "read miss response valid");
    pass &= expect(top->resp_rdata_o == expected, "DRAM-backed fill data");
    pass &= expect(top->resp_id_o == 0x33, "read miss response id");
    pass &= expect(top->fault_o == 0, "read miss no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool fault_case(
    Vtb_nvisc_3d_cache_with_dram* top,
    uint64_t addr,
    uint8_t size,
    uint16_t expected_code,
    const char* name
) {
    std::cout << "[3D+DRAM] Case " << name << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_size_bytes_i = size;
    tick(top);

    bool pass = true;
    pass &= expect(top->fault_o == 1, "fault asserted");
    pass &= expect(top->fault_code_o == expected_code, "fault code");

    set_defaults(top);
    tick(top);

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_3d_cache_with_dram;
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
    const uint64_t data = 0xAABBCCDDEEFF0011ULL;

    pass &= cache_store(top, addr, data);
    pass &= cache_read_hit(top, addr, data);
    pass &= flush_cache(top);
    pass &= cache_read_miss_fill_from_dram(top, addr, data);
    pass &= cache_read_hit(top, addr, data);

    pass &= fault_case(top, addr + 1, 8, 0x0C01, "cache misaligned fault");
    pass &= fault_case(top, addr, 4, 0x0C02, "cache bad-size fault");

    delete top;

    if (!pass) {
        std::cerr << "[3D+DRAM] FAIL: 3D cache + DRAM integration test failed." << std::endl;
        return 1;
    }

    std::cout << "[3D+DRAM] PASS: 3D cache + DRAM integration test completed." << std::endl;
    return 0;
}
