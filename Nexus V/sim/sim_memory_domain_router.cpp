#include "Vnvisc_memory_domain_router.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static void tick(Vnvisc_memory_domain_router* top) {
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
    std::cout << "[MEM-ROUTER] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vnvisc_memory_domain_router* top) {
    top->req_valid_i = 0;
    top->req_is_read_i = 0;
    top->req_is_write_i = 0;
    top->req_paddr_i = 0;
    top->req_wdata_i = 0;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = 1; // NV_MEM_DATA in current package
    zero_wide_words(top->req_id_i, 5);
}

static void drive_request(
    Vnvisc_memory_domain_router* top,
    uint8_t domain,
    uint64_t addr,
    uint64_t data,
    bool is_read,
    bool is_write
) {
    set_defaults(top);

    top->req_valid_i = 1;
    top->req_is_read_i = is_read ? 1 : 0;
    top->req_is_write_i = is_write ? 1 : 0;
    top->req_paddr_i = addr;
    top->req_wdata_i = data;
    top->req_size_bytes_i = 8;
    top->req_mem_domain_i = domain;

    tick(top);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vnvisc_memory_domain_router;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->data_req_valid_o == 0, "reset clears DATA route");
    pass &= expect(top->exec_req_valid_o == 0, "reset clears EXEC route");
    pass &= expect(top->livehot_req_valid_o == 0, "reset clears LIVE/HOT route");
    pass &= expect(top->router_fault_o == 0, "reset clears router fault");

    top->rst_n = 1;
    tick(top);

    std::cout << "[MEM-ROUTER] Case DATA route" << std::endl;
    drive_request(top, 1, 0x1000, 0x1111222233334444ULL, true, false);
    pass &= expect(top->data_req_valid_o == 1, "DATA route valid");
    pass &= expect(top->data_req_is_read_o == 1, "DATA route read");
    pass &= expect(top->data_req_paddr_o == 0x1000, "DATA route address");
    pass &= expect(top->exec_req_valid_o == 0, "EXEC not selected for DATA");
    pass &= expect(top->livehot_req_valid_o == 0, "LIVE/HOT not selected for DATA");
    pass &= expect(top->router_fault_o == 0, "no fault for DATA");

    set_defaults(top);
    tick(top);

    std::cout << "[MEM-ROUTER] Case EXECUTION route" << std::endl;
    drive_request(top, 2, 0x2000, 0x5555666677778888ULL, true, false);
    pass &= expect(top->exec_req_valid_o == 1, "EXECUTION route valid");
    pass &= expect(top->exec_req_is_read_o == 1, "EXECUTION route read");
    pass &= expect(top->exec_req_paddr_o == 0x2000, "EXECUTION route address");
    pass &= expect(top->data_req_valid_o == 0, "DATA not selected for EXECUTION");
    pass &= expect(top->livehot_req_valid_o == 0, "LIVE/HOT not selected for EXECUTION");
    pass &= expect(top->router_fault_o == 0, "no fault for EXECUTION");

    set_defaults(top);
    tick(top);

    std::cout << "[MEM-ROUTER] Case LIVE/HOT route" << std::endl;
    drive_request(top, 3, 0x3000, 0x9999AAAABBBBCCCCULL, false, true);
    pass &= expect(top->livehot_req_valid_o == 1, "LIVE/HOT route valid");
    pass &= expect(top->livehot_req_is_write_o == 1, "LIVE/HOT route write");
    pass &= expect(top->livehot_req_paddr_o == 0x3000, "LIVE/HOT route address");
    pass &= expect(top->livehot_req_wdata_o == 0x9999AAAABBBBCCCCULL, "LIVE/HOT route wdata");
    pass &= expect(top->data_req_valid_o == 0, "DATA not selected for LIVE/HOT");
    pass &= expect(top->exec_req_valid_o == 0, "EXECUTION not selected for LIVE/HOT");
    pass &= expect(top->router_fault_o == 0, "no fault for LIVE/HOT");

    set_defaults(top);
    tick(top);

    std::cout << "[MEM-ROUTER] Case invalid domain" << std::endl;
    drive_request(top, 7, 0x4000, 0, true, false);
    pass &= expect(top->data_req_valid_o == 0, "DATA not selected for invalid");
    pass &= expect(top->exec_req_valid_o == 0, "EXECUTION not selected for invalid");
    pass &= expect(top->livehot_req_valid_o == 0, "LIVE/HOT not selected for invalid");
    pass &= expect(top->router_fault_o == 1, "fault for invalid domain");
    pass &= expect(top->router_fault_code_o == 0x0801, "invalid domain fault code");

    delete top;

    if (!pass) {
        std::cerr << "[MEM-ROUTER] FAIL: memory domain router test failed." << std::endl;
        return 1;
    }

    std::cout << "[MEM-ROUTER] PASS: memory domain router test completed." << std::endl;
    return 0;
}
