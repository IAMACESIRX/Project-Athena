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
    std::cout << "[CORE-LD] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
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

    // Preload base register r2 = 0x1000.
    core_write_reg(top, 2, 0x1000);
    pass &= expect(top->dbg_rf_r2_o == 0x1000, "preload r2 base");

    // LOAD r1, [r2 + 0x20]
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvenc_i(NV_OP_LOAD, 1, 2, 0x20);
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    tick(top);

    pass &= expect(top->fetch_valid_o == 1, "fetch valid");
    pass &= expect(top->decode_class_o == 2, "decode class LOAD");
    pass &= expect(top->lsu_valid_o == 1, "LSU valid");

    // Hold LOAD stable one more edge so registered LSU request becomes visible
    // and load_pending captures rd.
    tick(top);

    // Return memory data.
    top->dmem_resp_valid_i = 1;
    top->dmem_resp_rdata_i = 0xDEADBEEFCAFEBABEULL;
    top->dmem_resp_fault_i = 0;
    top->dmem_resp_fault_code_i = 0;

    // Check combinational load writeback before the clock edge clears load_pending.
    top->eval();
    pass &= expect(top->load_wb_valid_o == 1, "LOAD writeback valid");
    pass &= expect(top->load_wb_data_o == 0xDEADBEEFCAFEBABEULL, "LOAD writeback data");

    // Register file writes on edge while response is present.
    tick(top);
    pass &= expect(top->dbg_rf_r1_o == 0xDEADBEEFCAFEBABEULL, "LOAD writes r1");

    // Clear inputs.
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->dmem_resp_valid_i = 0;
    top->dmem_resp_rdata_i = 0;
    tick(top);

    delete top;

    if (!pass) {
        std::cerr << "[CORE-LD] FAIL: integrated LOAD writeback test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-LD] PASS: integrated LOAD writeback test completed." << std::endl;
    return 0;
}
