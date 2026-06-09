#include "Vnvisc_alu_v02.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static bool expect(bool cond, const char* label) {
    std::cout << "[ALU] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static bool check_op(
    Vnvisc_alu_v02* top,
    const char* name,
    uint8_t op,
    uint64_t a,
    uint64_t b,
    uint64_t expected
) {
    top->alu_valid_i = 1;
    top->alu_op_i = op;
    top->src_a_i = a;
    top->src_b_i = b;
    top->eval();
    main_time++;

    bool pass = true;
    std::cout << "[ALU] Case " << name << std::endl;
    pass &= expect(top->result_valid_o == 1, "result valid");
    pass &= expect(top->result_o == expected, "result value");
    pass &= expect(top->fault_o == 0, "no fault");
    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_alu_v02;

    bool pass = true;

    // ALU ops:
    // ADD=0, SUB=1, AND=2, OR=3, XOR=4, SLT=5
    pass &= check_op(top, "ADD", 0, 10, 20, 30);
    pass &= check_op(top, "SUB", 1, 50, 8, 42);
    pass &= check_op(top, "AND", 2, 0xF0F0, 0x0FF0, 0x00F0);
    pass &= check_op(top, "OR",  3, 0xF000, 0x00F0, 0xF0F0);
    pass &= check_op(top, "XOR", 4, 0xAAAA, 0x00FF, 0xAA55);
    pass &= check_op(top, "SLT true", 5, uint64_t(-5), 3, 1);
    pass &= check_op(top, "SLT false", 5, 9, 3, 0);

    // Zero flag.
    top->alu_valid_i = 1;
    top->alu_op_i = 1; // SUB
    top->src_a_i = 123;
    top->src_b_i = 123;
    top->eval();
    main_time++;

    std::cout << "[ALU] Case zero flag" << std::endl;
    pass &= expect(top->result_valid_o == 1, "result valid");
    pass &= expect(top->result_o == 0, "result zero");
    pass &= expect(top->zero_o == 1, "zero flag");

    // Invalid op.
    top->alu_valid_i = 1;
    top->alu_op_i = 7;
    top->src_a_i = 1;
    top->src_b_i = 2;
    top->eval();
    main_time++;

    std::cout << "[ALU] Case invalid op" << std::endl;
    pass &= expect(top->result_valid_o == 0, "invalid op suppresses result");
    pass &= expect(top->fault_o == 1, "invalid op faults");
    pass &= expect(top->fault_code_o == 0x0201, "invalid op fault code");

    delete top;

    if (!pass) {
        std::cerr << "[ALU] FAIL: ALU functional test failed." << std::endl;
        return 1;
    }

    std::cout << "[ALU] PASS: ALU functional test completed." << std::endl;
    return 0;
}
