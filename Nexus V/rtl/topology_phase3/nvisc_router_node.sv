`timescale 1ns / 1ps

import nvisc_topology_pkg::*;

module nvisc_router_node #(
    parameter int NUM_NODES = 16,
    parameter int NUM_PORTS = 13,
    parameter int FLIT_W    = 192,
    parameter int PORT_W    = $clog2(NUM_PORTS)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic [15:0] node_id_i,

    input  logic [NUM_PORTS-1:0]              in_valid_i,
    input  logic [NUM_PORTS-1:0][FLIT_W-1:0] in_flit_i,
    output logic [NUM_PORTS-1:0]              in_ready_o,

    output logic [NUM_PORTS-1:0]              out_valid_o,
    output logic [NUM_PORTS-1:0][FLIT_W-1:0] out_flit_o,
    input  logic [NUM_PORTS-1:0]              out_ready_i,

    input  logic [NUM_PORTS-1:0][15:0]        neighbor_node_i,
    input  logic [NUM_PORTS-1:0]              port_fault_mask_i,
    input  logic [NUM_PORTS-1:0]              port_untrusted_mask_i,
    input  logic [NUM_PORTS-1:0]              port_hot_mask_i,

    output logic                              route_fault_o
);

    logic [NUM_PORTS-1:0][PORT_W-1:0] route_sel;
    logic [NUM_PORTS-1:0] rcu_valid;
    logic [NUM_PORTS-1:0] rcu_fault;

    genvar p;
    generate
        for (p = 0; p < NUM_PORTS; p++) begin : g_rcu
            nvisc_route_compute_unit #(
                .NUM_NODES(NUM_NODES),
                .NUM_PORTS(NUM_PORTS)
            ) u_rcu (
                .valid_i(in_valid_i[p]),
                .current_node_i(node_id_i),
                .dst_node_i(in_flit_i[p][159:144]),
                .policy_i(nvisc_route_policy_e'(in_flit_i[p][135:133])),
                .neighbor_node_i(neighbor_node_i),
                .port_fault_mask_i(port_fault_mask_i),
                .port_untrusted_mask_i(port_untrusted_mask_i),
                .port_hot_mask_i(port_hot_mask_i),
                .route_valid_o(rcu_valid[p]),
                .next_port_o(route_sel[p]),
                .route_fault_o(rcu_fault[p])
            );
        end
    endgenerate

    nvisc_poly_crossbar #(
        .NUM_PORTS(NUM_PORTS),
        .FLIT_W(FLIT_W)
    ) u_xbar (
        .clk(clk),
        .rst_n(rst_n),
        .in_valid_i(in_valid_i & rcu_valid),
        .in_flit_i(in_flit_i),
        .in_ready_o(in_ready_o),
        .out_valid_o(out_valid_o),
        .out_flit_o(out_flit_o),
        .out_ready_i(out_ready_i),
        .route_sel_i(route_sel)
    );

    assign route_fault_o = |rcu_fault;

endmodule
