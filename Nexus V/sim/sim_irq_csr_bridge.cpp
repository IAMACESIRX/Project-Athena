#include "Vnvisc_irq_csr_bridge.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_irq_csr_bridge* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[IRQ-CSR] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_irq_csr_bridge* top) {
    top->csr_valid_i = 0;
    top->csr_write_i = 0;
    top->csr_read_i = 0;
    top->csr_addr_i = 0;
    top->csr_wdata_i = 0;

    top->cycle_count_i = 0;
    top->irq_pending_i = 0;
    top->irq_taken_i = 0;
    top->irq_vector_i = 0;
    top->irq_code_i = 0;
}

static bool csr_write(Vnvisc_irq_csr_bridge* top, uint16_t addr, uint64_t data) {
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

static bool csr_read_expect(Vnvisc_irq_csr_bridge* top, uint16_t addr, uint64_t expected, const char* label) {
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

    auto* top = new Vnvisc_irq_csr_bridge;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->global_irq_enable_o == 0, "reset global irq disabled");
    pass &= expect(top->timer_enable_o == 0, "reset timer disabled");
    pass &= expect(top->timer_compare_o == 0xFFFFFFFFFFFFFFFFULL, "reset timer compare max");
    pass &= expect(top->irq_vector_base_o == 0x80000000ULL, "reset vector base");

    top->rst_n = 1;
    tick(top);

    std::cout << "[IRQ-CSR] Case writes" << std::endl;
    pass &= csr_write(top, 0x300, 1);
    pass &= expect(top->global_irq_enable_o == 1, "global irq enable written");

    pass &= csr_write(top, 0x304, 1);
    pass &= expect(top->timer_enable_o == 1, "timer enable written");

    pass &= csr_write(top, 0x308, 0x12345678);
    pass &= csr_write(top, 0x30C, 0x00000009);
    pass &= expect(top->timer_compare_o == 0x0000000912345678ULL, "timer compare written");

    pass &= csr_write(top, 0x310, 0xCAFEBABE);
    pass &= csr_write(top, 0x314, 0x00000001);
    pass &= expect(top->irq_vector_base_o == 0x00000001CAFEBABEULL, "irq vector base written");

    std::cout << "[IRQ-CSR] Case reads" << std::endl;
    pass &= csr_read_expect(top, 0x300, 1, "read global irq enable");
    pass &= csr_read_expect(top, 0x304, 1, "read timer enable");
    pass &= csr_read_expect(top, 0x308, 0x12345678, "read compare low");
    pass &= csr_read_expect(top, 0x30C, 0x00000009, "read compare high");

    top->cycle_count_i = 0x00000002DEADBEEFULL;
    top->irq_pending_i = 1;
    top->irq_taken_i = 1;
    top->irq_code_i = 0x1001;
    top->irq_vector_i = 0x0000000080000010ULL;

    pass &= csr_read_expect(top, 0x320, 0xDEADBEEF, "read cycle low");
    pass &= csr_read_expect(top, 0x324, 0x00000002, "read cycle high");
    pass &= csr_read_expect(top, 0x328, 0x3, "read irq pending/taken");
    pass &= csr_read_expect(top, 0x32C, 0x1001, "read irq code");
    pass &= csr_read_expect(top, 0x330, 0x80000010, "read irq vector low");
    pass &= csr_read_expect(top, 0x334, 0x0, "read irq vector high");

    std::cout << "[IRQ-CSR] Case ack pulse" << std::endl;
    top->csr_valid_i = 1;
    top->csr_write_i = 1;
    top->csr_read_i = 0;
    top->csr_addr_i = 0x318;
    top->csr_wdata_i = 1;
    tick(top);

    pass &= expect(top->irq_ack_o == 1, "irq ack pulse");

    top->csr_valid_i = 0;
    top->csr_write_i = 0;
    top->csr_wdata_i = 0;
    tick(top);

    pass &= expect(top->irq_ack_o == 0, "irq ack clears after pulse");

    delete top;

    if (!pass) {
        std::cerr << "[IRQ-CSR] FAIL: IRQ CSR bridge test failed." << std::endl;
        return 1;
    }

    std::cout << "[IRQ-CSR] PASS: IRQ CSR bridge test completed." << std::endl;
    return 0;
}
