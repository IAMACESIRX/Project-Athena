#include "Vnvisc_lsu_stub.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_lsu_stub* top) {
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
    std::cout << "[LSU] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_lsu_stub* top) {
    top->lsu_valid_i = 0;
    top->mem_read_i = 0;
    top->mem_write_i = 0;

    top->base_value_i = 0;
    top->imm_i = 0;
    top->store_data_i = 0;

    top->size_bytes_i = 8;
    top->mem_domain_i = 1; // NV_MEM_DATA

    zero_wide_words(top->id_i, 5);
}

static bool do_load(Vnvisc_lsu_stub* top) {
    set_defaults(top);

    top->lsu_valid_i = 1;
    top->mem_read_i = 1;
    top->mem_write_i = 0;
    top->base_value_i = 0x1000;
    top->imm_i = 0x20;
    top->size_bytes_i = 8;
    top->mem_domain_i = 1; // DATA

    tick(top);

    bool pass = true;
    std::cout << "[LSU] Case LOAD" << std::endl;
    pass &= expect(top->dbg_req_valid_o == 1, "request valid");
    pass &= expect(top->dbg_req_is_read_o == 1, "is_read");
    pass &= expect(top->dbg_req_is_write_o == 0, "is_write false");
    pass &= expect(top->dbg_req_vaddr_o == 0x1020, "vaddr = base + imm");
    pass &= expect(top->dbg_req_paddr_o == 0x1020, "paddr equals vaddr in stub");
    pass &= expect(top->dbg_req_size_bytes_o == 8, "size bytes");
    pass &= expect(top->dbg_req_mem_domain_o == 1, "memory domain DATA");
    pass &= expect(top->lsu_fault_o == 0, "no fault");

    return pass;
}

static bool do_store(Vnvisc_lsu_stub* top) {
    set_defaults(top);

    top->lsu_valid_i = 1;
    top->mem_read_i = 0;
    top->mem_write_i = 1;
    top->base_value_i = 0x2000;
    top->imm_i = 0x10;
    top->store_data_i = 0xAABBCCDDEEFF0011ULL;
    top->size_bytes_i = 8;
    top->mem_domain_i = 3; // LIVE_HOT

    tick(top);

    bool pass = true;
    std::cout << "[LSU] Case STORE" << std::endl;
    pass &= expect(top->dbg_req_valid_o == 1, "request valid");
    pass &= expect(top->dbg_req_is_read_o == 0, "is_read false");
    pass &= expect(top->dbg_req_is_write_o == 1, "is_write");
    pass &= expect(top->dbg_req_vaddr_o == 0x2010, "vaddr = base + imm");
    pass &= expect(top->dbg_req_wdata_o == 0xAABBCCDDEEFF0011ULL, "store data");
    pass &= expect(top->dbg_req_mem_domain_o == 3, "memory domain LIVE_HOT");
    pass &= expect(top->lsu_fault_o == 0, "no fault");

    return pass;
}

static bool bad_size(Vnvisc_lsu_stub* top) {
    set_defaults(top);

    top->lsu_valid_i = 1;
    top->mem_read_i = 1;
    top->size_bytes_i = 3;

    tick(top);

    bool pass = true;
    std::cout << "[LSU] Case bad size" << std::endl;
    pass &= expect(top->dbg_req_valid_o == 0, "no request on bad size");
    pass &= expect(top->lsu_fault_o == 1, "fault asserted");
    pass &= expect(top->lsu_fault_code_o == 0x0101, "bad size fault code");

    return pass;
}

static bool both_read_write(Vnvisc_lsu_stub* top) {
    set_defaults(top);

    top->lsu_valid_i = 1;
    top->mem_read_i = 1;
    top->mem_write_i = 1;
    top->size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[LSU] Case read+write conflict" << std::endl;
    pass &= expect(top->dbg_req_valid_o == 0, "no request on read+write conflict");
    pass &= expect(top->lsu_fault_o == 1, "fault asserted");
    pass &= expect(top->lsu_fault_code_o == 0x0102, "read+write fault code");

    return pass;
}

static bool no_op(Vnvisc_lsu_stub* top) {
    set_defaults(top);

    top->lsu_valid_i = 1;
    top->mem_read_i = 0;
    top->mem_write_i = 0;
    top->size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[LSU] Case no-op LSU valid" << std::endl;
    pass &= expect(top->dbg_req_valid_o == 0, "no request on no-op");
    pass &= expect(top->lsu_fault_o == 1, "fault asserted");
    pass &= expect(top->lsu_fault_code_o == 0x0103, "no-op fault code");

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_lsu_stub;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->dbg_req_valid_o == 0, "reset clears request");
    pass &= expect(top->lsu_fault_o == 0, "reset clears fault");

    top->rst_n = 1;
    tick(top);

    pass &= do_load(top);
    pass &= do_store(top);
    pass &= bad_size(top);
    pass &= both_read_write(top);
    pass &= no_op(top);

    delete top;

    if (!pass) {
        std::cerr << "[LSU] FAIL: LSU stub functional test failed." << std::endl;
        return 1;
    }

    std::cout << "[LSU] PASS: LSU stub functional test completed." << std::endl;
    return 0;
}
