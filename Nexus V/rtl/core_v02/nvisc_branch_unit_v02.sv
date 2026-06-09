`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_branch_unit_v02 (
    input  logic        branch_valid_i,

    input  logic [63:0] pc_i,
    input  logic [63:0] imm_i,

    input  logic [63:0] src_a_i,
    input  logic [63:0] src_b_i,

    output logic        branch_taken_o,
    output logic [63:0] branch_target_o,

    output logic        fault_o,
    output logic [15:0] fault_code_o,

    // Debug-friendly mirrors.
    output logic        dbg_branch_valid_o,
    output logic        dbg_branch_taken_o,
    output logic [63:0] dbg_branch_target_o
);

    always_comb begin
        branch_taken_o  = 1'b0;
        branch_target_o = pc_i + imm_i;

        fault_o         = 1'b0;
        fault_code_o    = 16'd0;

        if (branch_valid_i) begin
            // Bring-up branch mode:
            // BEQ rs1, rs2, imm
            if (src_a_i == src_b_i) begin
                branch_taken_o = 1'b1;
            end
        end
    end

    assign dbg_branch_valid_o  = branch_valid_i;
    assign dbg_branch_taken_o  = branch_taken_o;
    assign dbg_branch_target_o = branch_target_o;

endmodule
