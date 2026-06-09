#include "Vnvisc_cache_maintenance_csr.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_cache_maintenance_csr* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CACHE-CSR] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_cache_maintenance_csr* top) {
    top->csr_valid_i = 0;
    top->csr_write_i = 0;
    top->csr_read_i = 0;
    top->csr_addr_i = 0;
    top->csr_wdata_i = 0;
}

static bool write_ctl(Vnvisc_cache_maintenance_csr* top, uint64_t value, const char* label) {
    std::cout << "[CACHE-CSR] Case " << label << std::endl;

    set_defaults(top);
    top->csr_valid_i = 1;
    top->csr_write_i = 1;
    top->csr_addr_i = 0x7D0;
    top->csr_wdata_i = value;
    tick(top);

    bool pass = true;
    pass &= expect(top->csr_resp_valid_o == 1, "CSR write response valid");
    pass &= expect(top->csr_fault_o == 0, "CSR write no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool read_status(Vnvisc_cache_maintenance_csr* top, uint64_t expected, const char* label) {
    std::cout << "[CACHE-CSR] Case " << label << std::endl;

    set_defaults(top);
    top->csr_valid_i = 1;
    top->csr_read_i = 1;
    top->csr_addr_i = 0x7D1;
    tick(top);

    bool pass = true;
    pass &= expect(top->csr_resp_valid_o == 1, "CSR read response valid");
    pass &= expect(top->csr_rdata_o == expected, "CSR status readback");
    pass &= expect(top->csr_fault_o == 0, "CSR read no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool bad_addr(Vnvisc_cache_maintenance_csr* top) {
    std::cout << "[CACHE-CSR] Case bad address" << std::endl;

    set_defaults(top);
    top->csr_valid_i = 1;
    top->csr_read_i = 1;
    top->csr_addr_i = 0x7FF;
    tick(top);

    bool pass = true;
    pass &= expect(top->csr_fault_o == 1, "bad address fault asserted");
    pass &= expect(top->csr_fault_code_o == 0x0C80, "bad address fault code");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool bad_op(Vnvisc_cache_maintenance_csr* top) {
    std::cout << "[CACHE-CSR] Case bad operation" << std::endl;

    set_defaults(top);
    top->csr_valid_i = 1;
    top->csr_write_i = 1;
    top->csr_read_i = 1;
    top->csr_addr_i = 0x7D0;
    tick(top);

    bool pass = true;
    pass &= expect(top->csr_fault_o == 1, "bad op fault asserted");
    pass &= expect(top->csr_fault_code_o == 0x0C81, "bad op fault code");

    set_defaults(top);
    tick(top);

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_cache_maintenance_csr;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->csr_resp_valid_o == 0, "reset clears response");
    pass &= expect(top->csr_fault_o == 0, "reset clears fault");
    pass &= expect(top->flush_l1d_o == 0, "reset clears L1D flush");
    pass &= expect(top->flush_3d_o == 0, "reset clears 3D flush");

    top->rst_n = 1;
    tick(top);

    pass &= write_ctl(top, 0x1, "write flush L1D");
    pass &= expect(top->flush_l1d_o == 0, "L1D flush pulse cleared after cycle");
    pass &= read_status(top, 0x1, "read status after L1D flush");

    pass &= write_ctl(top, 0x2, "write flush 3D");
    pass &= read_status(top, 0x2, "read status after 3D flush");

    set_defaults(top);
    top->csr_valid_i = 1;
    top->csr_write_i = 1;
    top->csr_addr_i = 0x7D0;
    top->csr_wdata_i = 0x4;
    tick(top);

    pass &= expect(top->csr_resp_valid_o == 1, "hierarchy write response valid");
    pass &= expect(top->flush_l1d_o == 1, "hierarchy pulses L1D flush");
    pass &= expect(top->flush_3d_o == 1, "hierarchy pulses 3D flush");
    pass &= expect(top->flush_data_hierarchy_o == 1, "hierarchy flush pulse");

    set_defaults(top);
    tick(top);

    pass &= read_status(top, 0x7, "read status after hierarchy flush");

    pass &= bad_addr(top);
    pass &= bad_op(top);

    delete top;

    if (!pass) {
        std::cerr << "[CACHE-CSR] FAIL: cache maintenance CSR test failed." << std::endl;
        return 1;
    }

    std::cout << "[CACHE-CSR] PASS: cache maintenance CSR test completed." << std::endl;
    return 0;
}
