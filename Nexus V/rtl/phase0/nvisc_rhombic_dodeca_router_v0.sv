`timescale 1ns / 1ps

import nvisc_pkg::*;

module nvisc_rhombic_dodeca_router_v0 #(
    parameter int NODE_COUNT = 16
)(
    input  logic clk,
    input  logic rst_n,

    input  nvisc_route_req_t route_req_i,

    input  logic [2:0] privilege_level_i,
    input  logic       aegis_route_approved_i,

    input  logic [NODE_COUNT-1:0] node_trusted_i,
    input  logic [NODE_COUNT-1:0] node_hot_i,
    input  logic [NODE_COUNT-1:0] node_fault_i,

    output nvisc_route_resp_t    route_resp_o,
    output nvisc_topology_token_t topology_token_o
);

    nvisc_route_resp_t     resp_q;
    nvisc_topology_token_t token_q;

    logic source_in_range;
    logic target_in_range;
    logic source_ok;
    logic target_ok;
    logic safe_ok;
    logic cool_ok;
    logic policy_ok;
    logic [15:0] path_id_comb;

    assign source_in_range = (route_req_i.source_node < NODE_COUNT);
    assign target_in_range = (route_req_i.target_node < NODE_COUNT);

    assign source_ok = source_in_range && !node_fault_i[route_req_i.source_node[$clog2(NODE_COUNT)-1:0]];
    assign target_ok = target_in_range && !node_fault_i[route_req_i.target_node[$clog2(NODE_COUNT)-1:0]];

    assign safe_ok = source_in_range && target_in_range &&
                     node_trusted_i[route_req_i.source_node[$clog2(NODE_COUNT)-1:0]] &&
                     node_trusted_i[route_req_i.target_node[$clog2(NODE_COUNT)-1:0]];

    assign cool_ok = source_in_range && target_in_range &&
                     !node_hot_i[route_req_i.source_node[$clog2(NODE_COUNT)-1:0]] &&
                     !node_hot_i[route_req_i.target_node[$clog2(NODE_COUNT)-1:0]];

    always_comb begin
        policy_ok = 1'b0;
        unique case (route_req_i.policy)
            ROUTE_FAST:      policy_ok = source_ok && target_ok;
            ROUTE_SAFE:      policy_ok = source_ok && target_ok && safe_ok && aegis_route_approved_i;
            ROUTE_COOL:      policy_ok = source_ok && target_ok && cool_ok;
            ROUTE_LOW_POWER: policy_ok = source_ok && target_ok;
            ROUTE_REDUNDANT: policy_ok = source_ok && target_ok && safe_ok && cool_ok;
            default:         policy_ok = 1'b0;
        endcase
    end

    assign path_id_comb = {route_req_i.source_node[5:0], route_req_i.target_node[5:0], route_req_i.policy[2:0], 1'b0};

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            resp_q  <= '0;
            token_q <= '0;
        end else begin
            resp_q <= '0;

            if (route_req_i.valid) begin
                resp_q.ready          <= 1'b1;
                resp_q.source_node    <= route_req_i.source_node;
                resp_q.target_node    <= route_req_i.target_node;
                resp_q.policy         <= route_req_i.policy;
                resp_q.topology_epoch <= route_req_i.topology_epoch;
                resp_q.thermal_epoch  <= route_req_i.thermal_epoch;

                if (!source_in_range || !target_in_range || !policy_ok) begin
                    resp_q.valid <= 1'b1;
                    resp_q.fault <= 1'b1;
                    token_q      <= '0;
                end else begin
                    resp_q.valid            <= 1'b1;
                    resp_q.fault            <= 1'b0;
                    resp_q.route_id         <= path_id_comb;
                    resp_q.selected_path_id <= path_id_comb;
                    resp_q.token_id         <= {8'h52, route_req_i.source_node[7:0], route_req_i.target_node[7:0], route_req_i.policy};

                    token_q.valid           <= 1'b1;
                    token_q.token_id        <= {8'h52, route_req_i.source_node[7:0], route_req_i.target_node[7:0], route_req_i.policy};
                    token_q.source_node     <= route_req_i.source_node;
                    token_q.target_node     <= route_req_i.target_node;
                    token_q.path_id         <= path_id_comb;
                    token_q.policy          <= route_req_i.policy;
                    token_q.topology_epoch  <= route_req_i.topology_epoch;
                    token_q.thermal_epoch   <= route_req_i.thermal_epoch;
                    token_q.privilege_level <= privilege_level_i;
                    token_q.aegis_approved  <= aegis_route_approved_i;
                end
            end
        end
    end

    assign route_resp_o      = resp_q;
    assign topology_token_o  = token_q;
endmodule
