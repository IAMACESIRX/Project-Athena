`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_pc_branch_unit #(
    parameter logic [63:0] RESET_VECTOR = NV_RESET_VECTOR
)(
    input  logic clk,
    input  logic rst_n,

    input  logic stall_i,

    input  logic redirect_valid_i,
    input  logic [63:0] redirect_pc_i,

    input  logic branch_taken_i,
    input  logic [63:0] branch_target_i,

    input  logic trap_valid_i,
    input  logic [63:0] trap_vector_i,

    input  logic rollback_redirect_i,
    input  logic [63:0] rollback_pc_i,

    output logic [63:0] pc_o,
    output logic        pc_valid_o
);

    logic [63:0] pc_q;
    logic        valid_q;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pc_q    <= RESET_VECTOR;
            valid_q <= 1'b0;
        end else begin
            valid_q <= 1'b1;

            if (!stall_i) begin
                if (rollback_redirect_i) begin
                    pc_q <= rollback_pc_i;
                end else if (trap_valid_i) begin
                    pc_q <= trap_vector_i;
                end else if (redirect_valid_i) begin
                    pc_q <= redirect_pc_i;
                end else if (branch_taken_i) begin
                    pc_q <= branch_target_i;
                end else begin
                    pc_q <= pc_q + 64'd4;
                end
            end
        end
    end

    assign pc_o       = pc_q;
    assign pc_valid_o = valid_q;

endmodule
