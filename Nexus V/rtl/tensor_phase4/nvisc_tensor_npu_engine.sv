`timescale 1ns / 1ps
import nvisc_tensor_pkg::*;

module nvisc_tensor_npu_engine #(
    parameter int NUM_NODES = 16,
    parameter int DATA_W = 32,
    parameter int ACC_W = 64,
    parameter int TENSOR_ID_W = 32
)(
    input  logic clk,
    input  logic rst_n,
    input  logic instr_valid_i,
    input  nvisc_tensor_op_e tensor_op_i,
    input  logic [31:0] branch_id_i,
    input  logic [31:0] state_id_i,
    input  logic [TENSOR_ID_W-1:0] tensor_a_id_i,
    input  logic [TENSOR_ID_W-1:0] tensor_b_id_i,
    input  logic [TENSOR_ID_W-1:0] tensor_c_id_i,
    input  logic [15:0] rows_i,
    input  logic [15:0] cols_i,
    input  logic [15:0] inner_dim_i,
    input  logic [NUM_NODES-1:0] node_available_mask_i,
    input  logic [NUM_NODES-1:0] node_trust_mask_i,
    input  logic [NUM_NODES-1:0] node_cool_mask_i,
    input  logic route_req_ready_i,
    input  logic route_done_i,
    input  logic route_fault_i,
    input  logic inject_numeric_fault_i,
    output logic busy_o,
    output logic done_o,
    output logic fault_o,
    output nvisc_tensor_fault_e fault_code_o,
    output logic tensor_result_valid_o,
    output logic [TENSOR_ID_W-1:0] tensor_result_id_o,
    output logic numeric_ok_o,
    output logic npu_audit_req_o,
    output logic npu_sync_valid_o,
    output logic route_req_valid_o,
    output logic [15:0] route_src_node_o,
    output logic [15:0] route_dst_node_o,
    output logic [2:0] route_policy_o
);
    nvisc_tensor_desc_t a_desc, b_desc, c_desc;
    nvisc_tensor_tile_job_t jobs [NUM_NODES];
    logic sched_valid, sched_fault;
    nvisc_tensor_fault_e sched_fault_code;
    logic [NUM_NODES-1:0] done_mask;
    logic signed [ACC_W-1:0] acc [NUM_NODES];
    logic [31:0] branch_id_vec [NUM_NODES];
    logic [31:0] state_id_vec [NUM_NODES];
    logic signed [ACC_W-1:0] fold_sum;
    logic fold_valid;
    logic numeric_fault;
    logic do_tload, do_tmatmul, do_tinfer, do_sync, do_audit;
    logic route_fault_seen;

    always_comb begin
        a_desc = '0; b_desc = '0; c_desc = '0;
        a_desc.valid = 1'b1; b_desc.valid = 1'b1; c_desc.valid = 1'b1;
        a_desc.tensor_id = tensor_a_id_i; b_desc.tensor_id = tensor_b_id_i; c_desc.tensor_id = tensor_c_id_i;
        a_desc.rows = rows_i; a_desc.cols = inner_dim_i;
        b_desc.rows = inner_dim_i; b_desc.cols = cols_i;
        c_desc.rows = rows_i; c_desc.cols = cols_i;
        a_desc.branch_id = branch_id_i; b_desc.branch_id = branch_id_i; c_desc.branch_id = branch_id_i;
        a_desc.state_id = state_id_i; b_desc.state_id = state_id_i; c_desc.state_id = state_id_i;
        a_desc.dtype = TENSOR_DTYPE_INT16; b_desc.dtype = TENSOR_DTYPE_INT16; c_desc.dtype = TENSOR_DTYPE_INT16;
        a_desc.layout = TENSOR_LAYOUT_TILED; b_desc.layout = TENSOR_LAYOUT_TILED; c_desc.layout = TENSOR_LAYOUT_TILED;
    end

    nvisc_tensor_dispatch_unit u_dispatch(.clk(clk), .rst_n(rst_n), .instr_valid_i(instr_valid_i), .tensor_op_i(tensor_op_i), .do_tload_o(do_tload), .do_tmatmul_o(do_tmatmul), .do_tinfer_o(do_tinfer), .do_sync_o(do_sync), .do_audit_o(do_audit));
    nvisc_tensor_tile_scheduler #(.NUM_NODES(NUM_NODES)) u_sched(.clk(clk), .rst_n(rst_n), .start_i(do_tmatmul || do_tinfer), .a_desc_i(a_desc), .b_desc_i(b_desc), .c_desc_i(c_desc), .node_available_mask_i(node_available_mask_i), .node_trust_mask_i(node_trust_mask_i), .node_cool_mask_i(node_cool_mask_i), .valid_o(sched_valid), .jobs_o(jobs), .fault_o(sched_fault), .fault_code_o(sched_fault_code));
    nvisc_tensor_route_adapter #(.NUM_NODES(NUM_NODES)) u_route(.clk(clk), .rst_n(rst_n), .emit_i(sched_valid), .jobs_i(jobs), .route_ready_i(route_req_ready_i), .route_req_valid_o(route_req_valid_o), .route_src_node_o(route_src_node_o), .route_dst_node_o(route_dst_node_o), .route_policy_o(route_policy_o), .route_done_i(route_done_i), .route_fault_i(route_fault_i), .all_routes_done_o(), .route_fault_o(route_fault_seen));
    nvisc_tensor_node_array_16 #(.DATA_W(DATA_W), .ACC_W(ACC_W)) u_nodes(.clk(clk), .rst_n(rst_n), .start_i(sched_valid), .jobs_i(jobs), .done_mask_o(done_mask), .acc_o(acc), .branch_id_o(branch_id_vec), .state_id_o(state_id_vec));
    nvisc_tensor_reduce_fold_unit #(.NUM_NODES(NUM_NODES), .ACC_W(ACC_W)) u_fold(.acc_i(acc), .valid_mask_i(done_mask), .result_valid_o(fold_valid), .sum_o(fold_sum));
    nvisc_tensor_numeric_integrity_unit #(.ACC_W(ACC_W)) u_num(.check_i(fold_valid), .value_i(fold_sum), .inject_nan_i(inject_numeric_fault_i), .inject_overflow_i(1'b0), .numeric_ok_o(numeric_ok_o), .numeric_fault_o(numeric_fault));

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            busy_o <= 1'b0; done_o <= 1'b0; fault_o <= 1'b0; fault_code_o <= TENSOR_FAULT_NONE;
            tensor_result_valid_o <= 1'b0; tensor_result_id_o <= '0; npu_audit_req_o <= 1'b0; npu_sync_valid_o <= 1'b0;
        end else begin
            done_o <= 1'b0; tensor_result_valid_o <= 1'b0; npu_audit_req_o <= 1'b0; npu_sync_valid_o <= 1'b0;
            if (do_tload) begin
                done_o <= 1'b1;
                tensor_result_valid_o <= 1'b1;
                tensor_result_id_o <= tensor_a_id_i;
            end else if (sched_fault) begin
                fault_o <= 1'b1;
                fault_code_o <= sched_fault_code;
            end else if (route_fault_seen) begin
                fault_o <= 1'b1;
                fault_code_o <= TENSOR_FAULT_ROUTE_FAULT;
            end else if (numeric_fault) begin
                fault_o <= 1'b1;
                fault_code_o <= TENSOR_FAULT_NUMERIC;
            end else if (fold_valid && numeric_ok_o) begin
                done_o <= 1'b1;
                tensor_result_valid_o <= 1'b1;
                tensor_result_id_o <= tensor_c_id_i;
                npu_sync_valid_o <= 1'b1;
                npu_audit_req_o <= 1'b1;
            end
            busy_o <= instr_valid_i && !done_o && !fault_o;
        end
    end
endmodule
