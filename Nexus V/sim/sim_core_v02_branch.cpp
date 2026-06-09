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
    std::cout << "[CORE-BR] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
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

static bool run_branch_case(
    Vnvisc_core_v02* top,
    const char* name,
    uint64_t r2,
    uint64_t r3,
    uint16_t imm12,
    bool expect_taken
) {
    std::cout << "[CORE-BR] Case " << name << std::endl;

    core_write_reg(top, 2, r2);
    core_write_reg(top, 3, r3);

    uint64_t start_pc = top->pc_o;
    uint64_t expected_target = start_pc + imm12;

    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvenc_b(NV_OP_BRANCH, 2, 3, imm12);
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    top->dmem_resp_valid_i = 0;
    top->dmem_resp_rdata_i = 0;
    top->dmem_resp_fault_i = 0;
    top->dmem_resp_fault_code_i = 0;

    tick(top);

    bool pass = true;
    pass &= expect(top->fetch_valid_o == 1, "fetch valid");
    pass &= expect(top->decode_class_o == 4, "decode class BRANCH");
    pass &= expect(top->branch_valid_o == 1, "branch valid");
    pass &= expect(top->branch_taken_internal_o == expect_taken, expect_taken ? "branch taken" : "branch not taken");

    if (expect_taken) {
        pass &= expect(top->branch_target_internal_o == expected_target, "branch target pc+imm");

        // Hold branch stable one more cycle so PC unit samples internal branch_taken.
        tick(top);
        pass &= expect(top->pc_o == expected_target, "PC redirected to branch target");
    } else {
        uint64_t pc_before_next = top->pc_o;
        tick(top);
        pass &= expect(top->pc_o == pc_before_next + 4, "PC continues sequentially");
    }

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

    pass &= run_branch_case(top, "BEQ taken", 42, 42, 0x40, true);
    pass &= run_branch_case(top, "BEQ not taken", 42, 7, 0x40, false);

    delete top;

    if (!pass) {
        std::cerr << "[CORE-BR] FAIL: integrated branch core test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-BR] PASS: integrated branch core test completed." << std::endl;
    return 0;
}
