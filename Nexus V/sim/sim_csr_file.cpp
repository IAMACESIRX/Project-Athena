#include "Vnvisc_csr_file.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_csr_file* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CSR] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_csr_file* top) {
    top->csr_valid_i = 0;
    top->csr_read_i = 0;
    top->csr_write_i = 0;
    top->csr_addr_i = 0;
    top->csr_wdata_i = 0;

    top->thread_id_i = 3;
    top->branch_id_i = 0x11;
    top->state_id_i = 0x22;
    top->commit_id_i = 0x33;
    top->privilege_i = 2; // NV_PRIV_MACHINE
    top->aegis_policy_id_i = 0x44;
}

static bool csr_read(Vnvisc_csr_file* top, uint16_t addr, uint64_t expected, const char* label) {
    top->csr_valid_i = 1;
    top->csr_read_i = 1;
    top->csr_write_i = 0;
    top->csr_addr_i = addr;
    tick(top);

    bool pass = true;
    std::cout << "[CSR] Read " << label << std::endl;
    pass &= expect(top->csr_rvalid_o == 1, "read valid");
    pass &= expect(top->csr_fault_o == 0, "no read fault");
    pass &= expect(top->csr_rdata_o == expected, "read data");

    top->csr_valid_i = 0;
    top->csr_read_i = 0;
    tick(top);

    return pass;
}

static bool csr_write(Vnvisc_csr_file* top, uint16_t addr, uint64_t data, const char* label, bool expect_fault) {
    top->csr_valid_i = 1;
    top->csr_read_i = 0;
    top->csr_write_i = 1;
    top->csr_addr_i = addr;
    top->csr_wdata_i = data;
    tick(top);

    bool pass = true;
    std::cout << "[CSR] Write " << label << std::endl;
    pass &= expect(top->csr_fault_o == expect_fault, expect_fault ? "write fault expected" : "no write fault");

    top->csr_valid_i = 0;
    top->csr_write_i = 0;
    tick(top);

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_csr_file;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->dbg_core_id_o == 0, "reset core_id");
    pass &= expect(top->dbg_branch_id_o == 1, "reset branch_id");
    pass &= expect(top->dbg_state_id_o == 1, "reset state_id");
    pass &= expect(top->dbg_commit_id_o == 0, "reset commit_id");
    pass &= expect(top->dbg_privilege_o == 2, "reset privilege machine");

    top->rst_n = 1;
    tick(top);

    pass &= expect(top->dbg_thread_id_o == 3, "thread_id live update");
    pass &= expect(top->dbg_branch_id_o == 0x11, "branch_id live update");
    pass &= expect(top->dbg_state_id_o == 0x22, "state_id live update");
    pass &= expect(top->dbg_commit_id_o == 0x33, "commit_id live update");
    pass &= expect(top->dbg_aegis_policy_id_o == 0x44, "aegis policy live update");

    // CSR addresses from package:
    // CORE=0, THREAD=1, BRANCH=2, STATE=3, COMMIT=4, PRIV=5, POLICY=6, STATUS=7
    pass &= csr_read(top, 0x000, 0x0,  "CORE_ID");
    pass &= csr_read(top, 0x001, 0x3,  "THREAD_ID");
    pass &= csr_read(top, 0x002, 0x11, "BRANCH_ID");
    pass &= csr_read(top, 0x003, 0x22, "STATE_ID");
    pass &= csr_read(top, 0x004, 0x33, "COMMIT_ID");
    pass &= csr_read(top, 0x005, 0x2,  "PRIVILEGE");
    pass &= csr_read(top, 0x006, 0x44, "AEGIS_POLICY");

    pass &= csr_write(top, 0x007, 0xABCD, "STATUS", false);
    pass &= csr_read(top, 0x007, 0xABCD, "STATUS after write");

    pass &= csr_write(top, 0x000, 0x55, "CORE_ID read-only", true);

    top->csr_valid_i = 1;
    top->csr_read_i = 1;
    top->csr_write_i = 0;
    top->csr_addr_i = 0xFFF;
    tick(top);
    std::cout << "[CSR] Read bad address" << std::endl;
    pass &= expect(top->csr_fault_o == 1, "bad address faults");
    pass &= expect(top->csr_fault_code_o == 0x0002, "bad address fault code");

    delete top;

    if (!pass) {
        std::cerr << "[CSR] FAIL: CSR file functional test failed." << std::endl;
        return 1;
    }

    std::cout << "[CSR] PASS: CSR file functional test completed." << std::endl;
    return 0;
}
