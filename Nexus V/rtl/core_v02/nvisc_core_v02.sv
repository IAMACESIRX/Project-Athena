`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_core_v02 #(
    parameter logic [NV_CORE_ID_W-1:0] CORE_ID_RESET = 8'd0
)(
    input  logic clk,
    input  logic rst_n,

    // Simple instruction memory response path for bring-up.
    input  logic        imem_resp_valid_i,
    input  logic [31:0] imem_resp_instr_i,
    input  logic        imem_resp_fault_i,
    input  logic [15:0] imem_resp_fault_code_i,

    // Simple data memory response path for LOAD writeback bring-up.
    input  logic        dmem_resp_valid_i,
    input  logic [63:0] dmem_resp_rdata_i,
    input  logic        dmem_resp_fault_i,
    input  logic [15:0] dmem_resp_fault_code_i,

    // Live Nexus-V identity inputs.
    input  logic [NV_THREAD_ID_W-1:0] thread_id_i,
    input  logic [NV_BRANCH_ID_W-1:0] branch_id_i,
    input  logic [NV_STATE_ID_W-1:0]  state_id_i,
    input  logic [NV_COMMIT_ID_W-1:0] commit_id_i,
    input  nvisc_priv_e              privilege_i,
    input  logic [NV_POLICY_ID_W-1:0] aegis_policy_id_i,

    // LSU operand inputs for bring-up.
    // Later these come from the register file / execute stage.
    input  logic [63:0] lsu_base_value_i,
    input  logic [63:0] lsu_store_data_i,
    input  logic [7:0]  lsu_size_bytes_i,

    // Debug register preload/write path for bring-up.
    input  logic        dbg_rf_we_i,
    input  logic [4:0]  dbg_rf_waddr_i,
    input  logic [63:0] dbg_rf_wdata_i,

    // Simple control inputs.
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

    // Instruction memory request.
    output logic        imem_req_valid_o,
    output logic [63:0] imem_req_addr_o,

    // LSU memory request debug mirrors.
    output logic        mem_req_valid_o,
    output logic        mem_req_is_read_o,
    output logic        mem_req_is_write_o,
    output logic [63:0] mem_req_vaddr_o,
    output logic [63:0] mem_req_paddr_o,
    output logic [63:0] mem_req_wdata_o,
    output logic [7:0]  mem_req_size_bytes_o,
    output logic [2:0]  mem_req_domain_o,

    // LOAD response/writeback debug.
    output logic        load_wb_valid_o,
    output logic [63:0] load_wb_data_o,

    // Core-visible status.
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

    output logic        core_fault_o,
    output logic [15:0] core_fault_code_o
);

    // -------------------------------------------------------------------------
    // Internal wires
    // -------------------------------------------------------------------------
    logic [63:0] pc_w;
    logic        pc_valid_w;

    nvisc_exec_identity_t csr_identity_w;
    nvisc_fetch_packet_t  fetch_packet_w;
    nvisc_decode_packet_t decode_packet_w;
    nvisc_mem_req_t       lsu_mem_req_w;

    logic        mmu_resp_valid_w;
    logic        mmu_resp_is_read_w;
    logic        mmu_resp_is_write_w;
    logic [63:0] mmu_resp_vaddr_w;
    logic [63:0] mmu_resp_paddr_w;
    logic [63:0] mmu_resp_wdata_w;
    logic [7:0]  mmu_resp_size_bytes_w;
    nvisc_mem_domain_e mmu_resp_mem_domain_w;
    nvisc_exec_identity_t mmu_resp_id_w;

    logic        mmu_fault_w;
    logic [15:0] mmu_fault_code_w;

    logic [63:0] rs1_data_w;
    logic [63:0] rs2_data_w;

    logic        alu_fault_w;
    logic [15:0] alu_fault_code_w;

    logic        branch_fault_w;
    logic [15:0] branch_fault_code_w;
    logic        branch_taken_w;
    logic [63:0] branch_target_w;
    logic        pc_branch_taken_mux_w;
    logic [63:0] pc_branch_target_mux_w;

    logic        rf_we_w;
    logic [4:0]  rf_waddr_w;
    logic [63:0] rf_wdata_w;

    logic        load_pending_q;
    logic [4:0]  load_rd_q;
    logic        dmem_fault_w;
    logic [15:0] dmem_fault_code_w;

    logic fetch_fault_w;
    logic [15:0] fetch_fault_code_w;

    nvisc_alu_op_e ctrl_alu_op_w;

    logic ctrl_reg_write_w;
    logic ctrl_mem_read_w;
    logic ctrl_mem_write_w;
    logic ctrl_csr_read_w;
    logic ctrl_csr_write_w;
    logic ctrl_illegal_w;
    logic ctrl_trap_w;
    logic [15:0] ctrl_trap_code_w;

    logic [4:0] ctrl_rd_w;
    logic [4:0] ctrl_rs1_w;
    logic [4:0] ctrl_rs2_w;
    logic [63:0] ctrl_imm_w;

    nvisc_mem_domain_e ctrl_mem_domain_w;
    nvisc_exec_identity_t ctrl_identity_w;

    logic lsu_fault_w;
    logic [15:0] lsu_fault_code_w;

    logic [63:0] csr_rdata_unused;
    logic csr_rvalid_unused;
    logic csr_fault_w;
    logic [15:0] csr_fault_code_w;

    // -------------------------------------------------------------------------
    // CSR identity source
    // -------------------------------------------------------------------------
    nvisc_csr_file #(
        .CORE_ID_RESET(CORE_ID_RESET)
    ) u_csr (
        .clk(clk),
        .rst_n(rst_n),

        .csr_valid_i(1'b0),
        .csr_read_i(1'b0),
        .csr_write_i(1'b0),
        .csr_addr_i(12'd0),
        .csr_wdata_i(64'd0),

        .thread_id_i(thread_id_i),
        .branch_id_i(branch_id_i),
        .state_id_i(state_id_i),
        .commit_id_i(commit_id_i),
        .privilege_i(privilege_i),
        .aegis_policy_id_i(aegis_policy_id_i),

        .csr_rdata_o(csr_rdata_unused),
        .csr_rvalid_o(csr_rvalid_unused),
        .csr_fault_o(csr_fault_w),
        .csr_fault_code_o(csr_fault_code_w),

        .id_o(csr_identity_w),

        .dbg_core_id_o(),
        .dbg_thread_id_o(),
        .dbg_branch_id_o(),
        .dbg_state_id_o(),
        .dbg_commit_id_o(),
        .dbg_privilege_o(),
        .dbg_aegis_policy_id_o(),
        .dbg_status_o()
    );

    // -------------------------------------------------------------------------
    // External/internal branch redirect mux
    // -------------------------------------------------------------------------
    always_comb begin
        pc_branch_taken_mux_w  = branch_taken_i;
        pc_branch_target_mux_w = branch_target_i;

        // Internal decoded branch has priority for this core-local path.
        if (branch_taken_w) begin
            pc_branch_taken_mux_w  = 1'b1;
            pc_branch_target_mux_w = branch_target_w;
        end
    end

    // -------------------------------------------------------------------------
    // PC / branch unit
    // -------------------------------------------------------------------------
    nvisc_pc_branch_unit u_pc (
        .clk(clk),
        .rst_n(rst_n),

        .stall_i(stall_i),

        .redirect_valid_i(redirect_valid_i),
        .redirect_pc_i(redirect_pc_i),

        .branch_taken_i(pc_branch_taken_mux_w),
        .branch_target_i(pc_branch_target_mux_w),

        .trap_valid_i(trap_valid_i),
        .trap_vector_i(trap_vector_i),

        .rollback_redirect_i(rollback_redirect_i),
        .rollback_pc_i(rollback_pc_i),

        .pc_o(pc_w),
        .pc_valid_o(pc_valid_w)
    );

    // -------------------------------------------------------------------------
    // Instruction fetch
    // -------------------------------------------------------------------------
    nvisc_instruction_fetch_unit u_if (
        .clk(clk),
        .rst_n(rst_n),

        .stall_i(stall_i),
        .flush_i(flush_i),

        .pc_i(pc_w),
        .pc_valid_i(pc_valid_w),
        .id_i(csr_identity_w),

        .imem_req_valid_o(imem_req_valid_o),
        .imem_req_addr_o(imem_req_addr_o),
        .imem_req_id_o(),

        .imem_resp_valid_i(imem_resp_valid_i),
        .imem_resp_instr_i(imem_resp_instr_i),
        .imem_resp_fault_i(imem_resp_fault_i),
        .imem_resp_fault_code_i(imem_resp_fault_code_i),

        .fetch_packet_o(fetch_packet_w),
        .fetch_fault_o(fetch_fault_w),
        .fetch_fault_code_o(fetch_fault_code_w),

        .dbg_fetch_valid_o(fetch_valid_o),
        .dbg_fetch_pc_o(),
        .dbg_fetch_instr_o(fetch_instr_o)
    );

    // -------------------------------------------------------------------------
    // Decoder
    // -------------------------------------------------------------------------
    nvisc_instruction_decoder u_dec (
        .fetch_packet_i(fetch_packet_w),
        .decode_packet_o(decode_packet_w),

        .dbg_valid_o(),
        .dbg_pc_o(),
        .dbg_instr_o(),
        .dbg_instr_class_o(decode_class_o),
        .dbg_opcode_o(),
        .dbg_rd_o(),
        .dbg_rs1_o(),
        .dbg_rs2_o(),
        .dbg_imm_o(),
        .dbg_reg_write_o(),
        .dbg_mem_read_o(),
        .dbg_mem_write_o(),
        .dbg_csr_read_o(),
        .dbg_branch_o(),
        .dbg_illegal_o()
    );

    // -------------------------------------------------------------------------
    // Control
    // -------------------------------------------------------------------------
    nvisc_control_unit u_ctrl (
        .decode_packet_i(decode_packet_w),

        .alu_valid_o(alu_valid_o),
        .lsu_valid_o(lsu_valid_o),
        .csr_valid_o(csr_valid_o),
        .branch_valid_o(branch_valid_o),
        .alu_op_o(ctrl_alu_op_w),

        .reg_write_o(ctrl_reg_write_w),
        .mem_read_o(ctrl_mem_read_w),
        .mem_write_o(ctrl_mem_write_w),
        .csr_read_o(ctrl_csr_read_w),
        .csr_write_o(ctrl_csr_write_w),

        .rd_o(ctrl_rd_w),
        .rs1_o(ctrl_rs1_w),
        .rs2_o(ctrl_rs2_w),
        .imm_o(ctrl_imm_w),

        .mem_domain_o(ctrl_mem_domain_w),
        .id_o(ctrl_identity_w),

        .illegal_o(ctrl_illegal_w),
        .trap_o(ctrl_trap_w),
        .trap_code_o(ctrl_trap_code_w),

        .dbg_instr_class_o(),
        .dbg_any_valid_o()
    );

    // -------------------------------------------------------------------------
    // Minimal LOAD response tracker
    // -------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            load_pending_q <= 1'b0;
            load_rd_q      <= '0;
        end else begin
            // Capture destination register when a LOAD request is issued.
            if (lsu_valid_o && ctrl_mem_read_w && ctrl_reg_write_w) begin
                load_pending_q <= 1'b1;
                load_rd_q      <= ctrl_rd_w;
            end

            // Clear pending state when response arrives.
            if (dmem_resp_valid_i || dmem_resp_fault_i) begin
                load_pending_q <= 1'b0;
            end
        end
    end

    assign dmem_fault_w      = dmem_resp_fault_i;
    assign dmem_fault_code_w = dmem_resp_fault_code_i;

    assign load_wb_valid_o = load_pending_q && dmem_resp_valid_i && !dmem_resp_fault_i;
    assign load_wb_data_o  = dmem_resp_rdata_i;

    // -------------------------------------------------------------------------
    // Register-file writeback mux
    // -------------------------------------------------------------------------
    always_comb begin
        // Debug preload has priority during bring-up.
        rf_we_w    = dbg_rf_we_i;
        rf_waddr_w = dbg_rf_waddr_i;
        rf_wdata_w = dbg_rf_wdata_i;

        // LOAD response writeback.
        if (!dbg_rf_we_i && load_wb_valid_o) begin
            rf_we_w    = 1'b1;
            rf_waddr_w = load_rd_q;
            rf_wdata_w = dmem_resp_rdata_i;
        end

        // ALU writeback path.
        // Later this becomes a real WB-stage arbiter with load/CSR/vector support.
        if (!dbg_rf_we_i && !load_wb_valid_o && alu_result_valid_o && ctrl_reg_write_w) begin
            rf_we_w    = 1'b1;
            rf_waddr_w = ctrl_rd_w;
            rf_wdata_w = alu_result_o;
        end
    end

    // -------------------------------------------------------------------------
    // Scalar register file
    // -------------------------------------------------------------------------
    nvisc_scalar_regfile u_rf (
        .clk(clk),
        .rst_n(rst_n),

        .rs1_addr_i(ctrl_rs1_w),
        .rs1_data_o(rs1_data_w),

        .rs2_addr_i(ctrl_rs2_w),
        .rs2_data_o(rs2_data_w),

        .rd_we_i(rf_we_w),
        .rd_addr_i(rf_waddr_w),
        .rd_data_i(rf_wdata_w),

        .dbg_r0_o(),
        .dbg_r1_o(dbg_rf_r1_o),
        .dbg_r2_o(dbg_rf_r2_o),
        .dbg_r3_o(dbg_rf_r3_o)
    );

    // -------------------------------------------------------------------------
    // Basic ALU v0.2
    // -------------------------------------------------------------------------
    nvisc_alu_v02 u_alu (
        .alu_valid_i(alu_valid_o),

        .alu_op_i(ctrl_alu_op_w),

        .src_a_i(rs1_data_w),
        .src_b_i(rs2_data_w),

        .result_valid_o(alu_result_valid_o),
        .result_o(alu_result_o),

        .zero_o(alu_zero_o),
        .negative_o(alu_negative_o),
        .overflow_o(alu_overflow_o),

        .fault_o(alu_fault_w),
        .fault_code_o(alu_fault_code_w),

        .dbg_alu_op_o(),
        .dbg_src_a_o(),
        .dbg_src_b_o(),
        .dbg_result_o()
    );

    // -------------------------------------------------------------------------
    // Branch execution unit v0.2
    // -------------------------------------------------------------------------
    nvisc_branch_unit_v02 u_branch (
        .branch_valid_i(branch_valid_o),

        .pc_i(decode_packet_w.pc),
        .imm_i(ctrl_imm_w),

        .src_a_i(rs1_data_w),
        .src_b_i(rs2_data_w),

        .branch_taken_o(branch_taken_w),
        .branch_target_o(branch_target_w),

        .fault_o(branch_fault_w),
        .fault_code_o(branch_fault_code_w),

        .dbg_branch_valid_o(),
        .dbg_branch_taken_o(branch_taken_internal_o),
        .dbg_branch_target_o(branch_target_internal_o)
    );

    // -------------------------------------------------------------------------
    // LSU stub
    // -------------------------------------------------------------------------
    nvisc_lsu_stub u_lsu (
        .clk(clk),
        .rst_n(rst_n),

        .lsu_valid_i(lsu_valid_o),
        .mem_read_i(ctrl_mem_read_w),
        .mem_write_i(ctrl_mem_write_w),

        .base_value_i(rs1_data_w),
        .imm_i(ctrl_imm_w),
        .store_data_i(rs2_data_w),

        .size_bytes_i(lsu_size_bytes_i),
        .mem_domain_i(ctrl_mem_domain_w),
        .id_i(ctrl_identity_w),

        .mem_req_o(lsu_mem_req_w),

        .lsu_fault_o(lsu_fault_w),
        .lsu_fault_code_o(lsu_fault_code_w),

        .dbg_req_valid_o(),
        .dbg_req_is_read_o(),
        .dbg_req_is_write_o(),
        .dbg_req_vaddr_o(),
        .dbg_req_paddr_o(),
        .dbg_req_wdata_o(),
        .dbg_req_size_bytes_o(),
        .dbg_req_mem_domain_o()
    );

    // -------------------------------------------------------------------------
    // MMU/TLB stub: LSU virtual request -> translated physical request
    // -------------------------------------------------------------------------
    nvisc_mmu_tlb_stub u_mmu (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(lsu_mem_req_w.valid),
        .req_is_read_i(lsu_mem_req_w.is_read),
        .req_is_write_i(lsu_mem_req_w.is_write),
        .req_vaddr_i(lsu_mem_req_w.vaddr),
        .req_wdata_i(lsu_mem_req_w.wdata),
        .req_size_bytes_i(lsu_mem_req_w.size_bytes),
        .req_mem_domain_i(lsu_mem_req_w.mem_domain),
        .req_id_i(lsu_mem_req_w.id),

        .resp_valid_o(mmu_resp_valid_w),
        .resp_is_read_o(mmu_resp_is_read_w),
        .resp_is_write_o(mmu_resp_is_write_w),
        .resp_vaddr_o(mmu_resp_vaddr_w),
        .resp_paddr_o(mmu_resp_paddr_w),
        .resp_wdata_o(mmu_resp_wdata_w),
        .resp_size_bytes_o(mmu_resp_size_bytes_w),
        .resp_mem_domain_o(mmu_resp_mem_domain_w),
        .resp_id_o(mmu_resp_id_w),

        .mmu_fault_o(mmu_fault_w),
        .mmu_fault_code_o(mmu_fault_code_w),

        .dbg_translate_valid_o(),
        .dbg_vaddr_o(),
        .dbg_paddr_o(),
        .dbg_page_fault_o(),
        .dbg_align_fault_o()
    );

    // -------------------------------------------------------------------------
    // Core fault aggregation
    // -------------------------------------------------------------------------
    always_comb begin
        core_fault_o      = 1'b0;
        core_fault_code_o = 16'd0;

        if (fetch_fault_w) begin
            core_fault_o      = 1'b1;
            core_fault_code_o = fetch_fault_code_w;
        end else if (ctrl_trap_w) begin
            core_fault_o      = 1'b1;
            core_fault_code_o = ctrl_trap_code_w;
        end else if (alu_fault_w) begin
            core_fault_o      = 1'b1;
            core_fault_code_o = alu_fault_code_w;
        end else if (mmu_fault_w) begin
            core_fault_o      = 1'b1;
            core_fault_code_o = mmu_fault_code_w;
        end else if (dmem_fault_w) begin
            core_fault_o      = 1'b1;
            core_fault_code_o = dmem_fault_code_w;
        end else if (branch_fault_w) begin
            core_fault_o      = 1'b1;
            core_fault_code_o = branch_fault_code_w;
        end else if (lsu_fault_w) begin
            core_fault_o      = 1'b1;
            core_fault_code_o = lsu_fault_code_w;
        end else if (csr_fault_w) begin
            core_fault_o      = 1'b1;
            core_fault_code_o = csr_fault_code_w;
        end
    end

    // Public memory request view after MMU/TLB translation.
    assign mem_req_valid_o      = mmu_resp_valid_w;
    assign mem_req_is_read_o    = mmu_resp_is_read_w;
    assign mem_req_is_write_o   = mmu_resp_is_write_w;
    assign mem_req_vaddr_o      = mmu_resp_vaddr_w;
    assign mem_req_paddr_o      = mmu_resp_paddr_w;
    assign mem_req_wdata_o      = mmu_resp_wdata_w;
    assign mem_req_size_bytes_o = mmu_resp_size_bytes_w;
    assign mem_req_domain_o     = mmu_resp_mem_domain_w;

    assign pc_o       = pc_w;
    assign pc_valid_o = pc_valid_w;

endmodule
