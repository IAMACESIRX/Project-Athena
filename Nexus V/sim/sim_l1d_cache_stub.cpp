#include "Vnvisc_l1d_cache_stub.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_l1d_cache_stub* top) {
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
    std::cout << "[L1D] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_l1d_cache_stub* top) {
    top->core_req_valid_i = 0;
    top->core_req_is_read_i = 0;
    top->core_req_is_write_i = 0;
    top->core_req_paddr_i = 0;
    top->core_req_wdata_i = 0;
    top->core_req_size_bytes_i = 8;
    top->core_req_mem_domain_i = 1;
    zero_wide_words(top->core_req_id_i, 5);

    top->mem_resp_valid_i = 0;
    top->mem_resp_rdata_i = 0;
    top->mem_resp_write_ack_i = 0;
    top->mem_fault_i = 0;
    top->mem_fault_code_i = 0;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_l1d_cache_stub;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->core_resp_valid_o == 0, "reset clears core response");

    top->rst_n = 1;
    tick(top);

    // First read should miss and request backing memory.
    top->core_req_valid_i = 1;
    top->core_req_is_read_i = 1;
    top->core_req_is_write_i = 0;
    top->core_req_paddr_i = 0x1000;
    top->core_req_size_bytes_i = 8;
    tick(top);

    std::cout << "[L1D] Case read miss" << std::endl;
    pass &= expect(top->dbg_miss_o == 1, "read miss");
    pass &= expect(top->mem_req_valid_o == 1, "backing read request valid");
    pass &= expect(top->mem_req_is_read_o == 1, "backing request is read");
    pass &= expect(top->mem_req_paddr_o == 0x1000, "backing request paddr");

    // Clear core request, provide memory fill.
    top->core_req_valid_i = 0;
    top->core_req_is_read_i = 0;
    top->mem_resp_valid_i = 1;
    top->mem_resp_rdata_i = 0xCAFEBABEDEADBEEFULL;
    tick(top);

    std::cout << "[L1D] Case fill" << std::endl;
    pass &= expect(top->dbg_fill_o == 1, "fill observed");
    pass &= expect(top->core_resp_valid_o == 1, "core response valid on fill");
    pass &= expect(top->core_resp_rdata_o == 0xCAFEBABEDEADBEEFULL, "fill data returned");

    set_defaults(top);
    tick(top);

    // Second read same address should hit without backing request.
    top->core_req_valid_i = 1;
    top->core_req_is_read_i = 1;
    top->core_req_paddr_i = 0x1000;
    top->core_req_size_bytes_i = 8;
    tick(top);

    std::cout << "[L1D] Case read hit" << std::endl;
    pass &= expect(top->dbg_hit_o == 1, "read hit");
    pass &= expect(top->core_resp_valid_o == 1, "core response valid on hit");
    pass &= expect(top->core_resp_rdata_o == 0xCAFEBABEDEADBEEFULL, "hit data");
    pass &= expect(top->mem_req_valid_o == 0, "no backing request on hit");

    set_defaults(top);
    tick(top);

    // Store should write-through to backing memory.
    top->core_req_valid_i = 1;
    top->core_req_is_write_i = 1;
    top->core_req_paddr_i = 0x1000;
    top->core_req_wdata_i = 0x1122334455667788ULL;
    top->core_req_size_bytes_i = 8;
    tick(top);

    std::cout << "[L1D] Case write-through store" << std::endl;
    pass &= expect(top->mem_req_valid_o == 1, "store backing request valid");
    pass &= expect(top->mem_req_is_write_o == 1, "store backing request write");
    pass &= expect(top->mem_req_wdata_o == 0x1122334455667788ULL, "store backing wdata");

    // Backing memory write ack.
    top->core_req_valid_i = 0;
    top->core_req_is_write_i = 0;
    top->mem_resp_write_ack_i = 1;
    tick(top);

    pass &= expect(top->core_resp_valid_o == 1, "store ack response valid");
    pass &= expect(top->core_resp_write_ack_o == 1, "store ack");

    set_defaults(top);
    tick(top);

    // Read same address should hit updated cached data.
    top->core_req_valid_i = 1;
    top->core_req_is_read_i = 1;
    top->core_req_paddr_i = 0x1000;
    top->core_req_size_bytes_i = 8;
    tick(top);

    std::cout << "[L1D] Case read hit after store update" << std::endl;
    pass &= expect(top->dbg_hit_o == 1, "read hit after store");
    pass &= expect(top->core_resp_rdata_o == 0x1122334455667788ULL, "updated hit data");

    delete top;

    if (!pass) {
        std::cerr << "[L1D] FAIL: L1D cache stub test failed." << std::endl;
        return 1;
    }

    std::cout << "[L1D] PASS: L1D cache stub test completed." << std::endl;
    return 0;
}
