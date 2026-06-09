`timescale 1ns / 1ps
import nvisc_tensor_pkg::*;

module nvisc_tensor_node_array_16 #(
    parameter int DATA_W = 32,
    parameter int ACC_W = 64
)(
    input  logic clk,
    input  logic rst_n,
    input  logic start_i,
    input  nvisc_tensor_tile_job_t jobs_i [16],
    output logic [15:0] done_mask_o,
    output logic signed [ACC_W-1:0] acc_o [16],
    output logic [31:0] branch_id_o [16],
    output logic [31:0] state_id_o [16]
);
    genvar g;
    generate
        for (g = 0; g < 16; g++) begin : GEN_TCU
            nvisc_tensor_compute_unit #(.DATA_W(DATA_W), .ACC_W(ACC_W)) u_tcu (
                .clk(clk), .rst_n(rst_n), .start_i(start_i), .job_i(jobs_i[g]),
                .a0_i(DATA_W'(g+1)), .b0_i(DATA_W'(1)), .a1_i(DATA_W'(1)), .b1_i(DATA_W'(1)),
                .done_o(done_mask_o[g]), .valid_o(), .acc_o(acc_o[g]),
                .branch_id_o(branch_id_o[g]), .state_id_o(state_id_o[g])
            );
        end
    endgenerate
endmodule
