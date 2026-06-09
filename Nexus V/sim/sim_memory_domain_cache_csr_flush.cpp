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
    std::cout << "[MEM-CACHE-CSR] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
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

static bool wait_resp(Vtb_nvisc_memory_domain_subsystem* top, int max_cycles = 128) {
    for (int i = 0; i < max_cycles; ++i) {
        if (top->resp_valid_o || top->fault_o) {
            return true;
        }
        tick(top);
    }
    return false;
}

static bool data_store(Vtb_nvisc_memory_domain_subsystem* top, uint64_t addr, uint64_t data) {
    std::cout << "[MEM-CACHE-CSR] Case DATA store" << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_write_i = 1;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    top->req_mem_domain_i = 1;
    tick(top);

    set_defaults(top);

    bool got = wait_resp(top);
    bool pass = true;
    pass &= expect(got, "store response observed");
    pass &= expect(top->resp_valid_o == 1, "store response valid");
    pass &= expect(top->resp_write_ack_o == 1, "store ack");
    pass &= expect(top->fault_o == 0, "store no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool data_load(Vtb_nvisc_memory_domain_subsystem* top, uint64_t addr, uint64_t expected, const char* label) {
    std::cout << "[MEM-CACHE-CSR] Case " << label << std::endl;

    set_defaults(top);
    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_paddr_i = addr;
    top->req_mem_domain_i = 1;
    tick(top);

    set_defaults(top);

    bool got = wait_resp(top);
    bool pass = true;
    pass &= expect(got, "load response observed");
    pass &= expect(top->resp_valid_o == 1, "load response valid");
    pass &= expect(top->resp_rdata_o == expected, "load data");
    pass &= expect(top->fault_o == 0, "load no fault");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool csr_flush_hierarchy(Vtb_nvisc_memory_domain_subsystem* top) {
    std::cout << "[MEM-CACHE-CSR] Case CSR hierarchy flush" << std::endl;

    set_defaults(top);
    top->cache_csr_valid_i = 1;
    top->cache_csr_write_i = 1;
    top->cache_csr_addr_i = 0x7D0;
    top->cache_csr_wdata_i = 0x4;
    tick(top);

    bool pass = true;
    pass &= expect(top->cache_csr_resp_valid_o == 1, "cache CSR write response valid");
    pass &= expect(top->cache_csr_fault_o == 0, "cache CSR no fault");

    set_defaults(top);
    tick(top);
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

    const uint64_t addr = 0x00000000800000C0ULL;
    const uint64_t data = 0xABCD1234FEDC5678ULL;

    pass &= data_store(top, addr, data);
    pass &= data_load(top, addr, data, "warm load before CSR flush");
    pass &= csr_flush_hierarchy(top);
    pass &= data_load(top, addr, data, "load after CSR hierarchy flush");

    delete top;

    if (!pass) {
        std::cerr << "[MEM-CACHE-CSR] FAIL: memory-domain cache CSR flush test failed." << std::endl;
        return 1;
    }

    std::cout << "[MEM-CACHE-CSR] PASS: memory-domain cache CSR flush test completed." << std::endl;
    return 0;
}
