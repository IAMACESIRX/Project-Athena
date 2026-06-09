#include "Vnvisc_dmem_controller_stub.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_dmem_controller_stub* top) {
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
    std::cout << "[DMEM] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_dmem_controller_stub* top) {
    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    top->req_is_write_i = 0;
    top->req_paddr_i = 0;
    top->req_wdata_i = 0;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = 1; // NV_MEM_DATA
    zero_wide_words(top->req_id_i, 5);
}

static bool do_store(Vnvisc_dmem_controller_stub* top, uint64_t addr, uint64_t data) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_write_i = 1;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    top->req_size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[DMEM] Case STORE" << std::endl;
    pass &= expect(top->resp_valid_o == 1, "store response valid");
    pass &= expect(top->resp_write_ack_o == 1, "store ack");
    pass &= expect(top->fault_o == 0, "no store fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool do_load(Vnvisc_dmem_controller_stub* top, uint64_t addr, uint64_t expected) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[DMEM] Case LOAD" << std::endl;
    pass &= expect(top->resp_valid_o == 1, "load response valid");
    pass &= expect(top->resp_rdata_o == expected, "load data");
    pass &= expect(top->fault_o == 0, "no load fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool out_of_range_fault(Vnvisc_dmem_controller_stub* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = 0x100000;
    top->req_size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[DMEM] Case out-of-range fault" << std::endl;
    pass &= expect(top->resp_valid_o == 0, "no response on out-of-range");
    pass &= expect(top->fault_o == 1, "fault asserted");
    pass &= expect(top->fault_code_o == 0x0404, "out-of-range fault code");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool bad_size_fault(Vnvisc_dmem_controller_stub* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = 0x40;
    top->req_size_bytes_i = 4;

    tick(top);

    bool pass = true;
    std::cout << "[DMEM] Case bad-size fault" << std::endl;
    pass &= expect(top->resp_valid_o == 0, "no response on bad size");
    pass &= expect(top->fault_o == 1, "fault asserted");
    pass &= expect(top->fault_code_o == 0x0402, "bad-size fault code");

    set_defaults(top);
    tick(top);

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_dmem_controller_stub;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->resp_valid_o == 0, "reset clears response");
    pass &= expect(top->fault_o == 0, "reset clears fault");

    top->rst_n = 1;
    tick(top);

    pass &= do_store(top, 0x40, 0x1122334455667788ULL);
    pass &= do_load(top, 0x40, 0x1122334455667788ULL);
    pass &= do_store(top, 0x80, 0xDEADBEEFCAFEBABEULL);
    pass &= do_load(top, 0x80, 0xDEADBEEFCAFEBABEULL);
    pass &= out_of_range_fault(top);
    pass &= bad_size_fault(top);

    delete top;

    if (!pass) {
        std::cerr << "[DMEM] FAIL: data memory controller stub test failed." << std::endl;
        return 1;
    }

    std::cout << "[DMEM] PASS: data memory controller stub test completed." << std::endl;
    return 0;
}
