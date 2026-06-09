`timescale 1ns / 1ps
import nvisc_tensor_pkg::*;

module nvisc_tensor_route_adapter #(
    parameter int NUM_NODES = NUM_TENSOR_NODES
)(
    input  logic clk,
    input  logic rst_n,
    input  logic emit_i,
    input  nvisc_tensor_tile_job_t jobs_i [NUM_NODES],
    input  logic route_ready_i,
    output logic route_req_valid_o,
    output logic [15:0] route_src_node_o,
    output logic [15:0] route_dst_node_o,
    output logic [2:0] route_policy_o,
    input  logic route_done_i,
    input  logic route_fault_i,
    output logic all_routes_done_o,
    output logic route_fault_o
);
    logic [$clog2(NUM_NODES):0] idx_q;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            idx_q <= '0;
            all_routes_done_o <= 1'b0;
            route_fault_o <= 1'b0;
        end else begin
            all_routes_done_o <= 1'b0;
            if (emit_i && route_ready_i && idx_q < NUM_NODES) begin
                idx_q <= idx_q + 1'b1;
            end
            if (idx_q == NUM_NODES) begin
                all_routes_done_o <= 1'b1;
            end
            if (route_fault_i) route_fault_o <= 1'b1;
            if (!emit_i) begin
                idx_q <= '0;
                route_fault_o <= 1'b0;
            end
        end
    end
    assign route_req_valid_o = emit_i && (idx_q < NUM_NODES);
    assign route_src_node_o = 16'd0;
    assign route_dst_node_o = jobs_i[idx_q[$clog2(NUM_NODES)-1:0]].node_id;
    assign route_policy_o = 3'd0;
endmodule
