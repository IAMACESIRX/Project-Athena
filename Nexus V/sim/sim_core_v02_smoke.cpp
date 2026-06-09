#include "Vnvisc_core_v02.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include "nvisc_instr_encode.hpp"

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_core_v02* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CORE] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
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

static void set_defaults(Vnvisc_core_v02* top) {
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    top->dmem_resp_valid_i = 0;
    top->dmem_resp_rdata_i = 0;
    top->dmem_resp_fault_i = 0;
    top->dmem_resp_fault_code_i = 0;

    top->thread_id_i = 1;
    top->branch_id_i = 0x10;
    top->state_id_i = 0x20;
    top->commit_id_i = 0x30;
    top->privilege_i = 2;
    top->aegis_policy_id_i = 0x40;

    top->lsu_base_value_i = 0x1000;
    top->lsu_store_data_i = 0xAABBCCDDEEFF0011ULL;
    top->lsu_size_bytes_i = 8;

    top->dbg_rf_we_i = 0;
    top->dbg_rf_waddr_i = 0;
    top->dbg_rf_wdata_i = 0;

    top->stall_i = 0;
    top->flush_i = 0;

    top->redirect_valid_i = 0;
    top->redirect_pc_i = 0;

    top->branch_taken_i = 0;
    top->branch_target_i = 0;

    top->trap_valid_i = 0;
    top->trap_vector_i = 0;

    top->rollback_redirect_i = 0;
    top->rollback_pc_i = 0;
}

static void core_write_reg(Vnvisc_core_v02* top, uint8_t addr, uint64_t data) {
    top->dbg_rf_we_i = 1;
    top->dbg_rf_waddr_i = addr;
    top->dbg_rf_wdata_i = data;
    tick(top);

    top->dbg_rf_we_i = 0;
    top->dbg_rf_waddr_i = 0;
    top->dbg_rf_wdata_i = 0;
    tick(top);
}

static bool present_instr_and_check_decode(
    Vnvisc_core_v02* top,
    const char* name,
    uint32_t instr,
    uint8_t exp_class
) {
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = instr;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    top->dmem_resp_valid_i = 0;
    top->dmem_resp_rdata_i = 0;
    top->dmem_resp_fault_i = 0;
    top->dmem_resp_fault_code_i = 0;

    tick(top);

    bool pass = true;
    std::cout << "[CORE] Instruction " << name << std::endl;
    pass &= expect(top->fetch_valid_o == 1, "fetch valid");
    pass &= expect(top->fetch_instr_o == instr, "fetch instruction captured");
    pass &= expect(top->decode_class_o == exp_class, "decode class");

    return pass;
}

static void clear_instr(Vnvisc_core_v02* top) {
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    top->dmem_resp_valid_i = 0;
    top->dmem_resp_rdata_i = 0;
    top->dmem_resp_fault_i = 0;
    top->dmem_resp_fault_code_i = 0;
    tick(top);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_core_v02;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->pc_o == 0, "PC reset vector");

    top->rst_n = 1;
    tick(top);

    pass &= expect(top->pc_valid_o == 1, "PC valid after reset");
    pass &= expect(top->imem_req_valid_o == 1, "instruction request valid");

    // Preload scalar registers for ALU ADD test first.
    core_write_reg(top, 2, 10);
    core_write_reg(top, 3, 20);

    pass &= expect(top->dbg_rf_r2_o == 10, "preload r2 ALU operand");
    pass &= expect(top->dbg_rf_r3_o == 20, "preload r3 ALU operand");

    // NOP
    pass &= present_instr_and_check_decode(top, "NOP", nvenc_nop(), 0);
    pass &= expect(top->core_fault_o == 0, "no core fault");
    clear_instr(top);

    // ADD / ALU
    pass &= present_instr_and_check_decode(top, "ADD", nvenc_add(1, 2, 3), 1);
    pass &= expect(top->alu_valid_o == 1, "ALU valid for ADD");
    pass &= expect(top->alu_result_valid_o == 1, "ALU result valid for ADD");
    pass &= expect(top->alu_result_o == 30, "ALU ADD result r2+r3");
    pass &= expect(top->core_fault_o == 0, "no core fault");

    // Writeback occurs on the next clock edge while ADD remains presented.
    tick(top);
    pass &= expect(top->dbg_rf_r1_o == 30, "ALU writeback writes r1");

    clear_instr(top);

    // Re-preload scalar registers for LOAD/STORE tests.
    // LOAD uses rs1=r2 as base.
    // STORE uses rs1=r2 as base and rs2=r3 as store data.
    core_write_reg(top, 2, 0x1000);
    core_write_reg(top, 3, 0xAABBCCDDEEFF0011ULL);

    pass &= expect(top->dbg_rf_r2_o == 0x1000, "preload r2 base register");
    pass &= expect(top->dbg_rf_r3_o == 0xAABBCCDDEEFF0011ULL, "preload r3 store-data register");

    // LOAD
    pass &= present_instr_and_check_decode(top, "LOAD", nvenc_i(NV_OP_LOAD, 1, 2, 0x20), 2);
    pass &= expect(top->lsu_valid_o == 1, "LSU valid for LOAD");

    // LSU and MMU/TLB are registered. Hold instruction stable long enough for
    // LSU request generation and MMU translation to become visible.
    tick(top);
    tick(top);
    pass &= expect(top->mem_req_valid_o == 1, "memory request valid for LOAD");
    pass &= expect(top->mem_req_is_read_o == 1, "LOAD memory request is read");
    pass &= expect(top->mem_req_vaddr_o == 0x1020, "LOAD vaddr base+imm");
    clear_instr(top);

    // STORE
    pass &= present_instr_and_check_decode(top, "STORE", nvenc_s(NV_OP_STORE, 2, 3, 0x10), 3);
    pass &= expect(top->lsu_valid_o == 1, "LSU valid for STORE");

    // LSU and MMU/TLB are registered. Hold instruction stable long enough for
    // LSU request generation and MMU translation to become visible.
    tick(top);
    tick(top);
    pass &= expect(top->mem_req_valid_o == 1, "memory request valid for STORE");
    pass &= expect(top->mem_req_is_write_o == 1, "STORE memory request is write");
    pass &= expect(top->mem_req_vaddr_o == 0x1010, "STORE vaddr base+imm");
    clear_instr(top);

    // BRANCH
    pass &= present_instr_and_check_decode(top, "BRANCH", nvenc_b(NV_OP_BRANCH, 1, 2, 0), 4);
    pass &= expect(top->branch_valid_o == 1, "branch valid for BRANCH");
    pass &= expect(top->core_fault_o == 0, "no core fault");
    clear_instr(top);

    // CSR
    pass &= present_instr_and_check_decode(top, "CSR", nvenc_csr(NV_OP_CSR, 1, 0), 5);
    pass &= expect(top->csr_valid_o == 1, "CSR valid for CSR instruction");
    pass &= expect(top->core_fault_o == 0, "no core fault");
    clear_instr(top);

    // ILLEGAL
    pass &= present_instr_and_check_decode(top, "ILLEGAL", nvenc_r(0x7F, 0, 0, 0), 255);
    pass &= expect(top->core_fault_o == 1, "illegal instruction causes core fault");

    delete top;

    if (!pass) {
        std::cerr << "[CORE] FAIL: core v0.2 smoke test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE] PASS: core v0.2 smoke test completed." << std::endl;
    return 0;
}
