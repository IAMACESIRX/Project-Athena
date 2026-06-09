`timescale 1ns / 1ps

import nvisc_pkg::*;

module nvisc_alu_slice #(
    parameter int XLEN_P = XLEN,
    parameter int MLEN_P = MLEN
)(
    input  logic              valid_i,
    input  nvisc_alu_op_e     op_i,
    input  nvisc_domain_e     domain_i,

    input  logic [XLEN_P-1:0] a_i,
    input  logic [XLEN_P-1:0] b_i,
    input  logic [MLEN_P-1:0] m_a_i,
    input  logic [MLEN_P-1:0] m_b_i,

    output logic              valid_o,
    output logic [XLEN_P-1:0] result_o,
    output logic [MLEN_P-1:0] m_result_o,
    output logic              route_req_hint_o,
    output logic              zero_o,
    output logic              negative_o,
    output logic              carry_o,
    output logic              overflow_o
);

    logic [XLEN_P:0] add_ext;
    logic [XLEN_P:0] sub_ext;

    always_comb begin
        valid_o          = valid_i;
        result_o         = '0;
        m_result_o       = '0;
        route_req_hint_o = 1'b0;
        zero_o           = 1'b0;
        negative_o       = 1'b0;
        carry_o          = 1'b0;
        overflow_o       = 1'b0;
        add_ext          = {1'b0, a_i} + {1'b0, b_i};
        sub_ext          = {1'b0, a_i} - {1'b0, b_i};

        unique case (op_i)
            ALU_NOP: begin
                result_o = a_i;
            end
            ALU_ADD: begin
                result_o = add_ext[XLEN_P-1:0];
                carry_o  = add_ext[XLEN_P];
                overflow_o = (~(a_i[XLEN_P-1] ^ b_i[XLEN_P-1])) &
                             (result_o[XLEN_P-1] ^ a_i[XLEN_P-1]);
            end
            ALU_SUB: begin
                result_o = sub_ext[XLEN_P-1:0];
                carry_o  = sub_ext[XLEN_P];
                overflow_o = (a_i[XLEN_P-1] ^ b_i[XLEN_P-1]) &
                             (result_o[XLEN_P-1] ^ a_i[XLEN_P-1]);
            end
            ALU_AND: result_o = a_i & b_i;
            ALU_OR:  result_o = a_i | b_i;
            ALU_XOR: result_o = a_i ^ b_i;
            ALU_NOT: result_o = ~a_i;
            ALU_SHL: result_o = a_i << b_i[$clog2(XLEN_P)-1:0];
            ALU_SHR: result_o = a_i >> b_i[$clog2(XLEN_P)-1:0];
            ALU_CMP: result_o = (a_i == b_i) ? {{(XLEN_P-1){1'b0}}, 1'b1} : '0;
            ALU_MSET: m_result_o = m_a_i;
            ALU_MADD: begin
                unique case (domain_i)
                    DOMAIN_TERN: m_result_o = (m_a_i + m_b_i) % 3;
                    DOMAIN_QUAD: m_result_o = (m_a_i + m_b_i) % 4;
                    default:     m_result_o = m_a_i + m_b_i;
                endcase
            end
            ALU_PASSA: begin
                result_o   = a_i;
                m_result_o = m_a_i;
            end
            ALU_PASSB: begin
                result_o   = b_i;
                m_result_o = m_b_i;
            end
            ALU_ROUTE: begin
                route_req_hint_o = valid_i;
                result_o         = '0;
            end
            default: begin
                valid_o = 1'b0;
            end
        endcase

        zero_o     = (result_o == '0);
        negative_o = result_o[XLEN_P-1];
    end
endmodule
