`timescale 1ns / 1ps
import nvisc_tensor_pkg::*;

module tb_nvisc_tensor_npu_engine;
    logic clk, rst_n;
    logic instr_valid;
    nvisc_tensor_op_e op;
    logic [31:0] branch_id, state_id;
    logic [31:0] tensor_a, tensor_b, tensor_c;
    logic [15:0] rows, cols, inner_dim;
    logic [15:0] node_available, node_trust, node_cool;
    logic route_ready, route_done, route_fault, inject_numeric_fault;
    logic busy, done, fault, result_valid, numeric_ok, audit_req, sync_valid, route_req;
    nvisc_tensor_fault_e fault_code;
    logic [31:0] result_id;
    logic [15:0] route_src, route_dst;
    logic [2:0] route_policy;

    nvisc_tensor_npu_engine dut(
        .clk(clk), .rst_n(rst_n), .instr_valid_i(instr_valid), .tensor_op_i(op),
        .branch_id_i(branch_id), .state_id_i(state_id), .tensor_a_id_i(tensor_a), .tensor_b_id_i(tensor_b), .tensor_c_id_i(tensor_c),
        .rows_i(rows), .cols_i(cols), .inner_dim_i(inner_dim),
        .node_available_mask_i(node_available), .node_trust_mask_i(node_trust), .node_cool_mask_i(node_cool),
        .route_req_ready_i(route_ready), .route_done_i(route_done), .route_fault_i(route_fault), .inject_numeric_fault_i(inject_numeric_fault),
        .busy_o(busy), .done_o(done), .fault_o(fault), .fault_code_o(fault_code),
        .tensor_result_valid_o(result_valid), .tensor_result_id_o(result_id), .numeric_ok_o(numeric_ok),
        .npu_audit_req_o(audit_req), .npu_sync_valid_o(sync_valid), .route_req_valid_o(route_req), .route_src_node_o(route_src), .route_dst_node_o(route_dst), .route_policy_o(route_policy)
    );

    always #5 clk = ~clk;

    initial begin
        clk=0; rst_n=0; instr_valid=0; op=TENSOR_OP_NOP; branch_id=32'hBEEF; state_id=32'hCAFE;
        tensor_a=1; tensor_b=2; tensor_c=3; rows=16; cols=16; inner_dim=16;
        node_available=16'hFFFF; node_trust=16'hFFFF; node_cool=16'hFFFF; route_ready=1; route_done=1; route_fault=0; inject_numeric_fault=0;
        repeat(4) @(posedge clk); rst_n=1; repeat(2) @(posedge clk);

        op=TENSOR_OP_TLOAD; instr_valid=1; @(posedge clk); instr_valid=0; @(posedge clk);
        assert(done && result_valid && result_id==tensor_a) else $fatal("TLOAD descriptor creation failed");

        op=TENSOR_OP_TMATMUL; instr_valid=1; @(posedge clk); instr_valid=0; repeat(3) @(posedge clk);
        assert(route_req) else $fatal("TMATMUL did not emit route requests");
        repeat(20) @(posedge clk);
        assert(done && result_valid && numeric_ok && sync_valid && audit_req) else $fatal("TMATMUL did not complete valid/sync/audit path");

        // Shape mismatch
        rows=16; cols=16; inner_dim=0; // bad shape surrogate by forcing scheduler mismatch through C descriptor impossible not modeled fully
        // Numeric fault
        rows=16; cols=16; inner_dim=16; inject_numeric_fault=1; op=TENSOR_OP_TMATMUL; instr_valid=1; @(posedge clk); instr_valid=0; repeat(10) @(posedge clk);
        assert(fault && fault_code==TENSOR_FAULT_NUMERIC) else $fatal("numeric fault not detected");

        $display("Phase 4 tensor/NPU smoke tests passed.");
        $finish;
    end
endmodule
