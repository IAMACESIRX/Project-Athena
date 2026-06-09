#include "Vnvisc_mem_domain_csr_bridge.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_mem_domain_csr_bridge* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[MEMDOM-CSR] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_mem_domain_csr_bridge* top) {
    top->csr_valid_i = 0;
    top->csr_write_i = 0;
    top->csr_read_i = 0;
    top->csr_addr_i = 0;
    top->csr_wdata_i = 0;
    top->core_mem_domain_i = 1;
}

static bool csr_write(Vnvisc_mem_domain_csr_bridge* top, uint16_t addr, uint64_t data, bool expect_fault = false) {
    top->csr_valid_i = 1;
    top->csr_write_i = 1;
    top->csr_read_i = 0;
    top->csr_addr_i = addr;
    top->csr_wdata_i = data;
    tick(top);

    bool pass = true;
    pass &= expect(top->csr_resp_valid_o == 1, "CSR write response valid");
    pass &= expect(top->csr_fault_o == (expect_fault ? 1 : 0), expect_fault ? "CSR write expected fault" : "CSR write no fault");

    top->csr_valid_i = 0;
    top->csr_write_i = 0;
    top->csr_addr_i = 0;
    top->csr_wdata_i = 0;
    tick(top);

    return pass;
}

static bool csr_read_expect(Vnvisc_mem_domain_csr_bridge* top, uint16_t addr, uint64_t expected, const char* label) {
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

    auto* top = new Vnvisc_mem_domain_csr_bridge;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->mem_domain_override_enable_o == 0, "reset override disabled");
    pass &= expect(top->mem_domain_select_o == 1, "reset selected DATA");
    pass &= expect(top->effective_mem_domain_o == 1, "reset effective follows core DATA");

    top->rst_n = 1;
    tick(top);

    std::cout << "[MEMDOM-CSR] Case normal core-selected domain" << std::endl;
    top->core_mem_domain_i = 1;
    tick(top);
    pass &= expect(top->effective_mem_domain_o == 1, "effective DATA when override disabled");

    top->core_mem_domain_i = 2;
    tick(top);
    pass &= expect(top->effective_mem_domain_o == 2, "effective EXECUTION follows core when override disabled");

    std::cout << "[MEMDOM-CSR] Case override EXECUTION" << std::endl;
    pass &= csr_write(top, 0x340, 2);
    pass &= csr_write(top, 0x344, 1);
    top->core_mem_domain_i = 1;
    tick(top);
    pass &= expect(top->mem_domain_override_enable_o == 1, "override enabled");
    pass &= expect(top->mem_domain_select_o == 2, "selected EXECUTION");
    pass &= expect(top->effective_mem_domain_o == 2, "effective EXECUTION with override");

    pass &= csr_read_expect(top, 0x340, 2, "read selected EXECUTION");
    pass &= csr_read_expect(top, 0x344, 1, "read override enabled");

    std::cout << "[MEMDOM-CSR] Case override LIVE/HOT" << std::endl;
    pass &= csr_write(top, 0x340, 3);
    tick(top);
    pass &= expect(top->mem_domain_select_o == 3, "selected LIVE/HOT");
    pass &= expect(top->effective_mem_domain_o == 3, "effective LIVE/HOT with override");

    std::cout << "[MEMDOM-CSR] Case disable override" << std::endl;
    pass &= csr_write(top, 0x344, 0);
    top->core_mem_domain_i = 1;
    tick(top);
    pass &= expect(top->mem_domain_override_enable_o == 0, "override disabled");
    pass &= expect(top->effective_mem_domain_o == 1, "effective returns to core DATA");

    std::cout << "[MEMDOM-CSR] Case invalid selected domain faults" << std::endl;
    pass &= csr_write(top, 0x340, 7, true);
    pass &= expect(top->mem_domain_select_o == 3, "invalid write does not change selected domain");

    delete top;

    if (!pass) {
        std::cerr << "[MEMDOM-CSR] FAIL: memory-domain CSR bridge test failed." << std::endl;
        return 1;
    }

    std::cout << "[MEMDOM-CSR] PASS: memory-domain CSR bridge test completed." << std::endl;
    return 0;
}
