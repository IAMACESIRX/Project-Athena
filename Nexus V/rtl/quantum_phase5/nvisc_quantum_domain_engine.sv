`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_quantum_domain_engine #(
    parameter int QREG_IDX_W = $clog2(QREG_COUNT),
    parameter int QTOKEN_IDX_W = $clog2(QTOKEN_COUNT)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic instr_valid_i,
    input  nvisc_qop_e qop_i,
    input  nvisc_qmode_e qmode_i,
    input  logic [QREG_IDX_W-1:0] qreg_idx_i,
    input  logic [31:0] branch_id_i,
    input  logic [31:0] state_id_i,
    input  logic [15:0] topology_epoch_i,
    input  logic [15:0] thermal_epoch_i,
    input  logic [7:0] seed_i,

    input  logic audit_allow_i,
    input  logic rollback_invalidate_i,
    input  logic [31:0] rollback_from_state_i,

    input  logic qhw_force_timeout_i,
    input  logic qhw_force_low_fidelity_i,

    output logic busy_o,
    output logic done_o,
    output logic fault_o,
    output nvisc_qfault_e fault_code_o,

    output logic qsync_valid_o,
    output logic [7:0] qsync_value_o,
    output logic qaudit_req_o,
    output logic qcommit_allow_o
);
    nvisc_qreg_meta_t alloc_meta, rd_meta, wr_meta;
    logic alloc_ready;
    logic [QREG_IDX_W-1:0] alloc_idx;
    logic qreg_rd_valid;

    nvisc_qsim_state_t qsim_rd, qsim_wr, gated_state;
    logic qsim_rd_valid, gate_valid, gate_fault;
    nvisc_qfault_e gate_fault_code;

    nvisc_qcollapse_reg_t collapse_from_measure, collapse_q;
    logic measure_valid, measure_fault;
    nvisc_qfault_e measure_fault_code;

    logic qtoken_create_ready;
    logic [QTOKEN_IDX_W-1:0] qtoken_create_idx;
    nvisc_quantum_token_t qtoken_create;

    logic qhw_accept, qhw_done, qhw_timeout;
    logic [7:0] qhw_result, qhw_fidelity;

    logic fsm_fault;
    nvisc_qfault_e fsm_fault_code;

    nvisc_qreg_file u_qreg_file (
        .clk(clk), .rst_n(rst_n),
        .wr_req_i((qop_i == QOP_QPREP && instr_valid_i) || (measure_valid)),
        .wr_idx_i(qreg_idx_i),
        .wr_meta_i(wr_meta),
        .rd_req_i(instr_valid_i),
        .rd_idx_i(qreg_idx_i),
        .rd_valid_o(qreg_rd_valid),
        .rd_meta_o(rd_meta),
        .alloc_req_i(instr_valid_i && qop_i == QOP_QALLOC),
        .branch_id_i(branch_id_i),
        .state_id_i(state_id_i),
        .qmode_i(qmode_i),
        .alloc_ready_o(alloc_ready),
        .alloc_idx_o(alloc_idx),
        .alloc_meta_o(alloc_meta)
    );

    always_comb begin
        wr_meta = rd_meta;
        if (instr_valid_i && qop_i == QOP_QPREP) begin
            wr_meta.valid = 1'b1;
            wr_meta.qreg_id = {{(32-QREG_IDX_W){1'b0}}, qreg_idx_i};
            wr_meta.branch_id = branch_id_i;
            wr_meta.state_id = state_id_i;
            wr_meta.qmode = qmode_i;
            wr_meta.prepared = 1'b1;
            wr_meta.collapsed = 1'b0;
            wr_meta.fidelity_score = 8'd255;
            wr_meta.rollback_valid = 1'b1;
        end
        if (measure_valid) begin
            wr_meta.measured = 1'b1;
            wr_meta.collapsed = 1'b1;
        end
    end

    nvisc_qsim_state_bank u_qsim_bank (
        .clk(clk), .rst_n(rst_n),
        .wr_req_i(gate_valid),
        .wr_idx_i(qreg_idx_i),
        .wr_state_i(gated_state),
        .rd_req_i(instr_valid_i),
        .rd_idx_i(qreg_idx_i),
        .rd_valid_o(qsim_rd_valid),
        .rd_state_o(qsim_rd),
        .prep_zero_i(instr_valid_i && qop_i == QOP_QPREP && qmode_i == QMODE_QSIM),
        .prep_idx_i(qreg_idx_i)
    );

    nvisc_quantum_gate_unit u_gate (
        .valid_i(instr_valid_i && (qop_i == QOP_QX || qop_i == QOP_QH || qop_i == QOP_QGATE)),
        .gate_i(qop_i),
        .state_i(qsim_rd),
        .valid_o(gate_valid),
        .state_o(gated_state),
        .fault_o(gate_fault),
        .fault_code_o(gate_fault_code)
    );

    nvisc_quantum_measure_unit u_measure (
        .clk(clk), .rst_n(rst_n),
        .measure_req_i(instr_valid_i && qop_i == QOP_QMEASURE),
        .qmeta_i(rd_meta),
        .qstate_i(qsim_rd),
        .seed_i(seed_i),
        .measure_valid_o(measure_valid),
        .collapse_o(collapse_from_measure),
        .fault_o(measure_fault),
        .fault_code_o(measure_fault_code)
    );

    nvisc_quantum_collapse_register u_collapse (
        .clk(clk), .rst_n(rst_n),
        .wr_req_i(measure_valid),
        .wr_collapse_i(collapse_from_measure),
        .clear_i(instr_valid_i && qop_i == QOP_QROLLBACK),
        .collapse_o(collapse_q)
    );

    nvisc_quantum_token_table u_qtoken_table (
        .clk(clk), .rst_n(rst_n),
        .create_req_i(measure_valid),
        .collapse_i(collapse_from_measure),
        .topology_epoch_i(topology_epoch_i),
        .thermal_epoch_i(thermal_epoch_i),
        .create_ready_o(qtoken_create_ready),
        .create_idx_o(qtoken_create_idx),
        .create_token_o(qtoken_create),
        .audit_mark_i(instr_valid_i && qop_i == QOP_QAUDIT && audit_allow_i),
        .audit_idx_i(qtoken_create_idx),
        .sync_mark_i(instr_valid_i && qop_i == QOP_QSYNC),
        .sync_idx_i(qtoken_create_idx),
        .rollback_invalidate_i(rollback_invalidate_i),
        .rollback_from_state_i(rollback_from_state_i),
        .rd_req_i(1'b0),
        .rd_idx_i('0),
        .rd_valid_o(),
        .rd_token_o()
    );

    nvisc_qhw_bridge_stub u_qhw (
        .clk(clk), .rst_n(rst_n),
        .qhw_req_i(instr_valid_i && qop_i == QOP_QHW_DISP),
        .qreg_id_i({{(32-QREG_IDX_W){1'b0}}, qreg_idx_i}),
        .shots_i(8'd16),
        .force_timeout_i(qhw_force_timeout_i),
        .force_low_fidelity_i(qhw_force_low_fidelity_i),
        .qhw_accept_o(qhw_accept),
        .qhw_done_o(qhw_done),
        .qhw_timeout_o(qhw_timeout),
        .qhw_result_o(qhw_result),
        .qhw_fidelity_o(qhw_fidelity)
    );

    nvisc_quantum_control_fsm u_fsm (
        .clk(clk), .rst_n(rst_n),
        .instr_valid_i(instr_valid_i),
        .qop_i(qop_i),
        .qmode_i(qmode_i),
        .audit_allow_i(audit_allow_i),
        .qhw_done_i(qhw_done),
        .qhw_timeout_i(qhw_timeout),
        .qhw_fidelity_i(qhw_fidelity),
        .busy_o(busy_o),
        .done_o(done_o),
        .fault_o(fsm_fault),
        .fault_code_o(fsm_fault_code),
        .audit_req_o(qaudit_req_o),
        .commit_allow_o(qcommit_allow_o),
        .rollback_discard_o()
    );

    assign qsync_valid_o = instr_valid_i && qop_i == QOP_QSYNC && collapse_q.valid;
    assign qsync_value_o = collapse_q.measured_value;

    always_comb begin
        fault_o = fsm_fault || gate_fault || measure_fault;
        fault_code_o = fsm_fault ? fsm_fault_code : (gate_fault ? gate_fault_code : measure_fault_code);
    end
endmodule
