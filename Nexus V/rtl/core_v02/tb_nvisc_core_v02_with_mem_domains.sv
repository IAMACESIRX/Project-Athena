`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module tb_nvisc_core_v02_with_mem_domains #(
    parameter logic [NV_CORE_ID_W-1:0] CORE_ID_RESET = 8'd0
)(
    input  logic clk,
    input  logic rst_n,

    // Instruction memory response path into core.
    input  logic        imem_resp_valid_i,
    input  logic [31:0] imem_resp_instr_i,
    input  logic        imem_resp_fault_i,
    input  logic [15:0] imem_resp_fault_code_i,

    // Identity inputs.
    input  logic [NV_THREAD_ID_W-1:0] thread_id_i,
    input  logic [NV_BRANCH_ID_W-1:0] branch_id_i,
    input  logic [NV_STATE_ID_W-1:0]  state_id_i,
    input  logic [NV_COMMIT_ID_W-1:0] commit_id_i,
    input  nvisc_priv_e              privilege_i,
    input  logic [NV_POLICY_ID_W-1:0] aegis_policy_id_i,

    // Legacy/core bring-up inputs.
    input  logic [63:0] lsu_base_value_i,
    input  logic [63:0] lsu_store_data_i,
    input  logic [7:0]  lsu_size_bytes_i,

    // Debug register preload/write path.
    input  logic        dbg_rf_we_i,
    input  logic [4:0]  dbg_rf_waddr_i,
    input  logic [63:0] dbg_rf_wdata_i,

    // Core control inputs.
    input  logic stall_i,
    input  logic flush_i,

    input  logic redirect_valid_i,
    input  logic [63:0] redirect_pc_i,

    input  logic branch_taken_i,
    input  logic [63:0] branch_target_i,

    input  logic trap_valid_i,
    input  logic [63:0] trap_vector_i,

    input  logic rollback_redirect_i,
    input  logic [63:0] rollback_pc_i,

    // Optional memory-domain override for integration testing and future
    // domain-select instruction plumbing.
    input  logic        mem_domain_override_valid_i,
    input  logic [2:0]  mem_domain_override_i,

    // Memory-domain CSR access.
    input  logic        memdom_csr_valid_i,
    input  logic        memdom_csr_write_i,
    input  logic        memdom_csr_read_i,
    input  logic [11:0] memdom_csr_addr_i,
    input  logic [63:0] memdom_csr_wdata_i,

    output logic        memdom_csr_resp_valid_o,
    output logic [63:0] memdom_csr_rdata_o,
    output logic        memdom_csr_fault_o,
    output logic [15:0] memdom_csr_fault_code_o,

    // Core outputs.
    output logic        imem_req_valid_o,
    output logic [63:0] imem_req_addr_o,

    output logic [63:0] pc_o,
    output logic        pc_valid_o,

    output logic        fetch_valid_o,
    output logic [31:0] fetch_instr_o,
    output logic [7:0]  decode_class_o,

    output logic [63:0] dbg_rf_r1_o,
    output logic [63:0] dbg_rf_r2_o,
    output logic [63:0] dbg_rf_r3_o,

    output logic        alu_result_valid_o,
    output logic [63:0] alu_result_o,
    output logic        alu_zero_o,
    output logic        alu_negative_o,
    output logic        alu_overflow_o,

    output logic        branch_taken_internal_o,
    output logic [63:0] branch_target_internal_o,

    output logic        alu_valid_o,
    output logic        lsu_valid_o,
    output logic        csr_valid_o,
    output logic        branch_valid_o,

    // Core translated memory request debug.
    output logic        mem_req_valid_o,
    output logic        mem_req_is_read_o,
    output logic        mem_req_is_write_o,
    output logic [63:0] mem_req_vaddr_o,
    output logic [63:0] mem_req_paddr_o,
    output logic [63:0] mem_req_wdata_o,
    output logic [7:0]  mem_req_size_bytes_o,
    output logic [2:0]  mem_req_domain_o,

    // Memory-domain subsystem debug.
    output logic        memsys_resp_valid_o,
    output logic [63:0] memsys_resp_rdata_o,
    output logic        memsys_resp_write_ack_o,
    output logic        memsys_fault_o,
    output logic [15:0] memsys_fault_code_o,

    output logic        dbg_data_route_valid_o,
    output logic        dbg_exec_route_valid_o,
    output logic        dbg_livehot_route_valid_o,

    output logic        load_wb_valid_o,
    output logic [63:0] load_wb_data_o,

    output logic        core_fault_o,
    output logic [15:0] core_fault_code_o
);

    // Core translated memory request wires.
    logic        core_mem_req_valid_w;
    logic        core_mem_req_is_read_w;
    logic        core_mem_req_is_write_w;
    logic [63:0] core_mem_req_vaddr_w;
    logic [63:0] core_mem_req_paddr_w;
    logic [63:0] core_mem_req_wdata_w;
    logic [7:0]  core_mem_req_size_bytes_w;
    logic [2:0]  core_mem_req_domain_w;
    logic [2:0]  wrapper_override_domain_w;
    logic [2:0]  csr_effective_mem_domain_w;
    logic [2:0]  effective_mem_req_domain_w;

    assign wrapper_override_domain_w =
        mem_domain_override_valid_i ? mem_domain_override_i : core_mem_req_domain_w;

    // CSR-controlled domain selection is architectural. The legacy wrapper
    // override remains available for older tests but feeds the bridge as the
    // "core-selected" domain.
    assign effective_mem_req_domain_w = csr_effective_mem_domain_w;

    // Memory subsystem response into core.
    logic        memsys_resp_valid_w;
    logic [63:0] memsys_resp_rdata_w;
    logic        memsys_resp_write_ack_w;
    logic        memsys_fault_w;
    logic [15:0] memsys_fault_code_w;

    nvisc_mem_domain_csr_bridge u_memdom_csr (
        .clk(clk),
        .rst_n(rst_n),

        .csr_valid_i(memdom_csr_valid_i),
        .csr_write_i(memdom_csr_write_i),
        .csr_read_i(memdom_csr_read_i),
        .csr_addr_i(memdom_csr_addr_i),
        .csr_wdata_i(memdom_csr_wdata_i),

        .csr_resp_valid_o(memdom_csr_resp_valid_o),
        .csr_rdata_o(memdom_csr_rdata_o),
        .csr_fault_o(memdom_csr_fault_o),
        .csr_fault_code_o(memdom_csr_fault_code_o),

        .core_mem_domain_i(wrapper_override_domain_w),

        .mem_domain_override_enable_o(),
        .mem_domain_select_o(),
        .effective_mem_domain_o(csr_effective_mem_domain_w),

        .dbg_csr_write_o(),
        .dbg_csr_read_o()
    );

    tb_nvisc_memory_domain_subsystem u_memsys (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(core_mem_req_valid_w),
        .req_is_read_i(core_mem_req_is_read_w),
        .req_is_write_i(core_mem_req_is_write_w),
        .req_paddr_i(core_mem_req_paddr_w),
        .req_wdata_i(core_mem_req_wdata_w),
        .req_size_bytes_i(core_mem_req_size_bytes_w),
        .req_mem_domain_i(nvisc_mem_domain_e'(effective_mem_req_domain_w)),
        .req_id_i('0),

        .resp_valid_o(memsys_resp_valid_w),
        .resp_rdata_o(memsys_resp_rdata_w),
        .resp_write_ack_o(memsys_resp_write_ack_w),
        .fault_o(memsys_fault_w),
        .fault_code_o(memsys_fault_code_w),

        .flush_data_l1d_i(1'b0),
        .flush_data_3d_i(1'b0),

        .cache_csr_valid_i(cache_csr_valid_i),
        .cache_csr_write_i(cache_csr_write_i),
        .cache_csr_read_i(cache_csr_read_i),
        .cache_csr_addr_i(cache_csr_addr_i),
        .cache_csr_wdata_i(cache_csr_wdata_i),
        .cache_csr_resp_valid_o(cache_csr_resp_valid_o),
        .cache_csr_rdata_o(cache_csr_rdata_o),
        .cache_csr_fault_o(cache_csr_fault_o),
        .cache_csr_fault_code_o(cache_csr_fault_code_o),

        .dbg_data_route_valid_o(dbg_data_route_valid_o),
        .dbg_exec_route_valid_o(dbg_exec_route_valid_o),
        .dbg_livehot_route_valid_o(dbg_livehot_route_valid_o),
        .dbg_router_fault_o(),
        .dbg_router_fault_code_o(),

        .dbg_data_resp_valid_o(),
        .dbg_data_resp_rdata_o(),
        .dbg_data_write_ack_o(),

        .dbg_exec_resp_valid_o(),
        .dbg_exec_resp_rdata_o(),
        .dbg_exec_write_ack_o(),

        .dbg_livehot_resp_valid_o(),
        .dbg_livehot_resp_rdata_o(),
        .dbg_livehot_write_ack_o()
    );

    nvisc_core_v02 #(
        .CORE_ID_RESET(CORE_ID_RESET)
    ) u_core (
        .clk(clk),
        .rst_n(rst_n),

        .imem_resp_valid_i(imem_resp_valid_i),
        .imem_resp_instr_i(imem_resp_instr_i),
        .imem_resp_fault_i(imem_resp_fault_i),
        .imem_resp_fault_code_i(imem_resp_fault_code_i),

        .dmem_resp_valid_i(memsys_resp_valid_w),
        .dmem_resp_rdata_i(memsys_resp_rdata_w),
        .dmem_resp_fault_i(memsys_fault_w),
        .dmem_resp_fault_code_i(memsys_fault_code_w),

        .thread_id_i(thread_id_i),
        .branch_id_i(branch_id_i),
        .state_id_i(state_id_i),
        .commit_id_i(commit_id_i),
        .privilege_i(privilege_i),
        .aegis_policy_id_i(aegis_policy_id_i),

        .lsu_base_value_i(lsu_base_value_i),
        .lsu_store_data_i(lsu_store_data_i),
        .lsu_size_bytes_i(lsu_size_bytes_i),

        .dbg_rf_we_i(dbg_rf_we_i),
        .dbg_rf_waddr_i(dbg_rf_waddr_i),
        .dbg_rf_wdata_i(dbg_rf_wdata_i),

        .stall_i(stall_i),
        .flush_i(flush_i),

        .redirect_valid_i(redirect_valid_i),
        .redirect_pc_i(redirect_pc_i),

        .branch_taken_i(branch_taken_i),
        .branch_target_i(branch_target_i),

        .trap_valid_i(trap_valid_i),
        .trap_vector_i(trap_vector_i),

        .rollback_redirect_i(rollback_redirect_i),
        .rollback_pc_i(rollback_pc_i),

        .imem_req_valid_o(imem_req_valid_o),
        .imem_req_addr_o(imem_req_addr_o),

        .mem_req_valid_o(core_mem_req_valid_w),
        .mem_req_is_read_o(core_mem_req_is_read_w),
        .mem_req_is_write_o(core_mem_req_is_write_w),
        .mem_req_vaddr_o(core_mem_req_vaddr_w),
        .mem_req_paddr_o(core_mem_req_paddr_w),
        .mem_req_wdata_o(core_mem_req_wdata_w),
        .mem_req_size_bytes_o(core_mem_req_size_bytes_w),
        .mem_req_domain_o(core_mem_req_domain_w),

        .load_wb_valid_o(load_wb_valid_o),
        .load_wb_data_o(load_wb_data_o),

        .pc_o(pc_o),
        .pc_valid_o(pc_valid_o),
        .fetch_valid_o(fetch_valid_o),
        .fetch_instr_o(fetch_instr_o),
        .decode_class_o(decode_class_o),

        .dbg_rf_r1_o(dbg_rf_r1_o),
        .dbg_rf_r2_o(dbg_rf_r2_o),
        .dbg_rf_r3_o(dbg_rf_r3_o),

        .alu_result_valid_o(alu_result_valid_o),
        .alu_result_o(alu_result_o),
        .alu_zero_o(alu_zero_o),
        .alu_negative_o(alu_negative_o),
        .alu_overflow_o(alu_overflow_o),

        .branch_taken_internal_o(branch_taken_internal_o),
        .branch_target_internal_o(branch_target_internal_o),

        .alu_valid_o(alu_valid_o),
        .lsu_valid_o(lsu_valid_o),
        .csr_valid_o(csr_valid_o),
        .branch_valid_o(branch_valid_o),

        .core_fault_o(core_fault_o),
        .core_fault_code_o(core_fault_code_o)
    );

    assign mem_req_valid_o      = core_mem_req_valid_w;
    assign mem_req_is_read_o    = core_mem_req_is_read_w;
    assign mem_req_is_write_o   = core_mem_req_is_write_w;
    assign mem_req_vaddr_o      = core_mem_req_vaddr_w;
    assign mem_req_paddr_o      = core_mem_req_paddr_w;
    assign mem_req_wdata_o      = core_mem_req_wdata_w;
    assign mem_req_size_bytes_o = core_mem_req_size_bytes_w;
    assign mem_req_domain_o     = core_mem_req_domain_w;

    assign memsys_resp_valid_o     = memsys_resp_valid_w;
    assign memsys_resp_rdata_o     = memsys_resp_rdata_w;
    assign memsys_resp_write_ack_o = memsys_resp_write_ack_w;
    assign memsys_fault_o          = memsys_fault_w;
    assign memsys_fault_code_o     = memsys_fault_code_w;

endmodule
