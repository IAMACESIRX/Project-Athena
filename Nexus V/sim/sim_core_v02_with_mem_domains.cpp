#include "Vtb_nvisc_core_v02_with_mem_domains.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include "nvisc_instr_encode.hpp"

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


static vluint64_t main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(main_time);
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
    std::cout << "[CORE-MEMDOM] " << label << " -> " << (cond ? "PASS" : "FAIL") << std::endl;
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

static bool wait_for_store_request(
    Vtb_nvisc_core_v02_with_mem_domains* top,
    uint64_t expected_paddr
) {
    bool saw_req = false;
    bool saw_write = false;
    bool saw_paddr = false;
    bool saw_data_route = false;

    for (int i = 0; i < 12; ++i) {
        if (top->mem_req_valid_o) {
            saw_req = true;
            if (top->mem_req_is_write_o) {
                saw_write = true;
            }
            if (top->mem_req_paddr_o == expected_paddr) {
                saw_paddr = true;
            }
        }

        if (top->dbg_data_route_valid_o) {
            saw_data_route = true;
        }

        if (saw_req && saw_write && saw_paddr && saw_data_route) {
            bool pass = true;
            pass &= expect(true, "STORE translated request valid");
            pass &= expect(true, "STORE translated request write");
            pass &= expect(true, "STORE translated paddr");
            pass &= expect(true, "STORE routed to DATA lane");
            return pass;
        }

        tick(top);
    }

    bool pass = true;
    pass &= expect(saw_req, "STORE translated request valid");
    pass &= expect(saw_write, "STORE translated request write");
    pass &= expect(saw_paddr, "STORE translated paddr");
    pass &= expect(saw_data_route, "STORE routed to DATA lane");
    return pass;
}

static bool wait_for_load_request(
    Vtb_nvisc_core_v02_with_mem_domains* top,
    uint64_t expected_paddr
) {
    bool saw_req = false;
    bool saw_read = false;
    bool saw_paddr = false;
    bool saw_data_route = false;

    for (int i = 0; i < 12; ++i) {
        if (top->mem_req_valid_o) {
            saw_req = true;
            if (top->mem_req_is_read_o) {
                saw_read = true;
            }
            if (top->mem_req_paddr_o == expected_paddr) {
                saw_paddr = true;
            }
        }

        if (top->dbg_data_route_valid_o) {
            saw_data_route = true;
        }

        if (saw_req && saw_read && saw_paddr && saw_data_route) {
            bool pass = true;
            pass &= expect(true, "LOAD translated request valid");
            pass &= expect(true, "LOAD translated request read");
            pass &= expect(true, "LOAD translated paddr");
            pass &= expect(true, "LOAD routed to DATA lane");
            return pass;
        }

        tick(top);
    }

    bool pass = true;
    pass &= expect(saw_req, "LOAD translated request valid");
    pass &= expect(saw_read, "LOAD translated request read");
    pass &= expect(saw_paddr, "LOAD translated paddr");
    pass &= expect(saw_data_route, "LOAD routed to DATA lane");
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

    // Prepare base/data registers used by current LOAD/STORE path.
    preload_reg(top, 2, 0x0000000080000000ULL);
    preload_reg(top, 3, 0xA5A55A5ADEADBEEFULL);

    pass &= expect(top->dbg_rf_r2_o == 0x0000000080000000ULL, "preload r2 DRAM base");
    pass &= expect(top->dbg_rf_r3_o == 0xA5A55A5ADEADBEEFULL, "preload r3 store data");

    // STORE r3 -> [r2 + 0x40], DATA domain by current decoder.
    top->lsu_base_value_i = 0x0000000080000000ULL;
    top->lsu_store_data_i = 0xA5A55A5ADEADBEEFULL;
    top->lsu_size_bytes_i = 8;
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvmd_store(3, 2, 0x40);
    tick(top);

    std::cout << "[CORE-MEMDOM] Case STORE through memory-domain subsystem" << std::endl;
    pass &= expect(top->fetch_valid_o == 1, "STORE fetch valid");
    pass &= expect(top->decode_class_o == 3, "STORE decode class");
    pass &= expect(top->lsu_valid_o == 1, "STORE LSU valid");
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;

    pass &= wait_for_store_request(top, 0x0000000080000040ULL);

    bool saw_store_resp = false;
    bool saw_store_ack = false;

    for (int i = 0; i < 96; ++i) {
        if (top->memsys_resp_valid_o) {
            saw_store_resp = true;
        }
        if (top->memsys_resp_valid_o && top->memsys_resp_write_ack_o) {
            saw_store_ack = true;
            break;
        }
        tick(top);
    }

    pass &= expect(saw_store_resp, "STORE memsys response valid");
    pass &= expect(saw_store_ack, "STORE memsys write ack");
    pass &= expect(top->core_fault_o == 0, "no core fault after STORE");

    // LOAD r1 <- [r2 + 0x40], DATA domain by current decoder.
    top->lsu_base_value_i = 0x0000000080000000ULL;
    top->lsu_size_bytes_i = 8;
    top->imem_resp_valid_i = 1;
    top->imem_resp_instr_i = nvmd_load(1, 2, 0x40);
    tick(top);

    std::cout << "[CORE-MEMDOM] Case LOAD through memory-domain subsystem" << std::endl;
    pass &= expect(top->fetch_valid_o == 1, "LOAD fetch valid");
    pass &= expect(top->decode_class_o == 2, "LOAD decode class");
    pass &= expect(top->lsu_valid_o == 1, "LOAD LSU valid");
    top->imem_resp_valid_i = 0;
    top->imem_resp_instr_i = 0;

    pass &= wait_for_load_request(top, 0x0000000080000040ULL);

    bool saw_load_resp = false;
    bool saw_load_data = false;
    bool saw_load_wb = false;
    bool saw_r1_value = false;

    for (int i = 0; i < 128; ++i) {
        if (top->memsys_resp_valid_o) {
            saw_load_resp = true;
            if (top->memsys_resp_rdata_o == 0xA5A55A5ADEADBEEFULL) {
                saw_load_data = true;
            }
        }

        if (top->load_wb_valid_o) {
            saw_load_wb = true;
        }

        if (top->dbg_rf_r1_o == 0xA5A55A5ADEADBEEFULL) {
            saw_r1_value = true;
            break;
        }

        tick(top);
    }

    pass &= expect(saw_load_resp, "LOAD memsys response valid");
    pass &= expect(saw_load_data, "LOAD memsys response data");
    pass &= expect(saw_load_wb || saw_r1_value, "LOAD writeback observed");
    pass &= expect(saw_r1_value, "LOAD writes r1 from memory-domain subsystem");
    pass &= expect(top->core_fault_o == 0, "no core fault after LOAD");

    delete top;

    if (!pass) {
        std::cerr << "[CORE-MEMDOM] FAIL: core memory-domain integration test failed." << std::endl;
        return 1;
    }

    std::cout << "[CORE-MEMDOM] PASS: core memory-domain integration test completed." << std::endl;
    return 0;
}
