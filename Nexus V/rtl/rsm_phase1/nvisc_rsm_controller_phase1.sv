`timescale 1ns / 1ps
import nvisc_rsm_pkg::*;

module nvisc_rsm_controller_phase1 #(
    parameter int NUM_PAGES_P    = 256,
    parameter int NUM_BRANCHES_P = 64,
    parameter int NUM_STATES_P   = 256,
    parameter int PADDR_W_P      = PADDR_W,
    parameter int PAGE_IDX_W_P   = $clog2(NUM_PAGES_P),
    parameter int BRANCH_IDX_W_P = $clog2(NUM_BRANCHES_P),
    parameter int STATE_IDX_W_P  = $clog2(NUM_STATES_P)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic cow_fault_i,
    input  logic [BRANCH_IDX_W_P-1:0] active_branch_idx_i,
    input  logic [STATE_IDX_W_P-1:0] active_state_idx_i,
    input  logic [PAGE_IDX_W_P-1:0] logical_page_i,
    input  logic sealed_page_i,
    output logic cow_resolved_o,
    output logic cow_fault_o,
    output logic [PADDR_W_P-1:0] cow_new_paddr_o,

    input  logic branch_meta_wr_i,
    input  logic [BRANCH_IDX_W_P-1:0] branch_meta_wr_idx_i,
    input  nvisc_branch_meta_t branch_meta_wr_i_data,

    input  logic state_meta_wr_i,
    input  logic [STATE_IDX_W_P-1:0] state_meta_wr_idx_i,
    input  nvisc_state_meta_t state_meta_wr_i_data,

    input  logic rollback_req_i,
    input  logic [STATE_IDX_W_P-1:0] rollback_state_idx_i,
    output logic rollback_done_o,
    output logic rollback_fault_o,

    input  logic mark_commit_i,
    input  logic [STATE_IDX_W_P-1:0] commit_state_idx_i,
    input  logic [31:0] commit_id_i,

    output logic alloc_fault_o
);
    nvisc_branch_meta_t active_branch_meta;
    nvisc_state_meta_t active_state_meta;
    nvisc_state_meta_t rollback_state_meta;

    logic alloc_req, alloc_ready, alloc_take;
    logic [PADDR_W_P-1:0] alloc_paddr;

    nvisc_rsm_branch_meta_table #(.NUM_BRANCHES_P(NUM_BRANCHES_P)) u_branch_meta (
        .clk(clk), .rst_n(rst_n),
        .wr_en_i(branch_meta_wr_i), .wr_idx_i(branch_meta_wr_idx_i), .wr_meta_i(branch_meta_wr_i_data),
        .rd_idx_i(active_branch_idx_i), .rd_meta_o(active_branch_meta),
        .seal_i(1'b0), .unseal_i(1'b0), .seal_idx_i('0)
    );

    nvisc_rsm_state_meta_table #(.NUM_STATES_P(NUM_STATES_P)) u_state_meta_active (
        .clk(clk), .rst_n(rst_n),
        .wr_en_i(state_meta_wr_i), .wr_idx_i(state_meta_wr_idx_i), .wr_meta_i(state_meta_wr_i_data),
        .rd_idx_i(active_state_idx_i), .rd_meta_o(active_state_meta),
        .seal_i(1'b0), .unseal_i(1'b0), .seal_idx_i('0),
        .mark_commit_i(mark_commit_i), .commit_idx_i(commit_state_idx_i), .commit_id_i(commit_id_i)
    );

    // Phase 1 note: a second read port is modeled with a mirror instance for documentation clarity.
    // A production implementation should use a true dual-read SRAM wrapper.
    nvisc_rsm_state_meta_table #(.NUM_STATES_P(NUM_STATES_P)) u_state_meta_rollback_mirror (
        .clk(clk), .rst_n(rst_n),
        .wr_en_i(state_meta_wr_i), .wr_idx_i(state_meta_wr_idx_i), .wr_meta_i(state_meta_wr_i_data),
        .rd_idx_i(rollback_state_idx_i), .rd_meta_o(rollback_state_meta),
        .seal_i(1'b0), .unseal_i(1'b0), .seal_idx_i('0),
        .mark_commit_i(mark_commit_i), .commit_idx_i(commit_state_idx_i), .commit_id_i(commit_id_i)
    );

    nvisc_rsm_phys_alloc #(.NUM_PAGES_P(NUM_PAGES_P), .PADDR_W_P(PADDR_W_P)) u_alloc (
        .clk(clk), .rst_n(rst_n),
        .alloc_req_i(alloc_req), .alloc_ready_o(alloc_ready), .alloc_paddr_o(alloc_paddr),
        .alloc_page_idx_o(), .alloc_take_i(alloc_take),
        .free_req_i(1'b0), .free_paddr_i('0), .free_ok_o(), .free_fault_o(),
        .seal_req_i(1'b0), .seal_paddr_i('0), .unseal_req_i(1'b0), .unseal_paddr_i('0),
        .empty_o(), .full_o(), .free_count_o(), .alloc_fault_o(alloc_fault_o)
    );

    nvisc_rsm_cow_map #(.NUM_PAGES_P(NUM_PAGES_P), .PADDR_W_P(PADDR_W_P)) u_cow_map (
        .clk(clk), .rst_n(rst_n),
        .cow_fault_i(cow_fault_i), .logical_page_i(logical_page_i),
        .sealed_branch_i(active_branch_meta.sealed), .sealed_state_i(active_state_meta.sealed), .sealed_page_i(sealed_page_i),
        .alloc_req_o(alloc_req), .alloc_ready_i(alloc_ready), .alloc_paddr_i(alloc_paddr), .alloc_take_o(alloc_take),
        .remap_valid_o(), .remap_lpage_o(), .remap_paddr_o(cow_new_paddr_o),
        .cow_resolved_o(cow_resolved_o), .cow_fault_o(cow_fault_o)
    );

    assign rollback_done_o  = rollback_req_i && rollback_state_meta.valid && rollback_state_meta.rollback_valid && !rollback_state_meta.sealed;
    assign rollback_fault_o = rollback_req_i && (!rollback_state_meta.valid || !rollback_state_meta.rollback_valid || rollback_state_meta.sealed);
endmodule
