`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_alu_v02 (
    input  logic        alu_valid_i,
    input  logic [2:0]  alu_op_i,

    input  logic [63:0] src_a_i,
    input  logic [63:0] src_b_i,

    output logic        result_valid_o,
    output logic [63:0] result_o,

    output logic        zero_o,
    output logic        negative_o,
    output logic        overflow_o,

    output logic        fault_o,
    output logic [15:0] fault_code_o,

    // Debug-friendly mirrors.
    output logic [2:0]  dbg_alu_op_o,
    output logic [63:0] dbg_src_a_o,
    output logic [63:0] dbg_src_b_o,
    output logic [63:0] dbg_result_o
);

    localparam logic [2:0] ALU_ADD = 3'd0;
    localparam logic [2:0] ALU_SUB = 3'd1;
    localparam logic [2:0] ALU_AND = 3'd2;
    localparam logic [2:0] ALU_OR  = 3'd3;
    localparam logic [2:0] ALU_XOR = 3'd4;
    localparam logic [2:0] ALU_SLT = 3'd5;

    logic [63:0] result_c;
    logic        overflow_c;
    logic        fault_c;
    logic [15:0] fault_code_c;

    always_comb begin
        result_c     = 64'd0;
        overflow_c   = 1'b0;
        fault_c      = 1'b0;
        fault_code_c = 16'd0;

        if (alu_valid_i) begin
            unique case (alu_op_i)
                ALU_ADD: begin
                    result_c = src_a_i + src_b_i;
                    overflow_c = (~(src_a_i[63] ^ src_b_i[63])) &&
                                  (result_c[63] ^ src_a_i[63]);
                end

                ALU_SUB: begin
                    result_c = src_a_i - src_b_i;
                    overflow_c = (src_a_i[63] ^ src_b_i[63]) &&
                                  (result_c[63] ^ src_a_i[63]);
                end

                ALU_AND: begin
                    result_c = src_a_i & src_b_i;
                end

                ALU_OR: begin
                    result_c = src_a_i | src_b_i;
                end

                ALU_XOR: begin
                    result_c = src_a_i ^ src_b_i;
                end

                ALU_SLT: begin
                    result_c = ($signed(src_a_i) < $signed(src_b_i)) ? 64'd1 : 64'd0;
                end

                default: begin
                    fault_c      = 1'b1;
                    fault_code_c = 16'h0201;
                end
            endcase
        end
    end

    assign result_valid_o = alu_valid_i && !fault_c;
    assign result_o       = result_c;

    assign zero_o         = result_valid_o && (result_c == 64'd0);
    assign negative_o     = result_valid_o && result_c[63];
    assign overflow_o     = result_valid_o && overflow_c;

    assign fault_o        = fault_c;
    assign fault_code_o   = fault_code_c;

    assign dbg_alu_op_o   = alu_op_i;
    assign dbg_src_a_o    = src_a_i;
    assign dbg_src_b_o    = src_b_i;
    assign dbg_result_o   = result_c;

endmodule
