#include "Vtb_nvisc_core_v02_with_dmem.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include "nvisc_instr_encode.hpp"

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vtb_nvisc_core_v02_with_dmem* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CORE-DMEM] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_core_v02_with_dmem* top) {
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

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

static void core_write_reg(Vtb_nvisc_core_v02_with_dmem* top, uint8_t addr, uint64_t data) {
    top->dbg_rf_we_i = 1;
    top->dbg_rf_waddr_i = addr;
    top->dbg_rf_wdata_i = data;
    tick(top);

    top->dbg_rf_we_i = 0;
    top->dbg_rf_waddr_i = 0;
    top->dbg_rf_wdata_i = 0;
    tick(top);
}

static void clear_instr(Vtb_nvisc_core_v02_with_dmem* top) {
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;
    tick(top);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_core_v02_with_dmem;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->pc_o == 0, "PC reset vector");

    top->rst_n = 1;
    tick(top);

    pass &= expect(top->pc_valid_o == 1, "PC valid after reset");

    // r2 = base address, r3 = store data.
    core_write_reg(top, 2, 0x1000);
    core_write_reg(top, 3, 0xA5A55A5ADEADBEEFULL);

    pass &= expect(top->dbg_rf_r2_o == 0x1000, "preload r2 base");
    pass &= expect(top->dbg_rf_r3_o == 0xA5A55A5ADEADBEEFULL, "preload r3 store data");

    // STORE r3, [r2 + 0x40]
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvenc_s(NV_OP_STORE, 2, 3, 0x40);

    tick(top);
    pass &= expect(top->decode_class_o == 3, "STORE decode class");
    pass &= expect(top->lsu_valid_o == 1, "STORE LSU valid");

    // Pipeline through LSU -> MMU -> DMEM.
    tick(top);
    tick(top);
    tick(top);

    pass &= expect(top->mem_req_valid_o == 1, "STORE translated request valid");
    pass &= expect(top->mem_req_is_write_o == 1, "STORE translated request write");
    pass &= expect(top->mem_req_paddr_o == 0x1040, "STORE translated paddr");
    pass &= expect(top->mem_req_wdata_o == 0xA5A55A5ADEADBEEFULL, "STORE translated wdata");

    // One more edge for DMEM response/ack if needed.
    tick(top);
    pass &= expect(top->dmem_resp_valid_o == 1, "STORE DMEM response valid");
    pass &= expect(top->dmem_resp_write_ack_o == 1, "STORE DMEM write ack");
    pass &= expect(top->core_fault_o == 0, "no fault after STORE");

    clear_instr(top);

    // LOAD r1, [r2 + 0x40]
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvenc_i(NV_OP_LOAD, 1, 2, 0x40);

    tick(top);
    pass &= expect(top->decode_class_o == 2, "LOAD decode class");
    pass &= expect(top->lsu_valid_o == 1, "LOAD LSU valid");

    // Pipeline through LSU -> MMU -> DMEM -> core load response/writeback.
    tick(top);
    tick(top);
    tick(top);

    pass &= expect(top->mem_req_valid_o == 1, "LOAD translated request valid");
    pass &= expect(top->mem_req_is_read_o == 1, "LOAD translated request read");
    pass &= expect(top->mem_req_paddr_o == 0x1040, "LOAD translated paddr");

    tick(top);
    pass &= expect(top->dmem_resp_valid_o == 1, "LOAD DMEM response valid");
    pass &= expect(top->dmem_resp_rdata_o == 0xA5A55A5ADEADBEEFULL, "LOAD DMEM response data");

    tick(top);
    // Extra edge: core register-file writeback after L1D/DMEM response.
    tick(top);
    pass &= expect(top->dbg_rf_r1_o == 0xA5A55A5ADEADBEEFULL, "LOAD writes r1 from DMEM");

    pass &= expect(top->core_fault_o == 0, "no fault after LOAD");

    delete top;

    if (!pass) {
        std::cerr << "[CORE-DMEM] FAIL: core+DMEM end-to-end test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-DMEM] PASS: core+DMEM end-to-end test completed." << std::endl;
    return 0;
}
