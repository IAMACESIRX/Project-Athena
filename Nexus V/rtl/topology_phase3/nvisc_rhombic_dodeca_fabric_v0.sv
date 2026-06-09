`timescale 1ns / 1ps

import nvisc_pkg::*;

import nvisc_topology_pkg::*;

module nvisc_rhombic_dodeca_fabric_v0 #(
    parameter int NUM_NODES = 16,
    parameter int NUM_PORTS = 13,
    parameter int FLIT_W    = 192
)(
    input  logic clk,
    input  logic rst_n,

    input  logic inject_valid_i,
    input nvisc_topology_pkg::nvisc_route_flit_t inject_flit_i,
    input  logic aegis_route_allow_i,
    input  logic aegis_route_deny_i,

    input  logic [NUM_NODES-1:0] node_fault_mask_i,
    input  logic [NUM_NODES-1:0] node_untrusted_mask_i,
    input  logic [NUM_NODES-1:0] node_hot_mask_i,

    input  logic [15:0] current_topology_epoch_i,
    input  logic [15:0] current_thermal_epoch_i,

    output logic route_done_o,
    output logic route_fault_o,
    output nvisc_topology_pkg::nvisc_topology_token_t route_token_o,

    output logic [15:0] trace_hop_count_o,
    output logic [NUM_NODES-1:0] trace_visited_o
);
    nvisc_topology_pkg::nvisc_route_flit_t flit_q;
    logic active_q;
    logic [15:0] route_counter_q;
    logic [15:0] next_node;

    function automatic logic [15:0] step_toward(input logic [15:0] cur, input logic [15:0] dst);
        if (cur == dst) step_toward = cur;
        else if (cur < dst) step_toward = cur + 16'd1;
        else step_toward = cur - 16'd1;
    endfunction

    function automatic logic policy_blocks(input nvisc_route_policy_e policy, input logic [15:0] node);
        logic blocked;
        begin
            blocked = 1'b0;
            if (node >= NUM_NODES) blocked = 1'b1;
            else begin
                if (node_fault_mask_i[node[3:0]]) blocked = 1'b1;
                if (policy == ROUTE_SAFE && node_untrusted_mask_i[node[3:0]]) blocked = 1'b1;
                if (policy == ROUTE_COOL && node_hot_mask_i[node[3:0]]) blocked = 1'b1;
            end
            policy_blocks = blocked;
        end
    endfunction

    always_comb begin
        next_node = step_toward(flit_q.current_node, flit_q.dst_node);
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            flit_q <= '0;
            active_q <= 1'b0;
            route_counter_q <= 16'd1;
            route_done_o <= 1'b0;
            route_fault_o <= 1'b0;
            route_token_o <= '0;
            trace_hop_count_o <= 16'd0;
            trace_visited_o <= '0;
        end else begin
            route_done_o <= 1'b0;
            route_fault_o <= 1'b0;

            if (inject_valid_i && !active_q) begin
                if (aegis_route_deny_i || !aegis_route_allow_i) begin
                    route_fault_o <= 1'b1;
                    route_token_o.valid <= 1'b0;
                    route_token_o.faulted <= 1'b1;
                end else begin
                    active_q <= 1'b1;
                    flit_q <= inject_flit_i;
                    flit_q.route_id <= route_counter_q;
                    flit_q.current_node <= inject_flit_i.src_node;
                    flit_q.hop_count <= 8'd0;
                    trace_hop_count_o <= 16'd0;
                    trace_visited_o <= '0;
                    trace_visited_o[inject_flit_i.src_node[3:0]] <= 1'b1;
                end
            end else if (active_q) begin
                if (flit_q.current_node == flit_q.dst_node) begin
                    route_done_o <= 1'b1;
                    active_q <= 1'b0;
                    route_token_o.valid <= 1'b1;
                    route_token_o.route_id <= flit_q.route_id;
                    route_token_o.src_node <= flit_q.src_node;
                    route_token_o.dst_node <= flit_q.dst_node;
                    route_token_o.path_id <= flit_q.route_id;
                    route_token_o.policy <= nvisc_route_policy_e'(flit_q.policy);
                    route_token_o.branch_id <= flit_q.branch_id;
                    route_token_o.state_id <= flit_q.state_id;
                    route_token_o.topology_epoch <= current_topology_epoch_i;
                    route_token_o.thermal_epoch <= current_thermal_epoch_i;
                    route_token_o.aegis_approved <= aegis_route_allow_i;
                    route_token_o.completed <= 1'b1;
                    route_token_o.faulted <= 1'b0;
                    route_counter_q <= route_counter_q + 16'd1;
                end else if (flit_q.hop_count >= 8'd32 || policy_blocks(nvisc_route_policy_e'(flit_q.policy), next_node)) begin
                    route_fault_o <= 1'b1;
                    active_q <= 1'b0;
                    route_token_o.valid <= 1'b0;
                    route_token_o.route_id <= flit_q.route_id;
                    route_token_o.src_node <= flit_q.src_node;
                    route_token_o.dst_node <= flit_q.dst_node;
                    route_token_o.policy <= nvisc_route_policy_e'(flit_q.policy);
                    route_token_o.branch_id <= flit_q.branch_id;
                    route_token_o.state_id <= flit_q.state_id;
                    route_token_o.topology_epoch <= current_topology_epoch_i;
                    route_token_o.thermal_epoch <= current_thermal_epoch_i;
                    route_token_o.aegis_approved <= aegis_route_allow_i;
                    route_token_o.completed <= 1'b0;
                    route_token_o.faulted <= 1'b1;
                end else begin
                    flit_q.current_node <= next_node;
                    flit_q.hop_count <= flit_q.hop_count + 8'd1;
                    trace_hop_count_o <= trace_hop_count_o + 16'd1;
                    trace_visited_o[next_node[3:0]] <= 1'b1;
                end
            end
        end
    end

endmodule
