#include "Vtb_nvisc_core_v02_with_l1i_l1d_dmem.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include "nvisc_instr_encode.hpp"

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vtb_nvisc_core_v02_with_l1i_l1d_dmem* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CORE-HARVARD] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_core_v02_with_l1i_l1d_dmem* top) {
    top->backing_imem_resp_valid_i = 0;
    top->backing_imem_resp_instr_i = 0;
    top->backing_imem_resp_fault_i = 0;
    top->backing_imem_resp_fault_code_i = 0;

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

static bool wait_for_backing_imem_req(
    Vtb_nvisc_core_v02_with_l1i_l1d_dmem* top,
    uint64_t* captured_addr
) {
    for (int i = 0; i < 12; ++i) {
        if (top->backing_imem_req_valid_o) {
            *captured_addr = top->backing_imem_req_addr_o;
            std::cout << "[CORE-HARVARD] captured L1I backing request addr=0x"
                      << std::hex << *captured_addr << std::dec << std::endl;
            return expect(true, "L1I backing request appears");
        }
        tick(top);
    }

    expect(false, "L1I backing request appears");
    return false;
}

static bool wait_for_fetch_decode(
    Vtb_nvisc_core_v02_with_l1i_l1d_dmem* top,
    uint32_t expected_instr,
    uint8_t expected_class
) {
    for (int i = 0; i < 12; ++i) {
        if (top->fetch_valid_o) {
            bool pass = true;
            pass &= expect(top->fetch_instr_o == expected_instr, "core fetch instruction");
            pass &= expect(top->decode_class_o == expected_class, "core decode class");
            return pass;
        }
        tick(top);
    }

    expect(false, "core fetch/decode receives instruction");
    return false;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_core_v02_with_l1i_l1d_dmem;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->pc_o == 0, "PC reset vector");

    top->rst_n = 1;
    tick(top);

    pass &= expect(top->pc_valid_o == 1, "PC valid after reset");

    // First instruction fetch should miss in L1I and request backing imem.
    // Capture the actual address because the PC may have already advanced by
    // the time the registered L1I request is observed.
    uint64_t cached_pc = 0;
    pass &= wait_for_backing_imem_req(top, &cached_pc);
    pass &= expect(top->l1i_miss_o == 1, "L1I miss observed");

    // Fill with NOP for the captured address.
    top->backing_imem_resp_valid_i = 1;
    top->backing_imem_resp_instr_i = nvenc_nop();
    top->backing_imem_resp_fault_i = 0;
    top->backing_imem_resp_fault_code_i = 0;
    tick(top);

    pass &= expect(top->l1i_fill_o == 1, "L1I fill observed");

    top->backing_imem_resp_valid_i = 0;
    top->backing_imem_resp_instr_i = 0;

    pass &= wait_for_fetch_decode(top, nvenc_nop(), 0);

    // The combined wrapper proves the integration path:
    // core imem request -> L1I miss -> backing fill -> core fetch/decode.
    // Cache-hit behavior is verified in the standalone L1I regression; avoid
    // overcoupling this wrapper test to PC redirect timing.
    pass &= expect(top->core_fault_o == 0, "no core fault after L1I fill/fetch");

    delete top;

    if (!pass) {
        std::cerr << "[CORE-HARVARD] FAIL: combined L1I/L1D/DMEM wrapper test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-HARVARD] PASS: combined L1I/L1D/DMEM wrapper test completed." << std::endl;
    return 0;
}
