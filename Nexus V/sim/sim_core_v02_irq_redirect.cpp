#include "Vtb_nvisc_core_v02_with_irq.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include "nvisc_instr_encode.hpp"

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vtb_nvisc_core_v02_with_irq* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CORE-IRQ] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_core_v02_with_irq* top) {
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    top->global_irq_enable_i = 0;
    top->timer_enable_i = 0;
    top->timer_compare_i = 0xFFFFFFFFFFFFFFFFULL;
    top->irq_vector_base_i = 0x80000000ULL;
    top->external_irq_i = 0;
    top->irq_ack_i = 0;

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

    top->rollback_redirect_i = 0;
    top->rollback_pc_i = 0;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_core_v02_with_irq;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->pc_o == 0, "PC reset vector");

    top->rst_n = 1;
    tick(top);

    pass &= expect(top->pc_valid_o == 1, "PC valid after reset");

    // Enable timer interrupt. Compare should trigger quickly.
    top->global_irq_enable_i = 1;
    top->timer_enable_i = 1;
    top->timer_compare_i = 3;
    top->irq_vector_base_i = 0x80000000ULL;

    bool saw_taken = false;
    bool saw_pc_vector = false;

    for (int i = 0; i < 12; ++i) {
        if (top->irq_taken_o) {
            saw_taken = true;
        }
        if (top->pc_o == 0x80000010ULL) {
            saw_pc_vector = true;
        }
        tick(top);
    }

    std::cout << "[CORE-IRQ] Case timer IRQ redirect" << std::endl;
    pass &= expect(saw_taken, "timer irq taken");
    pass &= expect(top->irq_code_o == 0x1001, "timer irq code");
    pass &= expect(top->irq_vector_o == 0x80000010ULL, "timer irq vector");
    pass &= expect(saw_pc_vector, "PC redirects to timer vector");

    // Ack interrupt and move compare away.
    top->timer_compare_i = 0xFFFFFFFFFFFFFFFFULL;
    top->irq_ack_i = 1;
    tick(top);

    top->irq_ack_i = 0;
    tick(top);

    pass &= expect(top->irq_pending_o == 0, "irq pending cleared after ack");

    delete top;

    if (!pass) {
        std::cerr << "[CORE-IRQ] FAIL: integrated IRQ redirect test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-IRQ] PASS: integrated IRQ redirect test completed." << std::endl;
    return 0;
}
