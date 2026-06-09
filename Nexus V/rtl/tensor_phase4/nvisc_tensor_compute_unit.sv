`timescale 1ns / 1ps
import nvisc_tensor_pkg::*;

module nvisc_tensor_compute_unit #(
    parameter int DATA_W = 32,
    parameter int ACC_W = 64
)(
    input  logic clk,
    input  logic rst_n,
    input  logic start_i,
    input  nvisc_tensor_tile_job_t job_i,
    input  logic signed [DATA_W-1:0] a0_i,
    input  logic signed [DATA_W-1:0] b0_i,
    input  logic signed [DATA_W-1:0] a1_i,
    input  logic signed [DATA_W-1:0] b1_i,
    output logic done_o,
    output logic valid_o,
    output logic signed [ACC_W-1:0] acc_o,
    output logic [31:0] branch_id_o,
    output logic [31:0] state_id_o
);
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            done_o <= 1'b0;
            valid_o <= 1'b0;
            acc_o <= '0;
            branch_id_o <= '0;
            state_id_o <= '0;
        end else begin
            done_o <= 1'b0;
            valid_o <= 1'b0;
            if (start_i && job_i.valid) begin
                acc_o <= (a0_i * b0_i) + (a1_i * b1_i);
                branch_id_o <= job_i.branch_id;
                state_id_o <= job_i.state_id;
                done_o <= 1'b1;
                valid_o <= 1'b1;
            end
        end
    end
endmodule
