`timescale 1ns / 1ps
import nvisc_tensor_pkg::*;

module nvisc_tensor_tile_scheduler #(
    parameter int NUM_NODES = NUM_TENSOR_NODES
)(
    input  logic clk,
    input  logic rst_n,
    input  logic start_i,
    input  nvisc_tensor_desc_t a_desc_i,
    input  nvisc_tensor_desc_t b_desc_i,
    input  nvisc_tensor_desc_t c_desc_i,
    input  logic [NUM_NODES-1:0] node_available_mask_i,
    input  logic [NUM_NODES-1:0] node_trust_mask_i,
    input  logic [NUM_NODES-1:0] node_cool_mask_i,

    output logic valid_o,
    output nvisc_tensor_tile_job_t jobs_o [NUM_NODES],
    output logic fault_o,
    output nvisc_tensor_fault_e fault_code_o
);
    integer n;
    logic shape_ok;
    assign shape_ok = a_desc_i.valid && b_desc_i.valid && c_desc_i.valid &&
                      (a_desc_i.cols == b_desc_i.rows) &&
                      (c_desc_i.rows == a_desc_i.rows) &&
                      (c_desc_i.cols == b_desc_i.cols);

    always_comb begin
        valid_o = 1'b0;
        fault_o = 1'b0;
        fault_code_o = TENSOR_FAULT_NONE;
        for (n = 0; n < NUM_NODES; n++) begin
            jobs_o[n] = '0;
            jobs_o[n].node_id = n[15:0];
            jobs_o[n].tensor_a_id = a_desc_i.tensor_id;
            jobs_o[n].tensor_b_id = b_desc_i.tensor_id;
            jobs_o[n].tensor_c_id = c_desc_i.tensor_id;
            jobs_o[n].tile_m = (n / 4);
            jobs_o[n].tile_n = (n % 4);
            jobs_o[n].tile_k_start = 16'd0;
            jobs_o[n].tile_k_count = a_desc_i.cols;
            jobs_o[n].branch_id = c_desc_i.branch_id;
            jobs_o[n].state_id = c_desc_i.state_id;
        end
        if (start_i) begin
            if (!shape_ok) begin
                fault_o = 1'b1;
                fault_code_o = TENSOR_FAULT_SHAPE_MISMATCH;
            end else if (((node_available_mask_i & node_trust_mask_i & node_cool_mask_i) != {NUM_NODES{1'b1}})) begin
                fault_o = 1'b1;
                fault_code_o = TENSOR_FAULT_NODE_MASKED;
            end else begin
                valid_o = 1'b1;
                for (n = 0; n < NUM_NODES; n++) jobs_o[n].valid = 1'b1;
            end
        end
    end
endmodule
