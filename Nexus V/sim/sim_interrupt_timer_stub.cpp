#include "Vnvisc_interrupt_timer_stub.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_interrupt_timer_stub* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[IRQ] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_interrupt_timer_stub* top) {
    top->global_irq_enable_i = 0;
    top->timer_enable_i = 0;
    top->timer_compare_i = 0;
    top->irq_vector_base_i = 0x80000000ULL;
    top->external_irq_i = 0;
    top->irq_ack_i = 0;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_interrupt_timer_stub;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->cycle_count_o == 0, "reset clears cycle counter");
    pass &= expect(top->irq_pending_o == 0, "reset clears irq pending");
    pass &= expect(top->irq_taken_o == 0, "reset clears irq taken");

    top->rst_n = 1;
    tick(top);

    pass &= expect(top->cycle_count_o == 1, "cycle counter increments");

    // Timer enabled but global IRQ disabled: pending may assert, taken must not.
    top->timer_enable_i = 1;
    top->timer_compare_i = 3;
    top->global_irq_enable_i = 0;

    for (int i = 0; i < 4; ++i) {
        tick(top);
    }

    std::cout << "[IRQ] Case timer pending with global disabled" << std::endl;
    pass &= expect(top->timer_pending_o == 1, "timer pending asserted");
    pass &= expect(top->irq_pending_o == 1, "irq pending asserted");
    pass &= expect(top->irq_taken_o == 0, "irq not taken when globally disabled");

    // Enable global IRQ. Timer should now be taken.
    top->global_irq_enable_i = 1;
    tick(top);

    std::cout << "[IRQ] Case timer taken" << std::endl;
    pass &= expect(top->irq_taken_o == 1, "timer irq taken");
    pass &= expect(top->irq_code_o == 0x1001, "timer irq code");
    pass &= expect(top->irq_vector_o == 0x80000010ULL, "timer irq vector");

    // Move compare away, then ack clears pending.
    top->timer_compare_i = 0xFFFFFFFFFFFFFFFFULL;
    top->irq_ack_i = 1;
    tick(top);

    top->irq_ack_i = 0;
    tick(top);

    std::cout << "[IRQ] Case ack clears timer" << std::endl;
    pass &= expect(top->timer_pending_o == 0, "timer pending cleared");
    pass &= expect(top->irq_pending_o == 0, "irq pending cleared");

    // External interrupt latches and takes.
    top->external_irq_i = 1;
    top->global_irq_enable_i = 1;
    tick(top);

    top->external_irq_i = 0;
    tick(top);

    std::cout << "[IRQ] Case external irq" << std::endl;
    pass &= expect(top->external_pending_o == 1, "external pending latched");
    pass &= expect(top->irq_taken_o == 1, "external irq taken");
    pass &= expect(top->irq_code_o == 0x1002, "external irq code");
    pass &= expect(top->irq_vector_o == 0x80000020ULL, "external irq vector");

    // Priority: external beats timer if both pending.
    top->timer_enable_i = 1;
    top->timer_compare_i = 0;
    tick(top);

    std::cout << "[IRQ] Case external priority over timer" << std::endl;
    pass &= expect(top->timer_pending_o == 1, "timer pending also set");
    pass &= expect(top->external_pending_o == 1, "external still pending");
    pass &= expect(top->irq_code_o == 0x1002, "external priority irq code");
    pass &= expect(top->irq_vector_o == 0x80000020ULL, "external priority irq vector");

    // Ack clears both.
    top->timer_compare_i = 0xFFFFFFFFFFFFFFFFULL;
    top->irq_ack_i = 1;
    tick(top);

    top->irq_ack_i = 0;
    tick(top);

    std::cout << "[IRQ] Case ack clears all" << std::endl;
    pass &= expect(top->timer_pending_o == 0, "timer pending cleared again");
    pass &= expect(top->external_pending_o == 0, "external pending cleared");
    pass &= expect(top->irq_pending_o == 0, "no pending irq");

    delete top;

    if (!pass) {
        std::cerr << "[IRQ] FAIL: interrupt/timer stub test failed." << std::endl;
        return 1;
    }

    std::cout << "[IRQ] PASS: interrupt/timer stub test completed." << std::endl;
    return 0;
}
