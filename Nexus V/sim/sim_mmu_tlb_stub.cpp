#include "Vnvisc_mmu_tlb_stub.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_mmu_tlb_stub* top) {
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
    std::cout << "[MMU] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_mmu_tlb_stub* top) {
    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    top->req_is_write_i = 0;
    top->req_vaddr_i = 0;
    top->req_wdata_i = 0;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = 1; // NV_MEM_DATA
    zero_wide_words(top->req_id_i, 5);
}

static bool identity_read(Vnvisc_mmu_tlb_stub* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_is_write_i = 0;
    top->req_vaddr_i = 0x0000000000001020ULL;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = 1;

    tick(top);

    bool pass = true;
    std::cout << "[MMU] Case identity read" << std::endl;
    pass &= expect(top->resp_valid_o == 1, "translation valid");
    pass &= expect(top->resp_is_read_o == 1, "read passthrough");
    pass &= expect(top->resp_is_write_o == 0, "write false");
    pass &= expect(top->resp_vaddr_o == 0x1020, "vaddr passthrough");
    pass &= expect(top->resp_paddr_o == 0x1020, "identity paddr");
    pass &= expect(top->resp_size_bytes_o == 8, "size passthrough");
    pass &= expect(top->mmu_fault_o == 0, "no fault");
    return pass;
}

static bool identity_write(Vnvisc_mmu_tlb_stub* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 0;
    top->req_is_write_i = 1;
    top->req_vaddr_i = 0x0000000000002040ULL;
    top->req_wdata_i = 0x1122334455667788ULL;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = 1;

    tick(top);

    bool pass = true;
    std::cout << "[MMU] Case identity write" << std::endl;
    pass &= expect(top->resp_valid_o == 1, "translation valid");
    pass &= expect(top->resp_is_read_o == 0, "read false");
    pass &= expect(top->resp_is_write_o == 1, "write passthrough");
    pass &= expect(top->resp_paddr_o == 0x2040, "identity paddr");
    pass &= expect(top->resp_wdata_o == 0x1122334455667788ULL, "wdata passthrough");
    pass &= expect(top->mmu_fault_o == 0, "no fault");
    return pass;
}

static bool page_fault(Vnvisc_mmu_tlb_stub* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_vaddr_i = 0xFFFF000000001000ULL;
    top->req_size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[MMU] Case page fault" << std::endl;
    pass &= expect(top->resp_valid_o == 0, "no translation on page fault");
    pass &= expect(top->mmu_fault_o == 1, "fault asserted");
    pass &= expect(top->mmu_fault_code_o == 0x0301, "page fault code");
    return pass;
}

static bool align_fault(Vnvisc_mmu_tlb_stub* top) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = 1;
    top->req_vaddr_i = 0x0000000000001002ULL;
    top->req_size_bytes_i = 8;

    tick(top);

    bool pass = true;
    std::cout << "[MMU] Case alignment fault" << std::endl;
    pass &= expect(top->resp_valid_o == 0, "no translation on alignment fault");
    pass &= expect(top->mmu_fault_o == 1, "fault asserted");
    pass &= expect(top->mmu_fault_code_o == 0x0302, "alignment fault code");
    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_mmu_tlb_stub;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->resp_valid_o == 0, "reset clears response");
    pass &= expect(top->mmu_fault_o == 0, "reset clears fault");

    top->rst_n = 1;
    tick(top);

    pass &= identity_read(top);
    pass &= identity_write(top);
    pass &= page_fault(top);
    pass &= align_fault(top);

    delete top;

    if (!pass) {
        std::cerr << "[MMU] FAIL: MMU/TLB stub functional test failed." << std::endl;
        return 1;
    }

    std::cout << "[MMU] PASS: MMU/TLB stub functional test completed." << std::endl;
    return 0;
}
