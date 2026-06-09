`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module tb_nvisc_core_v02_with_irq #(
    parameter logic [NV_CORE_ID_W-1:0] CORE_ID_RESET = 8'd0
)(
    input  logic clk,
    input  logic rst_n,

    // Instruction memory response path into core.
    input  logic        imem_resp_valid_i,
    input  logic [31:0] imem_resp_instr_i,
    input  logic        imem_resp_fault_i,
    input  logic [15:0] imem_resp_fault_code_i,

    // IRQ/timer control.
    input  logic        global_irq_enable_i,
    input  logic        timer_enable_i,
    input  logic [63:0] timer_compare_i,
    input  logic [63:0] irq_vector_base_i,
    input  logic        external_irq_i,
    input  logic        irq_ack_i,

    // Identity inputs.
    input  logic [NV_THREAD_ID_W-1:0] thread_id_i,
    input  logic [NV_BRANCH_ID_W-1:0] branch_id_i,
    input  logic [NV_STATE_ID_W-1:0]  state_id_i,
    input  logic [NV_COMMIT_ID_W-1:0] commit_id_i,
    input  nvisc_priv_e              privilege_i,
    input  logic [NV_POLICY_ID_W-1:0] aegis_policy_id_i,

    // Core bring-up inputs.
    input  logic [63:0] lsu_base_value_i,
    input  logic [63:0] lsu_store_data_i,
    input  logic [7:0]  lsu_size_bytes_i,

    input  logic        dbg_rf_we_i,
    input  logic [4:0]  dbg_rf_waddr_i,
    input  logic [63:0] dbg_rf_wdata_i,

    input  logic stall_i,
    input  logic flush_i,

    input  logic redirect_valid_i,
    input  logic [63:0] redirect_pc_i,

    input  logic branch_taken_i,
    input  logic [63:0] branch_target_i,

    input  logic rollback_redirect_i,
    input  logic [63:0] rollback_pc_i,

    // Core outputs.
    output logic        imem_req_valid_o,
    output logic [63:0] imem_req_addr_o,

    output logic [63:0] pc_o,
    output logic        pc_valid_o,
    output logic        fetch_valid_o,
    output logic [31:0] fetch_instr_o,
    output logic [7:0]  decode_class_o,

    output logic        irq_pending_o,
    output logic        irq_taken_o,
    output logic [63:0] irq_vector_o,
    output logic [15:0] irq_code_o,
    output logic [63:0] irq_cycle_count_o,

    output logic        core_fault_o,
    output logic [15:0] core_fault_code_o
);

    logic        irq_trap_valid_w;
    logic [63:0] irq_trap_vector_w;

    // Unused core data/memory debug outputs for this IRQ wrapper.
    logic        mem_req_valid_unused;
    logic        mem_req_is_read_unused;
    logic        mem_req_is_write_unused;
    logic [63:0] mem_req_vaddr_unused;
    logic [63:0] mem_req_paddr_unused;
    logic [63:0] mem_req_wdata_unused;
    logic [7:0]  mem_req_size_bytes_unused;
    logic [2:0]  mem_req_domain_unused;

    logic        load_wb_valid_unused;
    logic [63:0] load_wb_data_unused;

    logic [63:0] dbg_rf_r1_unused;
    logic [63:0] dbg_rf_r2_unused;
    logic [63:0] dbg_rf_r3_unused;

    logic        alu_result_valid_unused;
    logic [63:0] alu_result_unused;
    logic        alu_zero_unused;
    logic        alu_negative_unused;
    logic        alu_overflow_unused;

    logic        branch_taken_internal_unused;
    logic [63:0] branch_target_internal_unused;

    logic        alu_valid_unused;
    logic        lsu_valid_unused;
    logic        csr_valid_unused;
    logic        branch_valid_unused;

    nvisc_interrupt_timer_stub u_irq_timer (
        .clk(clk),
        .rst_n(rst_n),

        .global_irq_enable_i(global_irq_enable_i),
        .timer_enable_i(timer_enable_i),
        .timer_compare_i(timer_compare_i),
        .irq_vector_base_i(irq_vector_base_i),

        .external_irq_i(external_irq_i),
        .irq_ack_i(irq_ack_i),

        .cycle_count_o(irq_cycle_count_o),
        .timer_pending_o(),
        .external_pending_o(),

        .irq_pending_o(irq_pending_o),
        .irq_taken_o(irq_taken_o),
        .irq_vector_o(irq_vector_o),
        .irq_code_o(irq_code_o),

        .dbg_timer_fire_o(),
        .dbg_external_fire_o()
    );

    assign irq_trap_valid_w  = irq_taken_o;
    assign irq_trap_vector_w = irq_vector_o;

    nvisc_core_v02 #(
        .CORE_ID_RESET(CORE_ID_RESET)
    ) u_core (
        .clk(clk),
        .rst_n(rst_n),

        .imem_resp_valid_i(imem_resp_valid_i),
        .imem_resp_instr_i(imem_resp_instr_i),
        .imem_resp_fault_i(imem_resp_fault_i),
        .imem_resp_fault_code_i(imem_resp_fault_code_i),

        .dmem_resp_valid_i(1'b0),
        .dmem_resp_rdata_i(64'd0),
        .dmem_resp_fault_i(1'b0),
        .dmem_resp_fault_code_i(16'd0),

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

        .trap_valid_i(irq_trap_valid_w),
        .trap_vector_i(irq_trap_vector_w),

        .rollback_redirect_i(rollback_redirect_i),
        .rollback_pc_i(rollback_pc_i),

        .imem_req_valid_o(imem_req_valid_o),
        .imem_req_addr_o(imem_req_addr_o),

        .mem_req_valid_o(mem_req_valid_unused),
        .mem_req_is_read_o(mem_req_is_read_unused),
        .mem_req_is_write_o(mem_req_is_write_unused),
        .mem_req_vaddr_o(mem_req_vaddr_unused),
        .mem_req_paddr_o(mem_req_paddr_unused),
        .mem_req_wdata_o(mem_req_wdata_unused),
        .mem_req_size_bytes_o(mem_req_size_bytes_unused),
        .mem_req_domain_o(mem_req_domain_unused),

        .load_wb_valid_o(load_wb_valid_unused),
        .load_wb_data_o(load_wb_data_unused),

        .pc_o(pc_o),
        .pc_valid_o(pc_valid_o),
        .fetch_valid_o(fetch_valid_o),
        .fetch_instr_o(fetch_instr_o),
        .decode_class_o(decode_class_o),

        .dbg_rf_r1_o(dbg_rf_r1_unused),
        .dbg_rf_r2_o(dbg_rf_r2_unused),
        .dbg_rf_r3_o(dbg_rf_r3_unused),

        .alu_result_valid_o(alu_result_valid_unused),
        .alu_result_o(alu_result_unused),
        .alu_zero_o(alu_zero_unused),
        .alu_negative_o(alu_negative_unused),
        .alu_overflow_o(alu_overflow_unused),

        .branch_taken_internal_o(branch_taken_internal_unused),
        .branch_target_internal_o(branch_target_internal_unused),

        .alu_valid_o(alu_valid_unused),
        .lsu_valid_o(lsu_valid_unused),
        .csr_valid_o(csr_valid_unused),
        .branch_valid_o(branch_valid_unused),

        .core_fault_o(core_fault_o),
        .core_fault_code_o(core_fault_code_o)
    );

endmodule
