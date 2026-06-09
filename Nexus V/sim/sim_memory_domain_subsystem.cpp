#include "Vtb_nvisc_memory_domain_subsystem.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vtb_nvisc_memory_domain_subsystem* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static void zero_wide_words(WData* words, int count) {
    for (int i = 0; i < count; ++i) {
        words[i] = 0;
    }
}

static bool expect(bool cond, const char* label) {
    std::cout << "[MEM-SYS] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_memory_domain_subsystem* top) {
    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    top->req_is_write_i = 0;
    top->req_paddr_i = 0;
    top->req_wdata_i = 0;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = 1;
    zero_wide_words(top->req_id_i, 5);

    top->flush_data_l1d_i = 0;
    top->flush_data_3d_i = 0;

    top->cache_csr_valid_i = 0;
    top->cache_csr_write_i = 0;
    top->cache_csr_read_i = 0;
    top->cache_csr_addr_i = 0;
    top->cache_csr_wdata_i = 0;
}

static bool wait_for_resp(
    Vtb_nvisc_memory_domain_subsystem* top,
    bool want_ack,
    uint64_t expected_data,
    const char* label
) {
    for (int i = 0; i < 16; ++i) {
        if (top->resp_valid_o) {
            bool pass = true;
            pass &= expect(top->fault_o == 0, "no subsystem fault");
            if (want_ack) {
                pass &= expect(top->resp_write_ack_o == 1, label);
            } else {
                pass &= expect(top->resp_rdata_o == expected_data, label);
            }
            return pass;
        }
        tick(top);
    }

    expect(false, label);
    return false;
}

static bool domain_store(
    Vtb_nvisc_memory_domain_subsystem* top,
    uint8_t domain,
    uint64_t addr,
    uint64_t data,
    const char* label
) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_write_i = 1;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = domain;
    tick(top);

    top->req_valid_i = 0;
    top->req_is_write_i = 0;
    tick(top);

    return wait_for_resp(top, true, 0, label);
}

static bool domain_load(
    Vtb_nvisc_memory_domain_subsystem* top,
    uint8_t domain,
    uint64_t addr,
    uint64_t expected,
    const char* label
) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = domain;
    tick(top);

    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    tick(top);

    return wait_for_resp(top, false, expected, label);
}

static bool invalid_domain_fault(Vtb_nvisc_memory_domain_subsystem* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = 0x4000;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = 7;
    tick(top);

    // Router fault is a pulse; sample it before clearing the request.
    bool pass = true;
    pass &= expect(top->fault_o == 1, "invalid domain fault asserted");
    pass &= expect(top->fault_code_o == 0x0801, "invalid domain fault code");

    top->req_valid_i = 0;
    tick(top);

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_memory_domain_subsystem;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->resp_valid_o == 0, "reset clears response");
    pass &= expect(top->fault_o == 0, "reset clears fault");

    top->rst_n = 1;
    tick(top);

    std::cout << "[MEM-SYS] Case DATA lane" << std::endl;
    pass &= domain_store(top, 1, 0x0000000080000040ULL, 0x1111222233334444ULL, "DATA store ack");
    pass &= domain_load(top, 1, 0x0000000080000040ULL, 0x1111222233334444ULL, "DATA load data");

    std::cout << "[MEM-SYS] Case EXECUTION lane" << std::endl;
    pass &= domain_store(top, 2, 0x2040, 0x5555666677778888ULL, "EXECUTION store ack");
    pass &= domain_load(top, 2, 0x2040, 0x5555666677778888ULL, "EXECUTION load data");

    std::cout << "[MEM-SYS] Case LIVE/HOT lane" << std::endl;
    pass &= domain_store(top, 3, 0x3040, 0x9999AAAABBBBCCCCULL, "LIVE/HOT store ack");
    pass &= domain_load(top, 3, 0x3040, 0x9999AAAABBBBCCCCULL, "LIVE/HOT load data");

    std::cout << "[MEM-SYS] Case invalid domain" << std::endl;
    pass &= invalid_domain_fault(top);

    delete top;

    if (!pass) {
        std::cerr << "[MEM-SYS] FAIL: memory domain subsystem test failed." << std::endl;
        return 1;
    }

    std::cout << "[MEM-SYS] PASS: memory domain subsystem test completed." << std::endl;
    return 0;
}
