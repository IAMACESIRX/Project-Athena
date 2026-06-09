`timescale 1ns / 1ps

import nvisc_rsm_pkg::*;

module nvisc_rsm_controller_phase1_rollback #(
    parameter int STATE_ID_W  = 32,
    parameter int BRANCH_ID_W = 32,
    parameter int COMMIT_ID_W = 32,
    parameter int PAGE_ROOT_W = 32,
    parameter int LOG_DEPTH   = 256
)(
    input  logic clk,
    input  logic rst_n,

    input  logic rollback_req_i,
    input  logic [STATE_ID_W-1:0] rollback_state_id_i,
    input  logic [BRANCH_ID_W-1:0] active_branch_id_i,
    input  logic [STATE_ID_W-1:0] active_state_id_i,
    input  logic aegis_rollback_allow_i,

    input  nvisc_state_meta_t  state_meta_rd_data_i,
    input  logic               state_meta_rd_valid_i,
    output logic               state_meta_rd_req_o,
    output logic [STATE_ID_W-1:0] state_meta_rd_state_id_o,

    input  nvisc_branch_meta_t branch_meta_rd_data_i,
    input  logic               branch_meta_rd_valid_i,
    output logic               branch_meta_rd_req_o,
    output logic [BRANCH_ID_W-1:0] branch_meta_rd_branch_id_o,

    output logic               branch_meta_wr_req_o,
    output logic [BRANCH_ID_W-1:0] branch_meta_wr_branch_id_o,
    output nvisc_branch_meta_t branch_meta_wr_data_o,

    output logic rollback_busy_o,
    output logic rollback_done_o,
    output logic rollback_fault_o,
    output nvisc_rsm_rollback_fault_e rollback_fault_code_o,

    output logic active_root_update_o,
    output logic [PAGE_ROOT_W-1:0] active_page_root_o,
    output logic [STATE_ID_W-1:0]  new_active_state_id_o,
    output logic [COMMIT_ID_W-1:0] new_active_commit_id_o,

    output logic invalidate_descendants_o,
    output logic [STATE_ID_W-1:0] invalidate_from_state_id_o,

    output logic delta_log_full_o,
    output logic [31:0] delta_log_count_o
);

    nvisc_rsm_delta_entry_t delta_log_entry;
    logic delta_log_wr_req;
    logic delta_log_wr_ready;
    logic [$clog2(LOG_DEPTH)-1:0] delta_log_wr_index;
    logic [$clog2(LOG_DEPTH):0] delta_count;

    nvisc_rsm_rollback_fsm u_rollback_fsm (
        .clk(clk),
        .rst_n(rst_n),
        .rollback_req_i(rollback_req_i),
        .target_state_id_i(rollback_state_id_i),
        .active_branch_id_i(active_branch_id_i),
        .active_state_id_i(active_state_id_i),
        .aegis_rollback_allow_i(aegis_rollback_allow_i),
        .rollback_busy_o(rollback_busy_o),
        .rollback_done_o(rollback_done_o),
        .rollback_fault_o(rollback_fault_o),
        .rollback_fault_code_o(rollback_fault_code_o),
        .state_meta_rd_req_o(state_meta_rd_req_o),
        .state_meta_rd_state_id_o(state_meta_rd_state_id_o),
        .state_meta_rd_valid_i(state_meta_rd_valid_i),
        .state_meta_rd_data_i(state_meta_rd_data_i),
        .branch_meta_rd_req_o(branch_meta_rd_req_o),
        .branch_meta_rd_branch_id_o(branch_meta_rd_branch_id_o),
        .branch_meta_rd_valid_i(branch_meta_rd_valid_i),
        .branch_meta_rd_data_i(branch_meta_rd_data_i),
        .branch_meta_wr_req_o(branch_meta_wr_req_o),
        .branch_meta_wr_branch_id_o(branch_meta_wr_branch_id_o),
        .branch_meta_wr_data_o(branch_meta_wr_data_o),
        .active_root_update_o(active_root_update_o),
        .active_page_root_o(active_page_root_o),
        .new_active_state_id_o(new_active_state_id_o),
        .new_active_commit_id_o(new_active_commit_id_o),
        .invalidate_descendants_o(invalidate_descendants_o),
        .invalidate_from_state_id_o(invalidate_from_state_id_o),
        .delta_log_wr_req_o(delta_log_wr_req),
        .delta_log_entry_o(delta_log_entry)
    );

    nvisc_rsm_delta_log #(
        .LOG_DEPTH(LOG_DEPTH)
    ) u_delta_log (
        .clk(clk),
        .rst_n(rst_n),
        .wr_req_i(delta_log_wr_req),
        .wr_entry_i(delta_log_entry),
        .wr_ready_o(delta_log_wr_ready),
        .wr_index_o(delta_log_wr_index),
        .rd_req_i(1'b0),
        .rd_index_i('0),
        .rd_valid_o(),
        .rd_entry_o(),
        .full_o(delta_log_full_o),
        .empty_o(),
        .count_o(delta_count)
    );

    assign delta_log_count_o = {{(32-$bits(delta_count)){1'b0}}, delta_count};

endmodule
