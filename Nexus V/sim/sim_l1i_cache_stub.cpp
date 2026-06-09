#include "Vnvisc_l1i_cache_stub.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_l1i_cache_stub* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[L1I] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_l1i_cache_stub* top) {
    top->fetch_req_valid_i = 0;
    top->fetch_req_addr_i = 0;
    top->flush_i = 0;

    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_l1i_cache_stub;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->fetch_resp_valid_o == 0, "reset clears fetch response");
    pass &= expect(top->imem_req_valid_o == 0, "reset clears imem request");

    top->rst_n = 1;
    tick(top);

    // First fetch should miss and request backing instruction memory.
    top->fetch_req_valid_i = 1;
    top->fetch_req_addr_i = 0x1000;
    tick(top);

    std::cout << "[L1I] Case fetch miss" << std::endl;
    pass &= expect(top->dbg_miss_o == 1, "fetch miss");
    pass &= expect(top->imem_req_valid_o == 1, "backing imem request valid");
    pass &= expect(top->imem_req_addr_o == 0x1000, "backing imem request addr");

    // Clear fetch request and provide fill.
    top->fetch_req_valid_i = 0;
    top->fetch_req_addr_i = 0;
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = 0x00000013; // NOP-ish test instruction
    tick(top);

    std::cout << "[L1I] Case fill" << std::endl;
    pass &= expect(top->dbg_fill_o == 1, "fill observed");
    pass &= expect(top->fetch_resp_valid_o == 1, "fetch response valid on fill");
    pass &= expect(top->fetch_resp_instr_o == 0x00000013, "fill instruction returned");

    set_defaults(top);
    tick(top);

    // Second fetch same address should hit without backing request.
    top->fetch_req_valid_i = 1;
    top->fetch_req_addr_i = 0x1000;
    tick(top);

    std::cout << "[L1I] Case fetch hit" << std::endl;
    pass &= expect(top->dbg_hit_o == 1, "fetch hit");
    pass &= expect(top->fetch_resp_valid_o == 1, "fetch response valid on hit");
    pass &= expect(top->fetch_resp_instr_o == 0x00000013, "hit instruction");
    pass &= expect(top->imem_req_valid_o == 0, "no backing request on hit");

    set_defaults(top);
    tick(top);

    // Different tag same index should miss.
    top->fetch_req_valid_i = 1;
    top->fetch_req_addr_i = 0x2000;
    tick(top);

    std::cout << "[L1I] Case different tag miss" << std::endl;
    pass &= expect(top->dbg_miss_o == 1, "different tag miss");
    pass &= expect(top->imem_req_valid_o == 1, "backing request on different tag");

    // Complete the outstanding miss so the cache returns to IDLE before
    // testing a new misaligned fetch request.
    top->fetch_req_valid_i = 0;
    top->fetch_req_addr_i = 0;
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = 0x00000033;
    tick(top);

    pass &= expect(top->dbg_fill_o == 1, "different tag fill observed");

    set_defaults(top);
    tick(top);

    // Misaligned fetch should fault.
    top->fetch_req_valid_i = 1;
    top->fetch_req_addr_i = 0x1002;
    tick(top);

    std::cout << "[L1I] Case misaligned fetch" << std::endl;
    pass &= expect(top->fetch_resp_fault_o == 1, "misaligned fetch fault");
    pass &= expect(top->fetch_resp_fault_code_o == 0x0601, "misaligned fetch fault code");

    set_defaults(top);
    tick(top);

    // Flush should invalidate prior cached line.
    top->flush_i = 1;
    tick(top);

    set_defaults(top);
    tick(top);

    top->fetch_req_valid_i = 1;
    top->fetch_req_addr_i = 0x1000;
    tick(top);

    std::cout << "[L1I] Case miss after flush" << std::endl;
    pass &= expect(top->dbg_miss_o == 1, "miss after flush");
    pass &= expect(top->imem_req_valid_o == 1, "backing request after flush");

    delete top;

    if (!pass) {
        std::cerr << "[L1I] FAIL: L1I cache stub test failed." << std::endl;
        return 1;
    }

    std::cout << "[L1I] PASS: L1I cache stub test completed." << std::endl;
    return 0;
}
