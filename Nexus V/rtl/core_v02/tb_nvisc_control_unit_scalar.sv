`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module tb_nvisc_control_unit_scalar (
    input  logic        valid_i,
    input  logic [7:0]  instr_class_i,

    input  logic        dec_reg_write_i,
    input  logic        dec_mem_read_i,
    input  logic        dec_mem_write_i,
    input  logic        dec_csr_read_i,
    input  logic        dec_csr_write_i,
    input  logic        dec_illegal_i,

    input  logic [4:0]  rd_i,
    input  logic [4:0]  rs1_i,
    input  logic [4:0]  rs2_i,
    input  logic [63:0] imm_i,

    output logic        alu_valid_o,
    output logic        lsu_valid_o,
    output logic        csr_valid_o,
    output logic        branch_valid_o,
    output logic [2:0]  alu_op_o,

    output logic        reg_write_o,
    output logic        mem_read_o,
    output logic        mem_write_o,
    output logic        csr_read_o,
    output logic        csr_write_o,

    output logic [4:0]  rd_o,
    output logic [4:0]  rs1_o,
    output logic [4:0]  rs2_o,
    output logic [63:0] imm_o,

    output logic        illegal_o,
    output logic        trap_o,
    output logic [15:0] trap_code_o,

    output logic [7:0]  dbg_instr_class_o,
    output logic        dbg_any_valid_o
);

    nvisc_decode_packet_t dec;
    nvisc_mem_domain_e mem_domain_unused;
    nvisc_exec_identity_t id_unused;

    always_comb begin
        dec = '0;
        dec.valid       = valid_i;
        dec.instr_class = nvisc_instr_class_e'(instr_class_i);
        dec.alu_op      = NV_ALU_ADD;
        dec.reg_write   = dec_reg_write_i;
        dec.mem_read    = dec_mem_read_i;
        dec.mem_write   = dec_mem_write_i;
        dec.csr_read    = dec_csr_read_i;
        dec.csr_write   = dec_csr_write_i;
        dec.illegal     = dec_illegal_i;
        dec.rd          = rd_i;
        dec.rs1         = rs1_i;
        dec.rs2         = rs2_i;
        dec.imm         = imm_i;
        dec.mem_domain  = NV_MEM_DATA;
        dec.id          = '0;
    end

    nvisc_control_unit u_ctrl (
        .decode_packet_i(dec),

        .alu_valid_o(alu_valid_o),
        .lsu_valid_o(lsu_valid_o),
        .csr_valid_o(csr_valid_o),
        .branch_valid_o(branch_valid_o),
        .alu_op_o(alu_op_o),

        .reg_write_o(reg_write_o),
        .mem_read_o(mem_read_o),
        .mem_write_o(mem_write_o),
        .csr_read_o(csr_read_o),
        .csr_write_o(csr_write_o),

        .rd_o(rd_o),
        .rs1_o(rs1_o),
        .rs2_o(rs2_o),
        .imm_o(imm_o),

        .mem_domain_o(mem_domain_unused),
        .id_o(id_unused),

        .illegal_o(illegal_o),
        .trap_o(trap_o),
        .trap_code_o(trap_code_o),

        .dbg_instr_class_o(dbg_instr_class_o),
        .dbg_any_valid_o(dbg_any_valid_o)
    );

endmodule
