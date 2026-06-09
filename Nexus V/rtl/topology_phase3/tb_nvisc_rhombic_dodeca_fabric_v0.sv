`timescale 1ns / 1ps

import nvisc_topology_pkg::*;

module tb_nvisc_rhombic_dodeca_fabric_v0;
    logic clk;
    logic rst_n;
    logic inject_valid;
    nvisc_route_flit_t inject_flit;
    logic aegis_allow;
    logic aegis_deny;
    logic [15:0] topo_epoch;
    logic [15:0] therm_epoch;
    logic [15:0] hops;
    logic [15:0] visited;
    logic route_done;
    logic route_fault;
    nvisc_topology_token_t token;
    logic [15:0] node_fault_mask;
    logic [15:0] node_untrusted_mask;
    logic [15:0] node_hot_mask;

    nvisc_rhombic_dodeca_fabric_v0 dut (
        .clk(clk), .rst_n(rst_n),
        .inject_valid_i(inject_valid), .inject_flit_i(inject_flit),
        .aegis_route_allow_i(aegis_allow), .aegis_route_deny_i(aegis_deny),
        .node_fault_mask_i(node_fault_mask),
        .node_untrusted_mask_i(node_untrusted_mask),
        .node_hot_mask_i(node_hot_mask),
        .current_topology_epoch_i(topo_epoch),
        .current_thermal_epoch_i(therm_epoch),
        .route_done_o(route_done), .route_fault_o(route_fault),
        .route_token_o(token),
        .trace_hop_count_o(hops), .trace_visited_o(visited)
    );

    always #5 clk = ~clk;

    task automatic reset_flit;
        begin
            inject_flit = '0;
            inject_flit.valid = 1'b1;
            inject_flit.src_node = 16'd0;
            inject_flit.dst_node = 16'd0;
            inject_flit.current_node = 16'd0;
            inject_flit.policy = ROUTE_FAST;
            inject_flit.branch_id = 32'hA5A5_0001;
            inject_flit.state_id = 32'h0000_0042;
            inject_flit.topology_epoch = topo_epoch;
            inject_flit.thermal_epoch = therm_epoch;
            inject_flit.payload = 64'h1234;
            inject_flit.last = 1'b1;
        end
    endtask

    task automatic run_route(input logic [15:0] src, input logic [15:0] dst, input nvisc_route_policy_e policy);
        begin
            reset_flit();
            inject_flit.src_node = src;
            inject_flit.dst_node = dst;
            inject_flit.current_node = src;
            inject_flit.policy = policy;
            inject_valid = 1'b1;
            @(posedge clk);
            inject_valid = 1'b0;
            repeat (40) begin
                @(posedge clk);
                if (route_done || route_fault) break;
            end
        end
    endtask

    initial begin
        clk = 1'b0; rst_n = 1'b0; inject_valid = 1'b0;
        aegis_allow = 1'b1; aegis_deny = 1'b0;
        topo_epoch = 16'd1; therm_epoch = 16'd1;
        node_fault_mask = '0; node_untrusted_mask = '0; node_hot_mask = '0;
        reset_flit();
        repeat (4) @(posedge clk);
        rst_n = 1'b1;
        repeat (2) @(posedge clk);

        run_route(16'd0, 16'd0, ROUTE_FAST);
        assert(route_done && token.valid) else $fatal("single-node local route failed");

        run_route(16'd0, 16'd1, ROUTE_FAST);
        assert(route_done && token.src_node == 16'd0 && token.dst_node == 16'd1) else $fatal("node0->node1 failed");
        assert(token.branch_id == 32'hA5A5_0001 && token.state_id == 32'h42) else $fatal("lineage fields not preserved");

        run_route(16'd0, 16'd5, ROUTE_FAST);
        assert(route_done && hops >= 16'd5) else $fatal("multi-hop route failed");

        node_untrusted_mask[2] = 1'b1;
        run_route(16'd1, 16'd2, ROUTE_SAFE);
        assert(route_fault) else $fatal("ROUTE_SAFE failed to avoid/fault untrusted node");
        node_untrusted_mask = '0;

        node_hot_mask[3] = 1'b1;
        run_route(16'd2, 16'd3, ROUTE_COOL);
        assert(route_fault) else $fatal("ROUTE_COOL failed to avoid/fault hot node");
        node_hot_mask = '0;

        node_fault_mask[8] = 1'b1;
        run_route(16'd7, 16'd8, ROUTE_FAST);
        assert(route_fault) else $fatal("faulty target route did not fault");
        node_fault_mask = '0;

        aegis_allow = 1'b0; aegis_deny = 1'b1;
        run_route(16'd0, 16'd1, ROUTE_FAST);
        assert(route_fault) else $fatal("Aegis deny did not block route");
        aegis_allow = 1'b1; aegis_deny = 1'b0;

        $display("Phase 3 topology fabric smoke tests passed.");
        $finish;
    end
endmodule
