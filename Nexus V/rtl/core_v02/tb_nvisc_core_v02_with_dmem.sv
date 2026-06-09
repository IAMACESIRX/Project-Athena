`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module tb_nvisc_core_v02_with_dmem #(
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

    // Legacy/core bring-up inputs still present on nvisc_core_v02.
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

    // Instruction memory request from core.
    output logic        imem_req_valid_o,
    output logic [63:0] imem_req_addr_o,

    // Translated memory request view from core.
    output logic        mem_req_valid_o,
    output logic        mem_req_is_read_o,
    output logic        mem_req_is_write_o,
    output logic [63:0] mem_req_vaddr_o,
    output logic [63:0] mem_req_paddr_o,
    output logic [63:0] mem_req_wdata_o,
    output logic [7:0]  mem_req_size_bytes_o,
    output logic [2:0]  mem_req_domain_o,

    // DMEM response/debug view.
    output logic        dmem_resp_valid_o,
    output logic [63:0] dmem_resp_rdata_o,
    output logic        dmem_resp_write_ack_o,
    output logic        dmem_fault_o,
    output logic [15:0] dmem_fault_code_o,

    // Core-visible status/debug.
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

    // L1D backing memory request wires into DMEM.
    logic        l1d_mem_req_valid_w;
    logic        l1d_mem_req_is_read_w;
    logic        l1d_mem_req_is_write_w;
    logic [63:0] l1d_mem_req_paddr_w;
    logic [63:0] l1d_mem_req_wdata_w;
    logic [7:0]  l1d_mem_req_size_bytes_w;
    nvisc_mem_domain_e l1d_mem_req_domain_w;
    nvisc_exec_identity_t l1d_mem_req_id_w;

    // DMEM response wires.
    logic        dmem_resp_valid_w;
    logic [63:0] dmem_resp_rdata_w;
    logic        dmem_resp_write_ack_w;
    logic        dmem_fault_w;
    logic [15:0] dmem_fault_code_w;

    // L1D response wires back into core.
    logic        l1d_core_resp_valid_w;
    logic [63:0] l1d_core_resp_rdata_w;
    logic        l1d_core_resp_write_ack_w;
    logic        l1d_core_fault_w;
    logic [15:0] l1d_core_fault_code_w;

    nvisc_core_v02 #(
        .CORE_ID_RESET(CORE_ID_RESET)
    ) u_core (
        .clk(clk),
        .rst_n(rst_n),

        .imem_resp_valid_i(imem_resp_valid_i),
        .imem_resp_instr_i(imem_resp_instr_i),
        .imem_resp_fault_i(imem_resp_fault_i),
        .imem_resp_fault_code_i(imem_resp_fault_code_i),

        .dmem_resp_valid_i(l1d_core_resp_valid_w),
        .dmem_resp_rdata_i(l1d_core_resp_rdata_w),
        .dmem_resp_fault_i(l1d_core_fault_w),
        .dmem_resp_fault_code_i(l1d_core_fault_code_w),

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

    nvisc_l1d_cache_stub u_l1d (
        .clk(clk),
        .rst_n(rst_n),

        .flush_i(1'b0),

        .core_req_valid_i(core_mem_req_valid_w),
        .core_req_is_read_i(core_mem_req_is_read_w),
        .core_req_is_write_i(core_mem_req_is_write_w),
        .core_req_paddr_i(core_mem_req_paddr_w),
        .core_req_wdata_i(core_mem_req_wdata_w),
        .core_req_size_bytes_i(core_mem_req_size_bytes_w),
        .core_req_mem_domain_i(nvisc_mem_domain_e'(core_mem_req_domain_w)),
        .core_req_id_i('0),

        .core_resp_valid_o(l1d_core_resp_valid_w),
        .core_resp_rdata_o(l1d_core_resp_rdata_w),
        .core_resp_write_ack_o(l1d_core_resp_write_ack_w),
        .core_fault_o(l1d_core_fault_w),
        .core_fault_code_o(l1d_core_fault_code_w),

        .mem_req_valid_o(l1d_mem_req_valid_w),
        .mem_req_is_read_o(l1d_mem_req_is_read_w),
        .mem_req_is_write_o(l1d_mem_req_is_write_w),
        .mem_req_paddr_o(l1d_mem_req_paddr_w),
        .mem_req_wdata_o(l1d_mem_req_wdata_w),
        .mem_req_size_bytes_o(l1d_mem_req_size_bytes_w),
        .mem_req_mem_domain_o(l1d_mem_req_domain_w),
        .mem_req_id_o(l1d_mem_req_id_w),

        .mem_resp_valid_i(dmem_resp_valid_w),
        .mem_resp_rdata_i(dmem_resp_rdata_w),
        .mem_resp_write_ack_i(dmem_resp_write_ack_w),
        .mem_fault_i(dmem_fault_w),
        .mem_fault_code_i(dmem_fault_code_w),

        .dbg_hit_o(),
        .dbg_miss_o(),
        .dbg_fill_o(),
        .dbg_cached_data_o()
    );



    nvisc_dmem_controller_stub #(
        .MEM_WORDS(256),
        .BASE_ADDR(64'h0000_0000_0000_1000)
    ) u_dmem (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(l1d_mem_req_valid_w),
        .req_is_read_i(l1d_mem_req_is_read_w),
        .req_is_write_i(l1d_mem_req_is_write_w),
        .req_paddr_i(l1d_mem_req_paddr_w),
        .req_wdata_i(l1d_mem_req_wdata_w),
        .req_size_bytes_i(l1d_mem_req_size_bytes_w),
        .req_mem_domain_i(l1d_mem_req_domain_w),
        .req_id_i(l1d_mem_req_id_w),

        .resp_valid_o(dmem_resp_valid_w),
        .resp_rdata_o(dmem_resp_rdata_w),
        .resp_write_ack_o(dmem_resp_write_ack_w),

        .fault_o(dmem_fault_w),
        .fault_code_o(dmem_fault_code_w),

        .dbg_addr_o(),
        .dbg_wdata_o(),
        .dbg_rdata_o(),
        .dbg_write_seen_o(),
        .dbg_read_seen_o()
    );

    assign mem_req_valid_o      = core_mem_req_valid_w;
    assign mem_req_is_read_o    = core_mem_req_is_read_w;
    assign mem_req_is_write_o   = core_mem_req_is_write_w;
    assign mem_req_vaddr_o      = core_mem_req_vaddr_w;
    assign mem_req_paddr_o      = core_mem_req_paddr_w;
    assign mem_req_wdata_o      = core_mem_req_wdata_w;
    assign mem_req_size_bytes_o = core_mem_req_size_bytes_w;
    assign mem_req_domain_o     = core_mem_req_domain_w;

    assign dmem_resp_valid_o    = dmem_resp_valid_w;
    assign dmem_resp_rdata_o    = dmem_resp_rdata_w;
    assign dmem_resp_write_ack_o = dmem_resp_write_ack_w;
    assign dmem_fault_o         = dmem_fault_w;
    assign dmem_fault_code_o    = dmem_fault_code_w;

endmodule
