#include "Vnvisc_pc_branch_unit.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_pc_branch_unit* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect_pc(Vnvisc_pc_branch_unit* top, uint64_t expected, const char* label) {
    bool ok = (top->pc_o == expected);
    std::cout << "[PC] " << label
              << " pc=0x" << std::hex << top->pc_o
              << " expected=0x" << expected
              << std::dec << " -> " << (ok ? "PASS" : "FAIL")
              << std::endl;
    return ok;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_pc_branch_unit;

    top->clk = 0;
    top->rst_n = 0;
    top->stall_i = 0;
    top->redirect_valid_i = 0;
    top->redirect_pc_i = 0;
    top->branch_taken_i = 0;
    top->branch_target_i = 0;
    top->trap_valid_i = 0;
    top->trap_vector_i = 0;
    top->rollback_redirect_i = 0;
    top->rollback_pc_i = 0;

    tick(top);
    bool pass = true;
    pass &= expect_pc(top, 0x0, "reset vector");

    top->rst_n = 1;
    tick(top);
    pass &= expect_pc(top, 0x4, "increments after reset release");

    tick(top);
    pass &= expect_pc(top, 0x8, "increments again");

    top->stall_i = 1;
    tick(top);
    pass &= expect_pc(top, 0x8, "stall holds PC");
    top->stall_i = 0;

    top->branch_taken_i = 1;
    top->branch_target_i = 0x100;
    tick(top);
    pass &= expect_pc(top, 0x100, "branch target");
    top->branch_taken_i = 0;

    top->redirect_valid_i = 1;
    top->redirect_pc_i = 0x200;
    tick(top);
    pass &= expect_pc(top, 0x200, "explicit redirect");
    top->redirect_valid_i = 0;

    top->trap_valid_i = 1;
    top->trap_vector_i = 0x300;
    tick(top);
    pass &= expect_pc(top, 0x300, "trap vector");
    top->trap_valid_i = 0;

    top->branch_taken_i = 1;
    top->branch_target_i = 0x400;
    top->rollback_redirect_i = 1;
    top->rollback_pc_i = 0x500;
    tick(top);
    pass &= expect_pc(top, 0x500, "rollback overrides branch");
    top->branch_taken_i = 0;
    top->rollback_redirect_i = 0;

    delete top;

    if (!pass) {
        std::cerr << "[PC] FAIL: PC/branch unit simulation failed." << std::endl;
        return 1;
    }

    std::cout << "[PC] PASS: PC/branch unit simulation completed." << std::endl;
    return 0;
}
