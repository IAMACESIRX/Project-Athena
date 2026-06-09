#include "Vnvisc_branch_unit_v02.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static bool expect(bool cond, const char* label) {
    std::cout << "[BR] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_branch_unit_v02;
    bool pass = true;

    // Not valid: no branch.
    top->branch_valid_i = 0;
    top->pc_i = 0x1000;
    top->imm_i = 0x40;
    top->src_a_i = 5;
    top->src_b_i = 5;
    top->eval();
    main_time++;

    std::cout << "[BR] Case invalid" << std::endl;
    pass &= expect(top->branch_taken_o == 0, "invalid suppresses branch taken");
    pass &= expect(top->branch_target_o == 0x1040, "target still computes");

    // Equal: branch taken.
    top->branch_valid_i = 1;
    top->pc_i = 0x2000;
    top->imm_i = 0x80;
    top->src_a_i = 123;
    top->src_b_i = 123;
    top->eval();
    main_time++;

    std::cout << "[BR] Case equal" << std::endl;
    pass &= expect(top->branch_taken_o == 1, "equal operands branch taken");
    pass &= expect(top->branch_target_o == 0x2080, "target pc+imm");

    // Not equal: no branch.
    top->branch_valid_i = 1;
    top->pc_i = 0x3000;
    top->imm_i = 0x20;
    top->src_a_i = 1;
    top->src_b_i = 2;
    top->eval();
    main_time++;

    std::cout << "[BR] Case not equal" << std::endl;
    pass &= expect(top->branch_taken_o == 0, "not equal suppresses branch");
    pass &= expect(top->branch_target_o == 0x3020, "target pc+imm");

    delete top;

    if (!pass) {
        std::cerr << "[BR] FAIL: branch unit functional test failed." << std::endl;
        return 1;
    }

    std::cout << "[BR] PASS: branch unit functional test completed." << std::endl;
    return 0;
}
