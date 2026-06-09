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
    std::cout << "[CORE-ST] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
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

    // Preload base and store-data registers.
    // STORE uses rs1 = r2 as address base and rs2 = r3 as store data.
    core_write_reg(top, 2, 0x1000);
    core_write_reg(top, 3, 0x1122334455667788ULL);

    pass &= expect(top->dbg_rf_r2_o == 0x1000, "preload r2 base");
    pass &= expect(top->dbg_rf_r3_o == 0x1122334455667788ULL, "preload r3 store data");

    // STORE r3, [r2 + 0x28]
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvenc_s(NV_OP_STORE, 2, 3, 0x28);
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    tick(top);

    pass &= expect(top->fetch_valid_o == 1, "fetch valid");
    pass &= expect(top->decode_class_o == 3, "decode class STORE");
    pass &= expect(top->lsu_valid_o == 1, "LSU valid");

    // Hold STORE stable one more edge so registered LSU request passes through MMU/TLB.
    tick(top);

    // Extra edge: MMU/TLB registered translation becomes visible.
    tick(top);

    pass &= expect(top->mem_req_valid_o == 1, "memory request valid");
    pass &= expect(top->mem_req_is_write_o == 1, "memory request is write");
    pass &= expect(top->mem_req_is_read_o == 0, "memory request is not read");
    pass &= expect(top->mem_req_vaddr_o == 0x1028, "STORE address r2+imm");
    pass &= expect(top->mem_req_paddr_o == 0x1028, "STORE paddr equals vaddr in stub");
    pass &= expect(top->mem_req_wdata_o == 0x1122334455667788ULL, "STORE wdata equals r3");
    pass &= expect(top->mem_req_size_bytes_o == 8, "STORE size bytes");
    pass &= expect(top->core_fault_o == 0, "no core fault");

    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    tick(top);

    delete top;

    if (!pass) {
        std::cerr << "[CORE-ST] FAIL: integrated STORE data-path test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-ST] PASS: integrated STORE data-path test completed." << std::endl;
    return 0;
}
