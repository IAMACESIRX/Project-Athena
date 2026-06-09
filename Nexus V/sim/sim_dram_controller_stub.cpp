#include "Vnvisc_dram_controller_stub.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_dram_controller_stub* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[DRAM] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_dram_controller_stub* top) {
    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    top->req_is_write_i = 0;
    top->req_paddr_i = 0;
    top->req_wdata_i = 0;
    top->req_size_bytes_i = 8;
    top->req_id_i = 0;
}

static bool wait_resp(Vnvisc_dram_controller_stub* top) {
    for (int i = 0; i < 16; ++i) {
        if (top->resp_valid_o || top->fault_o) {
            return true;
        }
        tick(top);
    }
    return false;
}

static bool dram_store(Vnvisc_dram_controller_stub* top, uint64_t addr, uint64_t data) {
    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_write_i = 1;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    top->req_size_bytes_i = 8;
    top->req_id_i = 0x11;
    tick(top);

    set_defaults(top);

    bool got = wait_resp(top);
    bool pass = true;
    pass &= expect(got, "store response observed");
    pass &= expect(top->resp_valid_o == 1, "store response valid");
    pass &= expect(top->resp_write_ack_o == 1, "store write ack");
    pass &= expect(top->resp_id_o == 0x11, "store response id");
    pass &= expect(top->fault_o == 0, "store no fault");
    return pass;
}

static bool dram_load(Vnvisc_dram_controller_stub* top, uint64_t addr, uint64_t expected) {
    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_size_bytes_i = 8;
    top->req_id_i = 0x22;
    tick(top);

    set_defaults(top);

    bool got = wait_resp(top);
    bool pass = true;
    pass &= expect(got, "load response observed");
    pass &= expect(top->resp_valid_o == 1, "load response valid");
    pass &= expect(top->resp_rdata_o == expected, "load data");
    pass &= expect(top->resp_id_o == 0x22, "load response id");
    pass &= expect(top->fault_o == 0, "load no fault");
    return pass;
}

static bool fault_case(Vnvisc_dram_controller_stub* top, uint64_t addr, uint8_t size, uint16_t expected_code, const char* name) {
    std::cout << "[DRAM] Case " << name << std::endl;

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

    auto* top = new Vnvisc_dram_controller_stub;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->resp_valid_o == 0, "reset clears response");
    pass &= expect(top->fault_o == 0, "reset clears fault");

    top->rst_n = 1;
    tick(top);

    std::cout << "[DRAM] Case STORE/LOAD low DRAM address" << std::endl;
    pass &= dram_store(top, 0x0000000080000040ULL, 0x1122334455667788ULL);
    pass &= dram_load(top,  0x0000000080000040ULL, 0x1122334455667788ULL);

    std::cout << "[DRAM] Case STORE/LOAD second DRAM address" << std::endl;
    pass &= dram_store(top, 0x0000000080000100ULL, 0xDEADBEEFCAFEBABEULL);
    pass &= dram_load(top,  0x0000000080000100ULL, 0xDEADBEEFCAFEBABEULL);

    pass &= fault_case(top, 0x0000000080000041ULL, 8, 0x0D02, "misaligned address");
    pass &= fault_case(top, 0x0000000080000040ULL, 4, 0x0D03, "bad size");
    pass &= fault_case(top, 0x0000000090000000ULL, 8, 0x0D01, "out of range");

    delete top;

    if (!pass) {
        std::cerr << "[DRAM] FAIL: DRAM controller stub test failed." << std::endl;
        return 1;
    }

    std::cout << "[DRAM] PASS: DRAM controller stub test completed." << std::endl;
    return 0;
}
