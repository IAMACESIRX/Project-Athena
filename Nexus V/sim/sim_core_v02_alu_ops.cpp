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
    std::cout << "[CORE-ALU] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
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

    top->lsu_base_value_i = 0;
    top->lsu_store_data_i = 0;
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

static bool run_alu_case(
    Vnvisc_core_v02* top,
    const char* name,
    uint32_t instr,
    uint64_t a,
    uint64_t b,
    uint64_t expected
) {
    std::cout << "[CORE-ALU] Case " << name << std::endl;

    // Use r2 and r3 as source operands. Destination is r1.
    core_write_reg(top, 2, a);
    core_write_reg(top, 3, b);

    bool pass = true;
    pass &= expect(top->dbg_rf_r2_o == a, "r2 preload");
    pass &= expect(top->dbg_rf_r3_o == b, "r3 preload");

    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = instr;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    top->dmem_resp_valid_i = 0;
    top->dmem_resp_rdata_i = 0;
    top->dmem_resp_fault_i = 0;
    top->dmem_resp_fault_code_i = 0;

    tick(top);

    pass &= expect(top->fetch_valid_o == 1, "fetch valid");
    pass &= expect(top->decode_class_o == 1, "decode class ALU");
    pass &= expect(top->alu_valid_o == 1, "ALU valid");
    pass &= expect(top->alu_result_valid_o == 1, "ALU result valid");
    pass &= expect(top->alu_result_o == expected, "ALU result value");
    pass &= expect(top->core_fault_o == 0, "no core fault");

    // Hold instruction one more edge for writeback.
    tick(top);
    pass &= expect(top->dbg_rf_r1_o == expected, "writeback to r1");

    // Clear instruction.
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    tick(top);

    return pass;
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

    pass &= run_alu_case(top, "ADD", nvenc_add(1, 2, 3), 10, 20, 30);
    pass &= run_alu_case(top, "SUB", nvenc_sub(1, 2, 3), 50, 8, 42);
    pass &= run_alu_case(top, "AND", nvenc_and(1, 2, 3), 0xF0F0, 0x0FF0, 0x00F0);
    pass &= run_alu_case(top, "OR",  nvenc_or (1, 2, 3), 0xF000, 0x00F0, 0xF0F0);
    pass &= run_alu_case(top, "XOR", nvenc_xor(1, 2, 3), 0xAAAA, 0x00FF, 0xAA55);

    // Signed SLT true: -5 < 3.
    pass &= run_alu_case(top, "SLT true", nvenc_slt(1, 2, 3), uint64_t(-5), 3, 1);

    // Signed SLT false: 9 < 3 is false.
    pass &= run_alu_case(top, "SLT false", nvenc_slt(1, 2, 3), 9, 3, 0);

    delete top;

    if (!pass) {
        std::cerr << "[CORE-ALU] FAIL: integrated ALU-op core test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-ALU] PASS: integrated ALU-op core test completed." << std::endl;
    return 0;
}
