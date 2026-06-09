#include "Vtb_nvisc_control_unit_scalar.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CTRL] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_control_unit_scalar* top) {
    top->valid_i = 1;
    top->instr_class_i = 0;
    top->dec_reg_write_i = 0;
    top->dec_mem_read_i = 0;
    top->dec_mem_write_i = 0;
    top->dec_csr_read_i = 0;
    top->dec_csr_write_i = 0;
    top->dec_illegal_i = 0;
    top->rd_i = 1;
    top->rs1_i = 2;
    top->rs2_i = 3;
    top->imm_i = 0x1234;
}

static bool check_case(
    Vtb_nvisc_control_unit_scalar* top,
    const char* name,
    uint8_t instr_class,
    bool dec_reg_write,
    bool dec_mem_read,
    bool dec_mem_write,
    bool dec_csr_read,
    bool dec_csr_write,
    bool dec_illegal,
    bool exp_alu,
    bool exp_lsu,
    bool exp_csr,
    bool exp_branch,
    bool exp_reg_write,
    bool exp_mem_read,
    bool exp_mem_write,
    bool exp_csr_read,
    bool exp_csr_write,
    bool exp_illegal,
    bool exp_trap
) {
    set_defaults(top);
    top->instr_class_i = instr_class;
    top->dec_reg_write_i = dec_reg_write;
    top->dec_mem_read_i = dec_mem_read;
    top->dec_mem_write_i = dec_mem_write;
    top->dec_csr_read_i = dec_csr_read;
    top->dec_csr_write_i = dec_csr_write;
    top->dec_illegal_i = dec_illegal;

    top->eval();
    main_time++;

    bool pass = true;
    std::cout << "[CTRL] Case " << name << std::endl;

    pass &= expect(top->alu_valid_o == exp_alu, "alu_valid");
    pass &= expect(top->lsu_valid_o == exp_lsu, "lsu_valid");
    pass &= expect(top->csr_valid_o == exp_csr, "csr_valid");
    pass &= expect(top->branch_valid_o == exp_branch, "branch_valid");

    pass &= expect(top->reg_write_o == exp_reg_write, "reg_write");
    pass &= expect(top->mem_read_o == exp_mem_read, "mem_read");
    pass &= expect(top->mem_write_o == exp_mem_write, "mem_write");
    pass &= expect(top->csr_read_o == exp_csr_read, "csr_read");
    pass &= expect(top->csr_write_o == exp_csr_write, "csr_write");

    pass &= expect(top->illegal_o == exp_illegal, "illegal");
    pass &= expect(top->trap_o == exp_trap, "trap");

    pass &= expect(top->rd_o == 1, "rd passthrough");
    pass &= expect(top->rs1_o == 2, "rs1 passthrough");
    pass &= expect(top->rs2_o == 3, "rs2 passthrough");
    pass &= expect(top->imm_o == 0x1234, "imm passthrough");

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_control_unit_scalar;
    bool pass = true;

    // Enum values:
    // NOP=0, ALU=1, LOAD=2, STORE=3, BRANCH=4, CSR=5, ILLEGAL=255
    pass &= check_case(top, "NOP",    0,   false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false);
    pass &= check_case(top, "ALU",    1,   true,  false, false, false, false, false, true,  false, false, false, true,  false, false, false, false, false, false);
    pass &= check_case(top, "LOAD",   2,   true,  true,  false, false, false, false, false, true,  false, false, true,  true,  false, false, false, false, false);
    pass &= check_case(top, "STORE",  3,   false, false, true,  false, false, false, false, true,  false, false, false, false, true,  false, false, false, false);
    pass &= check_case(top, "BRANCH", 4,   false, false, false, false, false, false, false, false, false, true,  false, false, false, false, false, false, false);
    pass &= check_case(top, "CSR",    5,   true,  false, false, true,  false, false, false, false, true,  false, true,  false, false, true,  false, false, false);
    pass &= check_case(top, "BAD",    255, false, false, false, false, false, true,  false, false, false, false, false, false, false, false, false, true,  true);

    // Invalid decode packet: should suppress all side effects.
    set_defaults(top);
    top->valid_i = 0;
    top->instr_class_i = 255;
    top->dec_illegal_i = 1;
    top->eval();
    main_time++;

    std::cout << "[CTRL] Case invalid packet" << std::endl;
    pass &= expect(top->dbg_any_valid_o == 0, "invalid packet marked not valid");
    pass &= expect(top->trap_o == 0, "invalid packet suppresses trap");
    pass &= expect(top->illegal_o == 0, "invalid packet suppresses illegal");

    delete top;

    if (!pass) {
        std::cerr << "[CTRL] FAIL: control unit functional test failed." << std::endl;
        return 1;
    }

    std::cout << "[CTRL] PASS: control unit functional test completed." << std::endl;
    return 0;
}
