#include "Vnvisc_3d_cache_stub.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_3d_cache_stub* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[3DCACHE] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_3d_cache_stub* top) {
    top->core_req_valid_i = 0;
    top->core_req_is_read_i = 0;
    top->core_req_is_write_i = 0;
    top->core_req_paddr_i = 0;
    top->core_req_wdata_i = 0;
    top->core_req_size_bytes_i = 8;
    top->core_req_id_i = 0;

    top->mem_resp_valid_i = 0;
    top->mem_resp_rdata_i = 0;
    top->mem_resp_write_ack_i = 0;
    top->mem_resp_id_i = 0;

    top->mem_fault_i = 0;
    top->mem_fault_code_i = 0;

    top->flush_i = 0;
}

static bool read_miss_and_fill(Vnvisc_3d_cache_stub* top, uint64_t addr, uint64_t fill_data) {
    std::cout << "[3DCACHE] Case read miss and fill" << std::endl;

    set_defaults(top);
    top->core_req_valid_i = 1;
    top->core_req_is_read_i = 1;
    top->core_req_paddr_i = addr;
    top->core_req_size_bytes_i = 8;
    top->core_req_id_i = 0x21;
    tick(top);

    bool pass = true;
    pass &= expect(top->dbg_miss_o == 1, "read miss");
    pass &= expect(top->mem_req_valid_o == 1, "backing read request valid");
    pass &= expect(top->mem_req_is_read_o == 1, "backing request is read");
    pass &= expect(top->mem_req_paddr_o == addr, "backing request paddr");

    set_defaults(top);
    tick(top);

    top->mem_resp_valid_i = 1;
    top->mem_resp_rdata_i = fill_data;
    top->mem_resp_id_i = 0x21;
    tick(top);

    pass &= expect(top->dbg_fill_o == 1, "fill observed");
    pass &= expect(top->core_resp_valid_o == 1, "core response valid on fill");
    pass &= expect(top->core_resp_rdata_o == fill_data, "fill data returned");
    pass &= expect(top->core_resp_id_o == 0x21, "fill response id");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool read_hit(Vnvisc_3d_cache_stub* top, uint64_t addr, uint64_t expected) {
    std::cout << "[3DCACHE] Case read hit" << std::endl;

    set_defaults(top);
    top->core_req_valid_i = 1;
    top->core_req_is_read_i = 1;
    top->core_req_paddr_i = addr;
    top->core_req_size_bytes_i = 8;
    top->core_req_id_i = 0x22;
    tick(top);

    bool pass = true;
    pass &= expect(top->dbg_hit_o == 1, "read hit");
    pass &= expect(top->core_resp_valid_o == 1, "core response valid on hit");
    pass &= expect(top->core_resp_rdata_o == expected, "hit data");
    pass &= expect(top->mem_req_valid_o == 0, "no backing request on hit");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool store_write_through(Vnvisc_3d_cache_stub* top, uint64_t addr, uint64_t data) {
    std::cout << "[3DCACHE] Case write-through store" << std::endl;

    set_defaults(top);
    top->core_req_valid_i = 1;
    top->core_req_is_write_i = 1;
    top->core_req_paddr_i = addr;
    top->core_req_wdata_i = data;
    top->core_req_size_bytes_i = 8;
    top->core_req_id_i = 0x33;
    tick(top);

    bool pass = true;
    pass &= expect(top->dbg_store_o == 1, "store observed");
    pass &= expect(top->mem_req_valid_o == 1, "store backing request valid");
    pass &= expect(top->mem_req_is_write_o == 1, "store backing request write");
    pass &= expect(top->mem_req_wdata_o == data, "store backing wdata");

    set_defaults(top);
    tick(top);

    top->mem_resp_valid_i = 1;
    top->mem_resp_write_ack_i = 1;
    top->mem_resp_id_i = 0x33;
    tick(top);

    pass &= expect(top->core_resp_valid_o == 1, "store response valid");
    pass &= expect(top->core_resp_write_ack_o == 1, "store ack");
    pass &= expect(top->core_resp_id_o == 0x33, "store response id");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool flush_then_miss(Vnvisc_3d_cache_stub* top, uint64_t addr) {
    std::cout << "[3DCACHE] Case flush invalidates line" << std::endl;

    set_defaults(top);
    top->flush_i = 1;
    tick(top);

    set_defaults(top);
    tick(top);

    top->core_req_valid_i = 1;
    top->core_req_is_read_i = 1;
    top->core_req_paddr_i = addr;
    top->core_req_size_bytes_i = 8;
    top->core_req_id_i = 0x44;
    tick(top);

    bool pass = true;
    pass &= expect(top->dbg_miss_o == 1, "miss after flush");
    pass &= expect(top->mem_req_valid_o == 1, "backing request after flush");

    set_defaults(top);
    tick(top);

    return pass;
}

static bool fault_case(Vnvisc_3d_cache_stub* top, uint64_t addr, uint8_t size, uint16_t expected_code, const char* name) {
    std::cout << "[3DCACHE] Case " << name << std::endl;

    set_defaults(top);
    top->core_req_valid_i = 1;
    top->core_req_is_read_i = 1;
    top->core_req_paddr_i = addr;
    top->core_req_size_bytes_i = size;
    tick(top);

    bool pass = true;
    pass &= expect(top->core_fault_o == 1, "cache fault asserted");
    pass &= expect(top->core_fault_code_o == expected_code, "cache fault code");

    set_defaults(top);
    tick(top);

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_3d_cache_stub;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;
    pass &= expect(top->core_resp_valid_o == 0, "reset clears core response");
    pass &= expect(top->mem_req_valid_o == 0, "reset clears backing request");

    top->rst_n = 1;
    tick(top);

    const uint64_t addr = 0x0000000080000040ULL;
    const uint64_t fill = 0x1122334455667788ULL;
    const uint64_t updated = 0xDEADBEEFCAFEBABEULL;

    pass &= read_miss_and_fill(top, addr, fill);
    pass &= read_hit(top, addr, fill);
    pass &= store_write_through(top, addr, updated);
    pass &= read_hit(top, addr, updated);
    pass &= fault_case(top, addr + 1, 8, 0x0C01, "misaligned address");
    pass &= fault_case(top, addr, 4, 0x0C02, "bad size");
    pass &= flush_then_miss(top, addr);

    delete top;

    if (!pass) {
        std::cerr << "[3DCACHE] FAIL: 3D cache stub test failed." << std::endl;
        return 1;
    }

    std::cout << "[3DCACHE] PASS: 3D cache stub test completed." << std::endl;
    return 0;
}
