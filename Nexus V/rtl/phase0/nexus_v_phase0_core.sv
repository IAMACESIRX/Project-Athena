`timescale 1ns / 1ps

import nvisc_pkg::*;

module nexus_v_phase0_core (
    input  logic clk,
    input  logic rst_n,

    input  logic          instr_valid_i,
    input  nvisc_alu_op_e alu_op_i,
    input  nvisc_domain_e domain_i,

    input  logic [4:0]    src_a_i,
    input  logic [4:0]    src_b_i,
    input  logic [4:0]    dst_i,
    input  logic          dst_we_i,

    input  logic          dbg_r_we_i,
    input  logic [4:0]    dbg_r_waddr_i,
    input  logic [XLEN-1:0] dbg_r_wdata_i,

    input  logic          token_state_advance_i,
    input  logic [31:0]   next_state_id_i,

    // Dedicated routing unit path, used by decoded G.ROUTE / G.GEO_PATH.
    input  logic                g_route_valid_i,
    input  logic [15:0]         g_source_node_i,
    input  logic [15:0]         g_target_node_i,
    input  nvisc_route_policy_e g_route_policy_i,

    // ALU_ROUTE fast-path policy, used when alu_op_i == ALU_ROUTE.
    input  nvisc_route_policy_e alu_route_policy_i,

    input  logic [15:0] node_trusted_i,
    input  logic [15:0] node_hot_i,
    input  logic [15:0] node_fault_i,
    input  logic        aegis_route_approved_i,

    output logic [XLEN-1:0] alu_result_o,
    output logic            alu_valid_o,
    output logic            zero_o,
    output logic            negative_o,
    output nvisc_state_token_t state_token_o,

    output logic            route_done_o,
    output logic            route_fault_o,
    output logic [15:0]     route_id_o,
    output nvisc_route_resp_t route_resp_o,
    output nvisc_topology_token_t topology_token_o
);

    logic [XLEN-1:0] r_a;
    logic [XLEN-1:0] r_b;
    logic [XLEN-1:0] alu_result;
    logic [MLEN-1:0] m_dummy_a;
    logic [MLEN-1:0] m_dummy_b;
    logic [MLEN-1:0] m_result;
    logic carry;
    logic overflow;
    logic route_req_hint;

    nvisc_state_token_t state_token;
    nvisc_route_req_t   alu_route_req;
    nvisc_route_req_t   g_route_req;
    nvisc_route_req_t   selected_route_req;
    nvisc_route_resp_t  route_resp;
    nvisc_topology_token_t topology_token;

    logic route_success;
    logic state_advance_comb;
    logic [31:0] next_state_id_comb;

    assign m_dummy_a = '0;
    assign m_dummy_b = '0;

    nvisc_regfile u_regfile (
        .clk(clk),
        .rst_n(rst_n),
        .r_we((dst_we_i && alu_valid_o && alu_op_i != ALU_ROUTE) || dbg_r_we_i),
        .r_waddr(dbg_r_we_i ? dbg_r_waddr_i : dst_i),
        .r_wdata(dbg_r_we_i ? dbg_r_wdata_i : alu_result),
        .r_raddr_a(src_a_i),
        .r_raddr_b(src_b_i),
        .r_rdata_a(r_a),
        .r_rdata_b(r_b),
        .f_we(1'b0), .f_waddr('0), .f_wdata('0), .f_raddr_a('0), .f_rdata_a(),
        .d_we(1'b0), .d_waddr('0), .d_wdata('0), .d_raddr_a('0), .d_rdata_a(),
        .m_we(1'b0), .m_waddr('0), .m_wdata('0), .m_raddr_a('0), .m_rdata_a(),
        .t_we(1'b0), .t_waddr('0), .t_wdata('0), .t_raddr_a('0), .t_rdata_a(),
        .s_we(1'b0), .s_waddr('0), .s_wdata('0), .s_raddr_a('0), .s_rdata_a(),
        .p_we(1'b0), .p_waddr('0), .p_wdata('0), .p_raddr_a('0), .p_rdata_a(),
        .c_we(1'b0), .c_waddr('0), .c_wdata('0), .c_raddr_a('0), .c_rdata_a()
    );

    nvisc_alu_slice u_alu (
        .valid_i(instr_valid_i),
        .op_i(alu_op_i),
        .domain_i(domain_i),
        .a_i(r_a),
        .b_i(r_b),
        .m_a_i(m_dummy_a),
        .m_b_i(m_dummy_b),
        .valid_o(alu_valid_o),
        .result_o(alu_result),
        .m_result_o(m_result),
        .route_req_hint_o(route_req_hint),
        .zero_o(zero_o),
        .negative_o(negative_o),
        .carry_o(carry),
        .overflow_o(overflow)
    );

    always_comb begin
        alu_route_req = '0;
        if (instr_valid_i && route_req_hint) begin
            alu_route_req.valid          = 1'b1;
            alu_route_req.source_node    = r_a[15:0];
            alu_route_req.target_node    = r_b[15:0];
            alu_route_req.policy         = alu_route_policy_i;
            alu_route_req.topology_epoch = state_token.topology_epoch;
            alu_route_req.thermal_epoch  = state_token.thermal_epoch;
            alu_route_req.branch_id      = state_token.branch_id;
            alu_route_req.state_id       = state_token.state_id;
        end
    end

    nvisc_routing_unit u_routing_unit (
        .route_valid_i(g_route_valid_i),
        .source_node_i(g_source_node_i),
        .target_node_i(g_target_node_i),
        .policy_i(g_route_policy_i),
        .state_token_i(state_token),
        .route_req_o(g_route_req),
        .route_resp_i(route_resp),
        .route_done_o(route_done_o),
        .route_fault_o(route_fault_o),
        .route_id_o(route_id_o)
    );

    nvisc_route_req_arbiter u_route_arbiter (
        .alu_req_i(alu_route_req),
        .g_req_i(g_route_req),
        .route_req_o(selected_route_req)
    );

    nvisc_rhombic_dodeca_router_v0 #(.NODE_COUNT(16)) u_router (
        .clk(clk),
        .rst_n(rst_n),
        .route_req_i(selected_route_req),
        .privilege_level_i(3'd1),
        .aegis_route_approved_i(aegis_route_approved_i),
        .node_trusted_i(node_trusted_i),
        .node_hot_i(node_hot_i),
        .node_fault_i(node_fault_i),
        .route_resp_o(route_resp),
        .topology_token_o(topology_token)
    );

    assign route_success      = route_resp.valid && route_resp.ready && !route_resp.fault;
    assign state_advance_comb = token_state_advance_i || route_success;
    assign next_state_id_comb = route_success ? (state_token.state_id + 32'd1) : next_state_id_i;

    nvisc_state_token_if u_state_token (
        .clk(clk),
        .rst_n(rst_n),
        .update_i(1'b0),
        .token_i('0),
        .branch_advance_i(1'b0),
        .next_branch_id_i('0),
        .state_advance_i(state_advance_comb),
        .next_state_id_i(next_state_id_comb),
        .commit_advance_i(1'b0),
        .next_commit_id_i('0),
        .topology_epoch_inc_i(1'b0),
        .thermal_epoch_inc_i(1'b0),
        .set_committed_i(1'b0),
        .set_sealed_i(1'b0),
        .set_rollback_valid_i(1'b0),
        .token_o(state_token)
    );

    assign alu_result_o      = alu_result;
    assign state_token_o     = state_token;
    assign route_resp_o      = route_resp;
    assign topology_token_o  = topology_token;
endmodule
