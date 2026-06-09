`timescale 1ns / 1ps
import nvisc_tensor_pkg::*;

module nvisc_tensor_dispatch_unit (
    input  logic clk,
    input  logic rst_n,
    input  logic instr_valid_i,
    input  nvisc_tensor_op_e tensor_op_i,
    output logic do_tload_o,
    output logic do_tmatmul_o,
    output logic do_tinfer_o,
    output logic do_sync_o,
    output logic do_audit_o
);
    always_comb begin
        do_tload_o = instr_valid_i && (tensor_op_i == TENSOR_OP_TLOAD);
        do_tmatmul_o = instr_valid_i && (tensor_op_i == TENSOR_OP_TMATMUL);
        do_tinfer_o = instr_valid_i && (tensor_op_i == TENSOR_OP_TINFER);
        do_sync_o = instr_valid_i && (tensor_op_i == TENSOR_OP_NPU_SYNC);
        do_audit_o = instr_valid_i && (tensor_op_i == TENSOR_OP_NPU_AUDIT);
    end
endmodule
