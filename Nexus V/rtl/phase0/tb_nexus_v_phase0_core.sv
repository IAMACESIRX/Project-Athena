`timescale 1ns / 1ps

import nvisc_pkg::*;

module tb_nexus_v_phase0_core;

    logic clk;
    logic rst_n;

    logic instr_valid;
    nvisc_alu_op_e alu_op;
    nvisc_domain_e domain;
    logic [4:0] src_a;
    logic [4:0] src_b;
    logic [4:0] dst;
    logic dst_we;

    logic dbg_r_we;
    logic [4:0] dbg_r_waddr;
    logic [XLEN-1:0] dbg_r_wdata;

    logic token_state_advance;
    logic [31:0] next_state_id;

    logic g_route_valid;
    logic [15:0] g_source_node;
    logic [15:0] g_target_node;
    nvisc_route_policy_e g_route_policy;
    nvisc_route_policy_e alu_route_policy;

    logic [15:0] node_trusted;
    logic [15:0] node_hot;
    logic [15:0] node_fault;
    logic aegis_route_approved;

    logic [XLEN-1:0] alu_result;
    logic alu_valid;
    logic zero;
    logic negative;
    nvisc_state_token_t state_token;

    logic route_done;
    logic route_fault;
    logic [15:0] route_id;
    nvisc_route_resp_t route_resp;
    nvisc_topology_token_t topology_token;

    nexus_v_phase0_core dut (
        .clk(clk),
        .rst_n(rst_n),
        .instr_valid_i(instr_valid),
        .alu_op_i(alu_op),
        .domain_i(domain),
        .src_a_i(src_a),
        .src_b_i(src_b),
        .dst_i(dst),
        .dst_we_i(dst_we),
        .dbg_r_we_i(dbg_r_we),
        .dbg_r_waddr_i(dbg_r_waddr),
        .dbg_r_wdata_i(dbg_r_wdata),
        .token_state_advance_i(token_state_advance),
        .next_state_id_i(next_state_id),
        .g_route_valid_i(g_route_valid),
        .g_source_node_i(g_source_node),
        .g_target_node_i(g_target_node),
        .g_route_policy_i(g_route_policy),
        .alu_route_policy_i(alu_route_policy),
        .node_trusted_i(node_trusted),
        .node_hot_i(node_hot),
        .node_fault_i(node_fault),
        .aegis_route_approved_i(aegis_route_approved),
        .alu_result_o(alu_result),
        .alu_valid_o(alu_valid),
        .zero_o(zero),
        .negative_o(negative),
        .state_token_o(state_token),
        .route_done_o(route_done),
        .route_fault_o(route_fault),
        .route_id_o(route_id),
        .route_resp_o(route_resp),
        .topology_token_o(topology_token)
    );

    always #5 clk = ~clk;

    task dbg_write(input logic [4:0] addr, input logic [XLEN-1:0] data);
        begin
            dbg_r_we = 1'b1;
            dbg_r_waddr = addr;
            dbg_r_wdata = data;
            @(posedge clk);
            dbg_r_we = 1'b0;
            @(posedge clk);
        end
    endtask

    task clear_inputs;
        begin
            instr_valid = 1'b0;
            alu_op = ALU_NOP;
            domain = DOMAIN_BIN;
            src_a = 5'd0;
            src_b = 5'd0;
            dst = 5'd0;
            dst_we = 1'b0;
            dbg_r_we = 1'b0;
            dbg_r_waddr = 5'd0;
            dbg_r_wdata = '0;
            token_state_advance = 1'b0;
            next_state_id = 32'd0;
            g_route_valid = 1'b0;
            g_source_node = 16'd0;
            g_target_node = 16'd0;
            g_route_policy = ROUTE_FAST;
            alu_route_policy = ROUTE_FAST;
            node_trusted = 16'hFFFF;
            node_hot = 16'h0000;
            node_fault = 16'h0000;
            aegis_route_approved = 1'b1;
        end
    endtask

    initial begin
        clk = 1'b0;
        rst_n = 1'b0;
        clear_inputs();

        repeat (4) @(posedge clk);
        rst_n = 1'b1;
        repeat (2) @(posedge clk);

        assert(state_token.valid == 1'b1) else $fatal("State token invalid after reset");
        assert(state_token.state_id == 32'd0) else $fatal("Initial state_id expected 0");

        // Debug preload and ADD smoke test.
        dbg_write(5'd1, 64'd10);
        dbg_write(5'd2, 64'd32);

        instr_valid = 1'b1;
        alu_op = ALU_ADD;
        src_a = 5'd1;
        src_b = 5'd2;
        dst = 5'd3;
        dst_we = 1'b1;
        @(posedge clk);
        instr_valid = 1'b0;
        dst_we = 1'b0;
        @(posedge clk);
        assert(alu_result == 64'd42) else $fatal("ALU ADD expected 42");

        // ALU_ROUTE fast path: r1 = source node 10, r2 = target node 32 => update to valid small nodes.
        dbg_write(5'd1, 64'd1);
        dbg_write(5'd2, 64'd7);
        instr_valid = 1'b1;
        alu_op = ALU_ROUTE;
        src_a = 5'd1;
        src_b = 5'd2;
        alu_route_policy = ROUTE_FAST;
        @(posedge clk);
        instr_valid = 1'b0;
        @(posedge clk);
        assert(route_done == 1'b1) else $fatal("ALU_ROUTE did not complete");
        assert(route_fault == 1'b0) else $fatal("ALU_ROUTE faulted unexpectedly");
        assert(topology_token.valid == 1'b1) else $fatal("ALU_ROUTE did not create topology token");
        assert(state_token.state_id >= 32'd1) else $fatal("ALU_ROUTE did not advance state token");

        // Dedicated G.ROUTE path.
        g_route_valid = 1'b1;
        g_source_node = 16'd2;
        g_target_node = 16'd8;
        g_route_policy = ROUTE_FAST;
        @(posedge clk);
        g_route_valid = 1'b0;
        @(posedge clk);
        assert(route_done == 1'b1) else $fatal("G.ROUTE did not complete");
        assert(topology_token.source_node == 16'd2) else $fatal("G.ROUTE source not reflected in token");
        assert(topology_token.target_node == 16'd8) else $fatal("G.ROUTE target not reflected in token");

        // Priority smoke test: G.ROUTE should win over simultaneous ALU_ROUTE.
        dbg_write(5'd1, 64'd3);
        dbg_write(5'd2, 64'd4);
        instr_valid = 1'b1;
        alu_op = ALU_ROUTE;
        src_a = 5'd1;
        src_b = 5'd2;
        alu_route_policy = ROUTE_FAST;
        g_route_valid = 1'b1;
        g_source_node = 16'd5;
        g_target_node = 16'd6;
        g_route_policy = ROUTE_FAST;
        @(posedge clk);
        instr_valid = 1'b0;
        g_route_valid = 1'b0;
        @(posedge clk);
        assert(topology_token.source_node == 16'd5) else $fatal("G.ROUTE priority over ALU_ROUTE failed");
        assert(topology_token.target_node == 16'd6) else $fatal("G.ROUTE priority target failed");

        // Route fault smoke test: target out of range.
        g_route_valid = 1'b1;
        g_source_node = 16'd1;
        g_target_node = 16'd99;
        g_route_policy = ROUTE_FAST;
        @(posedge clk);
        g_route_valid = 1'b0;
        @(posedge clk);
        assert(route_fault == 1'b1) else $fatal("Out-of-range G.ROUTE should fault");

        $display("Nexus-V Phase 0 closeout smoke tests passed.");
        $finish;
    end
endmodule
