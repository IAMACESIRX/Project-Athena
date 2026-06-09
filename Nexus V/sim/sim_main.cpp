#include "Vnexus_v_soc.h"
#include "verilated.h"
#include <iostream>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    Vnexus_v_soc* top = new Vnexus_v_soc;

    top->clk = 0;
    top->rst_n = 0;

    for (int cycle = 0; cycle < 100; cycle++) {
        top->clk = 0;
        top->eval();
        main_time++;

        top->clk = 1;
        top->eval();
        main_time++;

        if (cycle == 10) {
            top->rst_n = 1;
            std::cout << "[Nexus-V] Reset released at cycle " << cycle << std::endl;
        }
    }

    std::cout << "[Nexus-V] PASS: 100-cycle reset smoke simulation completed." << std::endl;

    delete top;
    return 0;
}
