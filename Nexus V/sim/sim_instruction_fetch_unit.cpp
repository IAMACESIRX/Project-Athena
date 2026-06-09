#include "Vnvisc_instruction_fetch_unit.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void zero_wide_words(WData* words, int count) {
    for (int i = 0; i < count; ++i) {
        words[i] = 0;
    }
}

static void tick(Vnvisc_instruction_fetch_unit* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[IF] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_instruction_fetch_unit;

    top->clk = 0;
    top->rst_n = 0;

    top->stall_i = 0;
    top->flush_i = 0;
    top->pc_i = 0x1000;
    top->pc_valid_i = 0;

    zero_wide_words(top->id_i, 5);

    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    tick(top);

    bool pass = true;

    top->rst_n = 1;
    top->pc_valid_i = 1;
    top->pc_i = 0x1000;
    top->eval();

    pass &= expect(top->imem_req_valid_o == 1, "request valid when PC valid");
    pass &= expect(top->imem_req_addr_o == 0x1000, "request address equals PC");

    // Return instruction.
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = 0x00000013; // NOP-like placeholder
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;
    tick(top);

    pass &= expect(top->dbg_fetch_valid_o == 1, "fetch packet valid after response");
    pass &= expect(top->dbg_fetch_pc_o == 0x1000, "fetch packet PC captured");
    pass &= expect(top->dbg_fetch_instr_o == 0x00000013, "fetch packet instruction captured");
    pass &= expect(top->fetch_fault_o == 0, "no fetch fault");

    // Stall should suppress request.
    top->stall_i = 1;
    top->pc_i = 0x2000;
    top->imem_resp_valid_i = 0;
    top->eval();

    pass &= expect(top->imem_req_valid_o == 0, "stall suppresses request");

    top->stall_i = 0;

    // Flush should suppress request and clear packet on tick.
    top->flush_i = 1;
    top->eval();
    pass &= expect(top->imem_req_valid_o == 0, "flush suppresses request");
    tick(top);
    pass &= expect(top->dbg_fetch_valid_o == 0, "flush clears fetch packet");
    top->flush_i = 0;

    // Fault response.
    top->pc_i = 0x3000;
    top->pc_valid_i = 1;
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = 0xFFFFFFFF;
    top->imem_resp_fault_i = 1;
    top->imem_resp_fault_code_i = 0x0042;
    tick(top);

    pass &= expect(top->dbg_fetch_valid_o == 0, "fault response suppresses valid packet");
    pass &= expect(top->fetch_fault_o == 1, "fetch fault asserted");
    pass &= expect(top->fetch_fault_code_o == 0x0042, "fetch fault code captured");

    delete top;

    if (!pass) {
        std::cerr << "[IF] FAIL: instruction fetch simulation failed." << std::endl;
        return 1;
    }

    std::cout << "[IF] PASS: instruction fetch simulation completed." << std::endl;
    return 0;
}
