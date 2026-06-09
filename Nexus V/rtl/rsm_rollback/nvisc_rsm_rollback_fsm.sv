`timescale 1ns / 1ps

import nvisc_rsm_pkg::*;

module nvisc_rsm_rollback_fsm #(
    parameter int STATE_ID_W  = 32,
    parameter int BRANCH_ID_W = 32,
    parameter int COMMIT_ID_W = 32,
    parameter int PAGE_ROOT_W = 32
)(
    input  logic clk,
    input  logic rst_n,

    input  logic rollback_req_i,
    input  logic [STATE_ID_W-1:0]  target_state_id_i,
    input  logic [BRANCH_ID_W-1:0] active_branch_id_i,
    input  logic [STATE_ID_W-1:0]  active_state_id_i,
    input  logic                   aegis_rollback_allow_i,

    output logic rollback_busy_o,
    output logic rollback_done_o,
    output logic rollback_fault_o,
    output nvisc_rsm_rollback_fault_e rollback_fault_code_o,

    output logic state_meta_rd_req_o,
    output logic [STATE_ID_W-1:0] state_meta_rd_state_id_o,
    input  logic state_meta_rd_valid_i,
    input  nvisc_state_meta_t state_meta_rd_data_i,

    output logic branch_meta_rd_req_o,
    output logic [BRANCH_ID_W-1:0] branch_meta_rd_branch_id_o,
    input  logic branch_meta_rd_valid_i,
    input  nvisc_branch_meta_t branch_meta_rd_data_i,

    output logic branch_meta_wr_req_o,
    output logic [BRANCH_ID_W-1:0] branch_meta_wr_branch_id_o,
    output nvisc_branch_meta_t branch_meta_wr_data_o,

    output logic active_root_update_o,
    output logic [PAGE_ROOT_W-1:0] active_page_root_o,
    output logic [STATE_ID_W-1:0]  new_active_state_id_o,
    output logic [COMMIT_ID_W-1:0] new_active_commit_id_o,

    output logic invalidate_descendants_o,
    output logic [STATE_ID_W-1:0] invalidate_from_state_id_o,

    output logic delta_log_wr_req_o,
    output nvisc_rsm_delta_entry_t delta_log_entry_o
);

    nvisc_rsm_rollback_fsm_e rb_state_q, rb_state_d;
    nvisc_state_meta_t       target_state_q;
    nvisc_branch_meta_t      branch_meta_q;
    nvisc_rsm_rollback_fault_e fault_code_q, fault_code_d;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rb_state_q     <= RB_IDLE;
            fault_code_q   <= RB_OK;
            target_state_q <= '0;
            branch_meta_q  <= '0;
        end else begin
            rb_state_q   <= rb_state_d;
            fault_code_q <= fault_code_d;

            if (state_meta_rd_valid_i) begin
                target_state_q <= state_meta_rd_data_i;
            end

            if (branch_meta_rd_valid_i) begin
                branch_meta_q <= branch_meta_rd_data_i;
            end
        end
    end

    always_comb begin
        rb_state_d   = rb_state_q;
        fault_code_d = fault_code_q;

        rollback_busy_o  = (rb_state_q != RB_IDLE) && (rb_state_q != RB_DONE) && (rb_state_q != RB_FAULT);
        rollback_done_o  = 1'b0;
        rollback_fault_o = 1'b0;
        rollback_fault_code_o = fault_code_q;

        state_meta_rd_req_o      = 1'b0;
        state_meta_rd_state_id_o = target_state_id_i;

        branch_meta_rd_req_o       = 1'b0;
        branch_meta_rd_branch_id_o = active_branch_id_i;

        branch_meta_wr_req_o       = 1'b0;
        branch_meta_wr_branch_id_o = active_branch_id_i;
        branch_meta_wr_data_o      = branch_meta_q;

        active_root_update_o   = 1'b0;
        active_page_root_o     = target_state_q.page_root_id[PAGE_ROOT_W-1:0];
        new_active_state_id_o  = target_state_q.state_id[STATE_ID_W-1:0];
        new_active_commit_id_o = target_state_q.commit_id[COMMIT_ID_W-1:0];

        invalidate_descendants_o      = 1'b0;
        invalidate_from_state_id_o    = active_state_id_i;

        delta_log_wr_req_o = 1'b0;
        delta_log_entry_o  = '0;

        unique case (rb_state_q)
            RB_IDLE: begin
                fault_code_d = RB_OK;
                if (rollback_req_i) begin
                    rb_state_d = RB_LOOKUP_STATE;
                end
            end

            RB_LOOKUP_STATE: begin
                state_meta_rd_req_o      = 1'b1;
                state_meta_rd_state_id_o = target_state_id_i;
                if (state_meta_rd_valid_i) rb_state_d = RB_VALIDATE_STATE;
            end

            RB_VALIDATE_STATE: begin
                if (!target_state_q.valid) begin
                    fault_code_d = RB_FAULT_INVALID_TARGET;
                    rb_state_d   = RB_FAULT;
                end else if (target_state_q.pruned) begin
                    fault_code_d = RB_FAULT_PRUNED_STATE;
                    rb_state_d   = RB_FAULT;
                end else if (!target_state_q.rollback_valid) begin
                    fault_code_d = RB_FAULT_NOT_ROLLBACKABLE;
                    rb_state_d   = RB_FAULT;
                end else if (target_state_q.page_root_id == '0) begin
                    fault_code_d = RB_FAULT_BAD_PAGE_ROOT;
                    rb_state_d   = RB_FAULT;
                end else if (!aegis_rollback_allow_i) begin
                    fault_code_d = RB_FAULT_AEGIS_DENIED;
                    rb_state_d   = RB_FAULT;
                end else begin
                    rb_state_d = RB_LOOKUP_BRANCH;
                end
            end

            RB_LOOKUP_BRANCH: begin
                branch_meta_rd_req_o       = 1'b1;
                branch_meta_rd_branch_id_o = active_branch_id_i;
                if (branch_meta_rd_valid_i) rb_state_d = RB_VALIDATE_BRANCH;
            end

            RB_VALIDATE_BRANCH: begin
                if (!branch_meta_q.valid || branch_meta_q.pruned) begin
                    fault_code_d = RB_FAULT_BRANCH_MISMATCH;
                    rb_state_d   = RB_FAULT;
                end else if ((target_state_q.branch_id != active_branch_id_i) &&
                             (target_state_q.branch_id != branch_meta_q.parent_branch_id)) begin
                    fault_code_d = RB_FAULT_LINEAGE_CONFLICT;
                    rb_state_d   = RB_FAULT;
                end else begin
                    rb_state_d = RB_FLUSH_DESCENDANTS;
                end
            end

            RB_FLUSH_DESCENDANTS: begin
                invalidate_descendants_o   = 1'b1;
                invalidate_from_state_id_o = active_state_id_i;
                rb_state_d = RB_REBIND_ROOT;
            end

            RB_REBIND_ROOT: begin
                active_root_update_o   = 1'b1;
                active_page_root_o     = target_state_q.page_root_id[PAGE_ROOT_W-1:0];
                new_active_state_id_o  = target_state_q.state_id[STATE_ID_W-1:0];
                new_active_commit_id_o = target_state_q.commit_id[COMMIT_ID_W-1:0];
                rb_state_d = RB_UPDATE_BRANCH_HEAD;
            end

            RB_UPDATE_BRANCH_HEAD: begin
                branch_meta_wr_req_o       = 1'b1;
                branch_meta_wr_branch_id_o = active_branch_id_i;
                branch_meta_wr_data_o      = branch_meta_q;
                branch_meta_wr_data_o.head_state_id = target_state_q.state_id;
                branch_meta_wr_data_o.commit_id     = target_state_q.commit_id;
                rb_state_d = RB_INVALIDATE_TOKENS;
            end

            RB_INVALIDATE_TOKENS: begin
                invalidate_descendants_o   = 1'b1;
                invalidate_from_state_id_o = target_state_q.state_id[STATE_ID_W-1:0];
                rb_state_d = RB_LOG_EVENT;
            end

            RB_LOG_EVENT: begin
                delta_log_wr_req_o = 1'b1;
                delta_log_entry_o.valid          = 1'b1;
                delta_log_entry_o.branch_id      = active_branch_id_i;
                delta_log_entry_o.from_state_id  = active_state_id_i;
                delta_log_entry_o.to_state_id    = target_state_q.state_id;
                delta_log_entry_o.commit_id      = target_state_q.commit_id;
                delta_log_entry_o.op_kind        = DELTA_ROLLBACK;
                delta_log_entry_o.rollback_event = 1'b1;
                rb_state_d = RB_DONE;
            end

            RB_DONE: begin
                rollback_done_o = 1'b1;
                if (!rollback_req_i) rb_state_d = RB_IDLE;
            end

            RB_FAULT: begin
                rollback_fault_o = 1'b1;
                rollback_fault_code_o = fault_code_q;
                if (!rollback_req_i) rb_state_d = RB_IDLE;
            end

            default: begin
                fault_code_d = RB_FAULT_INVALID_TARGET;
                rb_state_d = RB_FAULT;
            end
        endcase
    end

endmodule
