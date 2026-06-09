#include "Vtb_nvisc_instruction_decoder_scalar.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include "nvisc_instr_encode.hpp"

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static bool expect(bool cond, const char* label) {
    std::cout << "[DEC-FN] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static uint32_t make_instr(uint8_t opcode, uint8_t rd, uint8_t rs1, uint8_t rs2, uint16_t imm12) {
    uint32_t instr = 0;
    instr |= (opcode & 0x7F);
    instr |= (uint32_t(rd  & 0x1F) << 7);
    instr |= (uint32_t(rs1 & 0x1F) << 15);
    instr |= (uint32_t(rs2 & 0x1F) << 20);
    instr |= (uint32_t(imm12 & 0x0FFF) << 20);
    return instr;
}

static bool check_class(
    Vtb_nvisc_instruction_decoder_scalar* top,
    const char* name,
    uint32_t instr,
    uint8_t expected_class,
    bool reg_write,
    bool mem_read,
    bool mem_write,
    bool csr_read,
    bool branch,
    bool illegal
) {
    top->valid_i = 1;
    top->pc_i = 0x1000;
    top->instr_i = instr;
    top->eval();
    main_time++;

    bool pass = true;
    std::cout << "[DEC-FN] Case " << name << std::endl;

    pass &= expect(top->dbg_valid_o == 1, "valid");
    pass &= expect(top->dbg_instr_class_o == expected_class, "instruction class");
    pass &= expect(top->dbg_reg_write_o == reg_write, "reg_write");
    pass &= expect(top->dbg_mem_read_o == mem_read, "mem_read");
    pass &= expect(top->dbg_mem_write_o == mem_write, "mem_write");
    pass &= expect(top->dbg_csr_read_o == csr_read, "csr_read");
    pass &= expect(top->dbg_branch_o == branch, "branch");
    pass &= expect(top->dbg_illegal_o == illegal, "illegal");

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_instruction_decoder_scalar;
    bool pass = true;

    // Enum values from nvisc_core_v02_pkg.sv:
    // NOP=0, ALU=1, LOAD=2, STORE=3, BRANCH=4, CSR=5, ILLEGAL=255
    pass &= check_class(top, "NOP",    nvenc_nop(), 0,   false, false, false, false, false, false);
    pass &= check_class(top, "ADD",    nvenc_r(NV_OP_ALU, 1, 2, 3), 1,   true,  false, false, false, false, false);
    pass &= check_class(top, "LOAD",   nvenc_i(NV_OP_LOAD, 1, 2, 4), 2,   true,  true,  false, false, false, false);
    pass &= check_class(top, "STORE",  nvenc_s(NV_OP_STORE, 2, 3, 8), 3,   false, false, true,  false, false, false);
    pass &= check_class(top, "BRANCH", nvenc_b(NV_OP_BRANCH, 1, 2, 0), 4,   false, false, false, false, true,  false);
    pass &= check_class(top, "CSR",    nvenc_csr(NV_OP_CSR, 1, 0), 5,   true,  false, false, true,  false, false);
    pass &= check_class(top, "BAD",    nvenc_r(0x7F, 0, 0, 0), 255, false, false, false, false, false, true);

    // Invalid input should not assert illegal.
    top->valid_i = 0;
    top->pc_i = 0x2000;
    top->instr_i = nvenc_r(0x7F, 0, 0, 0);
    top->eval();
    main_time++;

    std::cout << "[DEC-FN] Case invalid fetch" << std::endl;
    pass &= expect(top->dbg_valid_o == 0, "invalid fetch suppresses valid");
    pass &= expect(top->dbg_illegal_o == 0, "invalid fetch suppresses illegal");

    delete top;

    if (!pass) {
        std::cerr << "[DEC-FN] FAIL: decoder functional test failed." << std::endl;
        return 1;
    }

    std::cout << "[DEC-FN] PASS: decoder functional test completed." << std::endl;
    return 0;
}
