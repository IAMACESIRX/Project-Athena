#include "Vnvisc_instruction_decoder.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void zero_wide_words(WData* words, int count) {
    for (int i = 0; i < count; ++i) {
        words[i] = 0;
    }
}

static bool expect(bool cond, const char* label) {
    std::cout << "[DEC] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_instruction_decoder;

    // Packed input fetch_packet_i is VlWide. Zero it for build/eval smoke.
    zero_wide_words(top->fetch_packet_i, 8);

    top->eval();
    main_time++;

    bool pass = true;
    pass &= expect(true, "decoder C++ model builds/evaluates");

    delete top;

    if (!pass) {
        std::cerr << "[DEC] FAIL: decoder simulation failed." << std::endl;
        return 1;
    }

    std::cout << "[DEC] PASS: decoder build/eval smoke completed." << std::endl;
    return 0;
}
