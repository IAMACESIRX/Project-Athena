#include "Vtb_nvisc_core_v02_with_irq_csr.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include "nvisc_instr_encode.hpp"

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vtb_nvisc_core_v02_with_irq_csr* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CORE-IRQ-CSR] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_core_v02_with_irq_csr* top) {
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    top->csr_valid_i = 0;
    top->csr_write_i = 0;
    top->csr_read_i = 0;
    top->csr_addr_i = 0;
    top->csr_wdata_i = 0;

    top->external_irq_i = 0;

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

static bool csr_write(Vtb_nvisc_core_v02_with_irq_csr* top, uint16_t addr, uint64_t data) {
    top->csr_valid_i = 1;
    top->csr_write_i = 1;
    top->csr_read_i = 0;
    top->csr_addr_i = addr;
    top->csr_wdata_i = data;
    tick(top);

    bool pass = true;
    pass &= expect(top->csr_resp_valid_o == 1, "CSR write response valid");
    pass &= expect(top->csr_fault_o == 0, "CSR write no fault");

    top->csr_valid_i = 0;
    top->csr_write_i = 0;
    top->csr_addr_i = 0;
    top->csr_wdata_i = 0;
    tick(top);

    return pass;
}

static bool csr_read_expect(Vtb_nvisc_core_v02_with_irq_csr* top, uint16_t addr, uint64_t expected, const char* label) {
    top->csr_valid_i = 1;
    top->csr_write_i = 0;
    top->csr_read_i = 1;
    top->csr_addr_i = addr;
    top->csr_wdata_i = 0;
    tick(top);

    bool pass = true;
    pass &= expect(top->csr_resp_valid_o == 1, "CSR read response valid");
    pass &= expect(top->csr_fault_o == 0, "CSR read no fault");
    pass &= expect(top->csr_rdata_o == expected, label);

    top->csr_valid_i = 0;
    top->csr_read_i = 0;
    top->csr_addr_i = 0;
    tick(top);

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_core_v02_with_irq_csr;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->pc_o == 0, "PC reset vector");

    top->rst_n = 1;
    tick(top);

    pass &= expect(top->pc_valid_o == 1, "PC valid after reset");

    std::cout << "[CORE-IRQ-CSR] Case configure timer through CSR" << std::endl;

    // IRQ vector base = 0x8000_0000
    pass &= csr_write(top, 0x310, 0x80000000);
    pass &= csr_write(top, 0x314, 0x00000000);

    // Timer compare = current small cycle target.
    pass &= csr_write(top, 0x308, 12);
    pass &= csr_write(top, 0x30C, 0);

    // Timer enable + global IRQ enable.
    pass &= csr_write(top, 0x304, 1);
    pass &= csr_write(top, 0x300, 1);

    bool saw_taken = false;
    bool saw_pc_vector = false;

    for (int i = 0; i < 24; ++i) {
        if (top->irq_taken_o) {
            saw_taken = true;
        }
        if (top->pc_o == 0x80000010ULL) {
            saw_pc_vector = true;
        }
        tick(top);
    }

    std::cout << "[CORE-IRQ-CSR] Case timer IRQ redirect via CSR config" << std::endl;
    pass &= expect(saw_taken, "timer irq taken");
    pass &= expect(top->irq_code_o == 0x1001, "timer irq code");
    pass &= expect(top->irq_vector_o == 0x80000010ULL, "timer irq vector");
    pass &= expect(saw_pc_vector, "PC redirects to timer vector");

    pass &= csr_read_expect(top, 0x328, 0x3, "CSR read irq pending/taken");
    pass &= csr_read_expect(top, 0x32C, 0x1001, "CSR read timer irq code");
    pass &= csr_read_expect(top, 0x330, 0x80000010, "CSR read active vector low");

    // Disable timer firing, then ack through CSR.
    pass &= csr_write(top, 0x308, 0xFFFFFFFF);
    pass &= csr_write(top, 0x30C, 0xFFFFFFFF);
    pass &= csr_write(top, 0x318, 1);

    tick(top);
    tick(top);

    pass &= expect(top->irq_pending_o == 0, "irq pending cleared after CSR ack");

    delete top;

    if (!pass) {
        std::cerr << "[CORE-IRQ-CSR] FAIL: CSR-controlled IRQ redirect test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-IRQ-CSR] PASS: CSR-controlled IRQ redirect test completed." << std::endl;
    return 0;
}
