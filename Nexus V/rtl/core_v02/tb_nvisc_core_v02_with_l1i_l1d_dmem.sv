`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module tb_nvisc_core_v02_with_l1i_l1d_dmem #(
    parameter logic [NV_CORE_ID_W-1:0] CORE_ID_RESET = 8'd0
)(
    input  logic clk,
    input  logic rst_n,

    // Backing instruction memory response into L1I.
    input  logic        backing_imem_resp_valid_i,
    input  logic [31:0] backing_imem_resp_instr_i,
    input  logic        backing_imem_resp_fault_i,
    input  logic [15:0] backing_imem_resp_fault_code_i,

    // Backing instruction memory request from L1I.
    output logic        backing_imem_req_valid_o,
    output logic [63:0] backing_imem_req_addr_o,

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

    // Core/status outputs.
    output logic [63:0] pc_o,
    output logic        pc_valid_o,

    output logic        fetch_valid_o,
    output logic [31:0] fetch_instr_o,
    output logic [7:0]  decode_class_o,

    output logic        imem_req_valid_o,
    output logic [63:0] imem_req_addr_o,

    output logic        l1i_hit_o,
    output logic        l1i_miss_o,
    output logic        l1i_fill_o,
    output logic [31:0] l1i_cached_instr_o,

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

    output logic        mem_req_valid_o,
    output logic        mem_req_is_read_o,
    output logic        mem_req_is_write_o,
    output logic [63:0] mem_req_vaddr_o,
    output logic [63:0] mem_req_paddr_o,
    output logic [63:0] mem_req_wdata_o,
    output logic [7:0]  mem_req_size_bytes_o,
    output logic [2:0]  mem_req_domain_o,

    output logic        dmem_resp_valid_o,
    output logic [63:0] dmem_resp_rdata_o,
    output logic        dmem_resp_write_ack_o,
    output logic        dmem_fault_o,
    output logic [15:0] dmem_fault_code_o,

    output logic        load_wb_valid_o,
    output logic [63:0] load_wb_data_o,

    output logic        core_fault_o,
    output logic [15:0] core_fault_code_o
);

    // Core instruction request from existing core+data wrapper.
    logic        core_imem_req_valid_w;
    logic [63:0] core_imem_req_addr_w;

    // L1I response into existing core+data wrapper.
    logic        l1i_fetch_resp_valid_w;
    logic [31:0] l1i_fetch_resp_instr_w;
    logic        l1i_fetch_resp_fault_w;
    logic [15:0] l1i_fetch_resp_fault_code_w;

    tb_nvisc_core_v02_with_dmem #(
        .CORE_ID_RESET(CORE_ID_RESET)
    ) u_core_data (
        .clk(clk),
        .rst_n(rst_n),

        .imem_resp_valid_i(l1i_fetch_resp_valid_w),
        .imem_resp_instr_i(l1i_fetch_resp_instr_w),
        .imem_resp_fault_i(l1i_fetch_resp_fault_w),
        .imem_resp_fault_code_i(l1i_fetch_resp_fault_code_w),

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

        .imem_req_valid_o(core_imem_req_valid_w),
        .imem_req_addr_o(core_imem_req_addr_w),

        .mem_req_valid_o(mem_req_valid_o),
        .mem_req_is_read_o(mem_req_is_read_o),
        .mem_req_is_write_o(mem_req_is_write_o),
        .mem_req_vaddr_o(mem_req_vaddr_o),
        .mem_req_paddr_o(mem_req_paddr_o),
        .mem_req_wdata_o(mem_req_wdata_o),
        .mem_req_size_bytes_o(mem_req_size_bytes_o),
        .mem_req_domain_o(mem_req_domain_o),

        .dmem_resp_valid_o(dmem_resp_valid_o),
        .dmem_resp_rdata_o(dmem_resp_rdata_o),
        .dmem_resp_write_ack_o(dmem_resp_write_ack_o),
        .dmem_fault_o(dmem_fault_o),
        .dmem_fault_code_o(dmem_fault_code_o),

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

        .load_wb_valid_o(load_wb_valid_o),
        .load_wb_data_o(load_wb_data_o),

        .core_fault_o(core_fault_o),
        .core_fault_code_o(core_fault_code_o)
    );

    nvisc_l1i_cache_stub u_l1i (
        .clk(clk),
        .rst_n(rst_n),

        .fetch_req_valid_i(core_imem_req_valid_w),
        .fetch_req_addr_i(core_imem_req_addr_w),
        .flush_i(flush_i),

        .fetch_resp_valid_o(l1i_fetch_resp_valid_w),
        .fetch_resp_instr_o(l1i_fetch_resp_instr_w),
        .fetch_resp_fault_o(l1i_fetch_resp_fault_w),
        .fetch_resp_fault_code_o(l1i_fetch_resp_fault_code_w),

        .imem_req_valid_o(backing_imem_req_valid_o),
        .imem_req_addr_o(backing_imem_req_addr_o),

        .imem_resp_valid_i(backing_imem_resp_valid_i),
        .imem_resp_instr_i(backing_imem_resp_instr_i),
        .imem_resp_fault_i(backing_imem_resp_fault_i),
        .imem_resp_fault_code_i(backing_imem_resp_fault_code_i),

        .dbg_hit_o(l1i_hit_o),
        .dbg_miss_o(l1i_miss_o),
        .dbg_fill_o(l1i_fill_o),
        .dbg_cached_instr_o(l1i_cached_instr_o)
    );

    assign imem_req_valid_o = core_imem_req_valid_w;
    assign imem_req_addr_o  = core_imem_req_addr_w;

endmodule
