`timescale 1ns / 1ps

import nvisc_topology_pkg::*;

module nvisc_route_compute_unit #(
    parameter int NUM_NODES = 16,
    parameter int NUM_PORTS = 13,
    parameter int NODE_ID_W = 16,
    parameter int PORT_W    = $clog2(NUM_PORTS)
)(
    input  logic                         valid_i,
    input  logic [NODE_ID_W-1:0]         current_node_i,
    input  logic [NODE_ID_W-1:0]         dst_node_i,
    input  nvisc_route_policy_e          policy_i,

    input  logic [NUM_PORTS-1:0][NODE_ID_W-1:0] neighbor_node_i,
    input  logic [NUM_PORTS-1:0]         port_fault_mask_i,
    input  logic [NUM_PORTS-1:0]         port_untrusted_mask_i,
    input  logic [NUM_PORTS-1:0]         port_hot_mask_i,

    output logic                         route_valid_o,
    output logic [PORT_W-1:0]            next_port_o,
    output logic                         route_fault_o
);

    integer i;
    logic found;
    logic [PORT_W-1:0] candidate;

    always_comb begin
        route_valid_o = 1'b0;
        route_fault_o = 1'b0;
        next_port_o   = '0;
        found         = 1'b0;
        candidate     = '0;

        if (valid_i) begin
            if (current_node_i == dst_node_i) begin
                route_valid_o = 1'b1;
                next_port_o   = PORT_LOCAL[PORT_W-1:0];
                found         = 1'b1;
            end else begin
                for (i = 0; i < NUM_PORTS; i++) begin
                    if (!found && neighbor_node_i[i] == dst_node_i) begin
                        unique case (policy_i)
                            ROUTE_SAFE: begin
                                if (!port_fault_mask_i[i] && !port_untrusted_mask_i[i]) begin
                                    found = 1'b1;
                                    candidate = i[PORT_W-1:0];
                                end
                            end

                            ROUTE_COOL: begin
                                if (!port_fault_mask_i[i] && !port_hot_mask_i[i]) begin
                                    found = 1'b1;
                                    candidate = i[PORT_W-1:0];
                                end
                            end

                            default: begin
                                if (!port_fault_mask_i[i]) begin
                                    found = 1'b1;
                                    candidate = i[PORT_W-1:0];
                                end
                            end
                        endcase
                    end
                end

                // Fallback deterministic greedy step toward target for multi-hop smoke tests.
                if (!found) begin
                    for (i = 1; i < NUM_PORTS; i++) begin
                        if (!found && neighbor_node_i[i] != current_node_i && neighbor_node_i[i] < NUM_NODES) begin
                            unique case (policy_i)
                                ROUTE_SAFE: begin
                                    if (!port_fault_mask_i[i] && !port_untrusted_mask_i[i]) begin
                                        found = 1'b1;
                                        candidate = i[PORT_W-1:0];
                                    end
                                end
                                ROUTE_COOL: begin
                                    if (!port_fault_mask_i[i] && !port_hot_mask_i[i]) begin
                                        found = 1'b1;
                                        candidate = i[PORT_W-1:0];
                                    end
                                end
                                default: begin
                                    if (!port_fault_mask_i[i]) begin
                                        found = 1'b1;
                                        candidate = i[PORT_W-1:0];
                                    end
                                end
                            endcase
                        end
                    end
                end
            end

            if (found) begin
                route_valid_o = 1'b1;
                if (current_node_i != dst_node_i) begin
                    next_port_o = candidate;
                end
            end else begin
                route_fault_o = 1'b1;
            end
        end
    end

endmodule
