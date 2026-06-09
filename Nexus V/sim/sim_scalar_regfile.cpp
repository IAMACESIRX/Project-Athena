#include "Vnvisc_scalar_regfile.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_scalar_regfile* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[REG] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_scalar_regfile* top) {
    top->rs1_addr_i = 0;
    top->rs2_addr_i = 0;
    top->rd_we_i = 0;
    top->rd_addr_i = 0;
    top->rd_data_i = 0;
}

static void write_reg(Vnvisc_scalar_regfile* top, uint8_t addr, uint64_t data) {
    top->rd_we_i = 1;
    top->rd_addr_i = addr;
    top->rd_data_i = data;
    tick(top);

    top->rd_we_i = 0;
    top->rd_addr_i = 0;
    top->rd_data_i = 0;
    tick(top);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_scalar_regfile;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->dbg_r0_o == 0, "reset r0");
    pass &= expect(top->dbg_r1_o == 0, "reset r1");
    pass &= expect(top->dbg_r2_o == 0, "reset r2");
    pass &= expect(top->dbg_r3_o == 0, "reset r3");

    top->rst_n = 1;
    tick(top);

    // r0 must stay zero even if written.
    write_reg(top, 0, 0xDEADBEEFULL);
    top->rs1_addr_i = 0;
    top->eval();
    pass &= expect(top->rs1_data_o == 0, "r0 hardwired zero after write attempt");

    // Write/read r1 and r2.
    write_reg(top, 1, 0x1111222233334444ULL);
    write_reg(top, 2, 0xAAAABBBBCCCCDDDDULL);

    top->rs1_addr_i = 1;
    top->rs2_addr_i = 2;
    top->eval();

    pass &= expect(top->rs1_data_o == 0x1111222233334444ULL, "read r1 through port A");
    pass &= expect(top->rs2_data_o == 0xAAAABBBBCCCCDDDDULL, "read r2 through port B");
    pass &= expect(top->dbg_r1_o == 0x1111222233334444ULL, "debug r1 mirror");
    pass &= expect(top->dbg_r2_o == 0xAAAABBBBCCCCDDDDULL, "debug r2 mirror");

    // Overwrite r1.
    write_reg(top, 1, 0x5555666677778888ULL);
    top->rs1_addr_i = 1;
    top->eval();

    pass &= expect(top->rs1_data_o == 0x5555666677778888ULL, "overwrite r1");

    delete top;

    if (!pass) {
        std::cerr << "[REG] FAIL: scalar register file functional test failed." << std::endl;
        return 1;
    }

    std::cout << "[REG] PASS: scalar register file functional test completed." << std::endl;
    return 0;
}
