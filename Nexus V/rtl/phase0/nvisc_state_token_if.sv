`timescale 1ns / 1ps

import nvisc_pkg::*;

module nvisc_state_token_if (
    input  logic clk,
    input  logic rst_n,

    input  logic update_i,
    input  nvisc_state_token_t token_i,

    input  logic branch_advance_i,
    input  logic [31:0] next_branch_id_i,
    input  logic state_advance_i,
    input  logic [31:0] next_state_id_i,
    input  logic commit_advance_i,
    input  logic [31:0] next_commit_id_i,

    input  logic topology_epoch_inc_i,
    input  logic thermal_epoch_inc_i,
    input  logic set_committed_i,
    input  logic set_sealed_i,
    input  logic set_rollback_valid_i,

    output nvisc_state_token_t token_o
);

    nvisc_state_token_t token_q;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            token_q.branch_id      <= 32'd0;
            token_q.state_id       <= 32'd0;
            token_q.commit_id      <= 32'd0;
            token_q.topology_epoch <= 16'd0;
            token_q.thermal_epoch  <= 16'd0;
            token_q.domain         <= DOMAIN_BIN;
            token_q.valid          <= 1'b1;
            token_q.committed      <= 1'b0;
            token_q.sealed         <= 1'b0;
            token_q.rollback_valid <= 1'b1;
        end else begin
            if (update_i) begin
                token_q <= token_i;
            end else begin
                if (branch_advance_i) begin
                    token_q.branch_id <= next_branch_id_i;
                    token_q.committed <= 1'b0;
                    token_q.sealed    <= 1'b0;
                end
                if (state_advance_i) begin
                    token_q.state_id  <= next_state_id_i;
                    token_q.committed <= 1'b0;
                end
                if (commit_advance_i) token_q.commit_id <= next_commit_id_i;
                if (topology_epoch_inc_i) token_q.topology_epoch <= token_q.topology_epoch + 16'd1;
                if (thermal_epoch_inc_i)  token_q.thermal_epoch  <= token_q.thermal_epoch + 16'd1;
                if (set_committed_i) token_q.committed <= 1'b1;
                if (set_sealed_i) token_q.sealed <= 1'b1;
                if (set_rollback_valid_i) token_q.rollback_valid <= 1'b1;
            end
        end
    end

    assign token_o = token_q;

endmodule
