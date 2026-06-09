#include "Vtb_nvisc_core_v02_with_mem_domains.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
}

static uint32_t nvmd_encode_i(uint8_t opcode, uint8_t rd, uint8_t rs1, int32_t imm12) {
    uint32_t imm = static_cast<uint32_t>(imm12) & 0xFFFu;
    return (imm << 20)
         | ((static_cast<uint32_t>(rs1) & 0x1Fu) << 15)
         | ((static_cast<uint32_t>(rd)  & 0x1Fu) << 7)
         | (static_cast<uint32_t>(opcode) & 0x7Fu);
}

static uint32_t nvmd_encode_s(uint8_t opcode, uint8_t rs2, uint8_t rs1, int32_t imm12) {
    uint32_t imm = static_cast<uint32_t>(imm12) & 0xFFFu;
    return (imm << 20)
         | ((static_cast<uint32_t>(rs2) & 0x1Fu) << 20)
         | ((static_cast<uint32_t>(rs1) & 0x1Fu) << 15)
         | (static_cast<uint32_t>(opcode) & 0x7Fu);
}

static uint32_t nvmd_load(uint8_t rd, uint8_t rs1, int32_t imm12) {
    return nvmd_encode_i(0x02, rd, rs1, imm12);
}

static uint32_t nvmd_store(uint8_t rs2, uint8_t rs1, int32_t imm12) {
    return nvmd_encode_s(0x03, rs2, rs1, imm12);
}

