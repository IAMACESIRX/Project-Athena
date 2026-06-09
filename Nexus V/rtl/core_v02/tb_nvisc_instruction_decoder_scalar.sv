`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module tb_nvisc_instruction_decoder_scalar (
    input  logic        valid_i,
    input  logic [63:0] pc_i,
    input  logic [31:0] instr_i,

    output logic        dbg_valid_o,
    output logic [63:0] dbg_pc_o,
    output logic [31:0] dbg_instr_o,
    output logic [7:0]  dbg_instr_class_o,
    output logic [6:0]  dbg_opcode_o,
    output logic [4:0]  dbg_rd_o,
    output logic [4:0]  dbg_rs1_o,
    output logic [4:0]  dbg_rs2_o,
    output logic [63:0] dbg_imm_o,
    output logic        dbg_reg_write_o,
    output logic        dbg_mem_read_o,
    output logic        dbg_mem_write_o,
    output logic        dbg_csr_read_o,
    output logic        dbg_branch_o,
    output logic        dbg_illegal_o
);

    nvisc_fetch_packet_t fetch_packet;
    nvisc_decode_packet_t decode_packet_unused;
    nvisc_exec_identity_t id_zero;

    assign id_zero = '0;

    always_comb begin
        fetch_packet       = '0;
        fetch_packet.valid = valid_i;
        fetch_packet.pc    = pc_i;
        fetch_packet.instr = instr_i;
        fetch_packet.id    = id_zero;
    end

    nvisc_instruction_decoder u_dec (
        .fetch_packet_i(fetch_packet),
        .decode_packet_o(decode_packet_unused),

        .dbg_valid_o(dbg_valid_o),
        .dbg_pc_o(dbg_pc_o),
        .dbg_instr_o(dbg_instr_o),
        .dbg_instr_class_o(dbg_instr_class_o),
        .dbg_opcode_o(dbg_opcode_o),
        .dbg_rd_o(dbg_rd_o),
        .dbg_rs1_o(dbg_rs1_o),
        .dbg_rs2_o(dbg_rs2_o),
        .dbg_imm_o(dbg_imm_o),
        .dbg_reg_write_o(dbg_reg_write_o),
        .dbg_mem_read_o(dbg_mem_read_o),
        .dbg_mem_write_o(dbg_mem_write_o),
        .dbg_csr_read_o(dbg_csr_read_o),
        .dbg_branch_o(dbg_branch_o),
        .dbg_illegal_o(dbg_illegal_o)
    );

endmodule
