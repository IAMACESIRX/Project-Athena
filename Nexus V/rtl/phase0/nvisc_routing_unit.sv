`timescale 1ns / 1ps

import nvisc_pkg::*;

module nvisc_routing_unit (
    input  logic                route_valid_i,
    input  logic [15:0]         source_node_i,
    input  logic [15:0]         target_node_i,
    input  nvisc_route_policy_e policy_i,
    input  nvisc_state_token_t  state_token_i,

    output nvisc_route_req_t    route_req_o,
    input  nvisc_route_resp_t   route_resp_i,

    output logic                route_done_o,
    output logic                route_fault_o,
    output logic [15:0]         route_id_o
);

    always_comb begin
        route_req_o = '0;
        route_req_o.valid          = route_valid_i;
        route_req_o.source_node    = source_node_i;
        route_req_o.target_node    = target_node_i;
        route_req_o.policy         = policy_i;
        route_req_o.topology_epoch = state_token_i.topology_epoch;
        route_req_o.thermal_epoch  = state_token_i.thermal_epoch;
        route_req_o.branch_id      = state_token_i.branch_id;
        route_req_o.state_id       = state_token_i.state_id;
    end

    assign route_done_o  = route_resp_i.valid && route_resp_i.ready && !route_resp_i.fault;
    assign route_fault_o = route_resp_i.valid && route_resp_i.fault;
    assign route_id_o    = route_resp_i.route_id;
endmodule