static void tick(Vtb_nvisc_core_v02_with_mem_domains* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

static bool expect(bool cond, const char* label) {
    std::cout << "[CORE-NONDATA] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
    return cond;
}

static void set_defaults(Vtb_nvisc_core_v02_with_mem_domains* top) {
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;
    top->imem_resp_fault_i = 0;
    top->imem_resp_fault_code_i = 0;

    top->thread_id_i = 1;
    top->branch_id_i = 0x10;
    top->state_id_i = 0x20;
    top->commit_id_i = 0x30;
    top->privilege_i = 2;
    top->aegis_policy_id_i = 0x40;

    top->lsu_base_value_i = 0;
    top->lsu_store_data_i = 0;
    top->lsu_size_bytes_i = 8;

    top->dbg_rf_we_i = 0;
    top->dbg_rf_waddr_i = 0;
    top->dbg_rf_wdata_i = 0;

    top->stall_i = 0;
    top->flush_i = 0;

    top->redirect_valid_i = 0;
    top->redirect_pc_i = 0;

    top->branch_taken_i = 0;
    top->branch_target_i = 0;

    top->trap_valid_i = 0;
    top->trap_vector_i = 0;

    top->rollback_redirect_i = 0;
    top->rollback_pc_i = 0;

    top->mem_domain_override_valid_i = 0;
    top->mem_domain_override_i = 0;
}

static void preload_reg(Vtb_nvisc_core_v02_with_mem_domains* top, uint8_t reg, uint64_t value) {
    top->dbg_rf_we_i = 1;
    top->dbg_rf_waddr_i = reg;
    top->dbg_rf_wdata_i = value;
    tick(top);

    top->dbg_rf_we_i = 0;
    top->dbg_rf_waddr_i = 0;
    top->dbg_rf_wdata_i = 0;
    tick(top);
}

static bool wait_for_store_ack(Vtb_nvisc_core_v02_with_mem_domains* top) {
    for (int i = 0; i < 20; ++i) {
        if (top->memsys_resp_valid_o && top->memsys_resp_write_ack_o) {
            return expect(true, "store ack observed");
        }
        tick(top);
    }

    return expect(false, "store ack observed");
}

static bool wait_for_load_wb(Vtb_nvisc_core_v02_with_mem_domains* top, uint64_t expected) {
    for (int i = 0; i < 24; ++i) {
        if (top->dbg_rf_r1_o == expected) {
            bool pass = true;
            pass &= expect(true, "load/writeback path active");
            pass &= expect(top->dbg_rf_r1_o == expected, "load writes expected value to r1");
            return pass;
        }
        tick(top);
    }

    return expect(false, "load writes expected value to r1");
}

static bool wait_for_domain_route(
    Vtb_nvisc_core_v02_with_mem_domains* top,
    bool expect_exec_route,
    bool expect_livehot_route,
    const char* label
) {
    for (int i = 0; i < 16; ++i) {
        if (expect_exec_route && top->dbg_exec_route_valid_o) {
            return expect(true, label);
        }
        if (expect_livehot_route && top->dbg_livehot_route_valid_o) {
            return expect(true, label);
        }
        tick(top);
    }

    return expect(false, label);
}

static bool run_domain_case(
    Vtb_nvisc_core_v02_with_mem_domains* top,
    const char* name,
    uint8_t domain,
    uint64_t base,
    uint64_t data,
    bool expect_exec_route,
    bool expect_livehot_route
) {
    std::cout << "[CORE-NONDATA] Case " << name << std::endl;

    preload_reg(top, 2, base);
    preload_reg(top, 3, data);

    top->mem_domain_override_valid_i = 1;
    top->mem_domain_override_i = domain;

    top->lsu_base_value_i = base;
    top->lsu_store_data_i = data;
    top->lsu_size_bytes_i = 8;

    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvmd_store(3, 2, 0x40);
    tick(top);

    bool pass = true;
    pass &= expect(top->fetch_valid_o == 1, "STORE fetch valid");
    pass &= expect(top->decode_class_o == 3, "STORE decode class");
    pass &= expect(top->lsu_valid_o == 1, "STORE LSU valid");

    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;

    pass &= wait_for_domain_route(
        top,
        expect_exec_route,
        expect_livehot_route,
        expect_exec_route ? "STORE routed to EXECUTION lane" : "STORE routed to LIVE/HOT lane"
    );

    pass &= wait_for_store_ack(top);
    pass &= expect(top->core_fault_o == 0, "no core fault after store");

    top->lsu_base_value_i = base;
    top->lsu_size_bytes_i = 8;

    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvmd_load(1, 2, 0x40);
    tick(top);

    pass &= expect(top->fetch_valid_o == 1, "LOAD fetch valid");
    pass &= expect(top->decode_class_o == 2, "LOAD decode class");
    pass &= expect(top->lsu_valid_o == 1, "LOAD LSU valid");

    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;

    pass &= wait_for_domain_route(
        top,
        expect_exec_route,
        expect_livehot_route,
        expect_exec_route ? "LOAD routed to EXECUTION lane" : "LOAD routed to LIVE/HOT lane"
    );

    pass &= wait_for_load_wb(top, data);
    pass &= expect(top->core_fault_o == 0, "no core fault after load");

    top->mem_domain_override_valid_i = 0;
    top->mem_domain_override_i = 0;

    return pass;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    auto* top = new Vtb_nvisc_core_v02_with_mem_domains;
    set_defaults(top);

    top->clk = 0;
    top->rst_n = 0;
    tick(top);

    bool pass = true;

    pass &= expect(top->pc_o == 0, "PC reset vector");

        top->cache_csr_valid_i = 0;
    top->cache_csr_write_i = 0;
    top->cache_csr_read_i = 0;
    top->cache_csr_addr_i = 0;
    top->cache_csr_wdata_i = 0;

top->rst_n = 1;
    tick(top);

    pass &= expect(top->pc_valid_o == 1, "PC valid after reset");

    pass &= run_domain_case(
        top,
        "EXECUTION domain",
        2,
        0x2000,
        0x123456789ABCDEF0ULL,
        true,
        false
    );

    pass &= run_domain_case(
        top,
        "LIVE/HOT domain",
        3,
        0x3000,
        0x0BADF00DCAFEBABEULL,
        false,
        true
    );

    delete top;

    if (!pass) {
        std::cerr << "[CORE-NONDATA] FAIL: non-DATA domain core integration test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-NONDATA] PASS: non-DATA domain core integration test completed." << std::endl;
    return 0;
}
