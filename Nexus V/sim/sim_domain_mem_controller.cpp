#include "verilated.h"
#include <iostream>
#include <cstdint>

#if defined(TEST_EXECMEM)
#include "Vnvisc_execmem_controller_stub.h"
using DUT = Vnvisc_execmem_controller_stub;
static constexpr const char* TAG = "EXECMEM";
static constexpr uint64_t BASE = 0x2000;
static constexpr uint16_t OUT_OF_RANGE_FAULT = 0x0904;
static constexpr uint16_t BAD_SIZE_FAULT = 0x0902;
#elif defined(TEST_LIVEHOT)
#include "Vnvisc_livehot_controller_stub.h"
using DUT = Vnvisc_livehot_controller_stub;
static constexpr const char* TAG = "LIVEHOT";
static constexpr uint64_t BASE = 0x3000;
static constexpr uint16_t OUT_OF_RANGE_FAULT = 0x0A04;
static constexpr uint16_t BAD_SIZE_FAULT = 0x0A02;
#else
#error "Define TEST_EXECMEM or TEST_LIVEHOT"
#endif

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(DUT* top) {
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
    std::cout << "[" << TAG << "] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(DUT* top) {
    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    top->req_is_write_i = 0;
    top->req_paddr_i = 0;
    top->req_wdata_i = 0;
    top->req_size_bytes_i = 8;
    zero_wide_words(top->req_id_i, 5);
}

static bool do_store(DUT* top, uint64_t addr, uint64_t data) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_write_i = 1;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    top->req_size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[" << TAG << "] Case STORE" << std::endl;
    pass &= expect(top->resp_valid_o == 1, "store response valid");
    pass &= expect(top->resp_write_ack_o == 1, "store ack");
    pass &= expect(top->fault_o == 0, "no store fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool do_load(DUT* top, uint64_t addr, uint64_t expected) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[" << TAG << "] Case LOAD" << std::endl;
    pass &= expect(top->resp_valid_o == 1, "load response valid");
    pass &= expect(top->resp_rdata_o == expected, "load data");
    pass &= expect(top->fault_o == 0, "no load fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool out_of_range_fault(DUT* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = BASE + 0x100000;
    top->req_size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[" << TAG << "] Case out-of-range fault" << std::endl;
    pass &= expect(top->resp_valid_o == 0, "no response on out-of-range");
    pass &= expect(top->fault_o == 1, "fault asserted");
    pass &= expect(top->fault_code_o == OUT_OF_RANGE_FAULT, "out-of-range fault code");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool bad_size_fault(DUT* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = BASE + 0x40;
    top->req_size_bytes_i = 4;

    tick(top);

    bool pass = true;
    std::cout << "[" << TAG << "] Case bad-size fault" << std::endl;
    pass &= expect(top->resp_valid_o == 0, "no response on bad size");
    pass &= expect(top->fault_o == 1, "fault asserted");
    pass &= expect(top->fault_code_o == BAD_SIZE_FAULT, "bad-size fault code");

    set_defaults(top);
    tick(top);

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new DUT;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->resp_valid_o == 0, "reset clears response");
    pass &= expect(top->fault_o == 0, "reset clears fault");

    top->rst_n = 1;
    tick(top);

    pass &= do_store(top, BASE + 0x40, 0x1122334455667788ULL);
    pass &= do_load(top, BASE + 0x40, 0x1122334455667788ULL);
    pass &= do_store(top, BASE + 0x80, 0xDEADBEEFCAFEBABEULL);
    pass &= do_load(top, BASE + 0x80, 0xDEADBEEFCAFEBABEULL);
    pass &= out_of_range_fault(top);
    pass &= bad_size_fault(top);

    delete top;

    if (!pass) {
        std::cerr << "[" << TAG << "] FAIL: domain memory controller test failed." << std::endl;
        return 1;
    }

    std::cout << "[" << TAG << "] PASS: domain memory controller test completed." << std::endl;
    return 0;
}
