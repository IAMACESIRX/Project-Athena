`timescale 1ns / 1ps
import nvisc_rsm_pkg::*;

module nvisc_rsm_state_meta_table #(
    parameter int NUM_STATES_P = 256,
    parameter int STATE_IDX_W_P = $clog2(NUM_STATES_P)
)(
    input  logic clk,
    input  logic rst_n,
    input  logic wr_en_i,
    input  logic [STATE_IDX_W_P-1:0] wr_idx_i,
    input  nvisc_state_meta_t wr_meta_i,
    input  logic [STATE_IDX_W_P-1:0] rd_idx_i,
    output nvisc_state_meta_t rd_meta_o,
    input  logic seal_i,
    input  logic unseal_i,
    input  logic [STATE_IDX_W_P-1:0] seal_idx_i,
    input  logic mark_commit_i,
    input  logic [STATE_IDX_W_P-1:0] commit_idx_i,
    input  logic [31:0] commit_id_i
);
    nvisc_state_meta_t table_q [NUM_STATES_P];
    integer i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < NUM_STATES_P; i++) begin
                table_q[i] <= '0;
            end
        end else begin
            if (wr_en_i) table_q[wr_idx_i] <= wr_meta_i;
            if (seal_i) table_q[seal_idx_i].sealed <= 1'b1;
            if (unseal_i) table_q[seal_idx_i].sealed <= 1'b0;
            if (mark_commit_i) begin
                table_q[commit_idx_i].committed <= 1'b1;
                table_q[commit_idx_i].commit_id <= commit_id_i;
                table_q[commit_idx_i].rollback_valid <= 1'b1;
            end
        end
    end

    assign rd_meta_o = table_q[rd_idx_i];
endmodule
