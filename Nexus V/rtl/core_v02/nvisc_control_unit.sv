`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_control_unit (
    input  nvisc_decode_packet_t decode_packet_i,

    output logic        alu_valid_o,
    output logic        lsu_valid_o,
    output logic        csr_valid_o,
    output logic        branch_valid_o,

    output nvisc_alu_op_e alu_op_o,

    output logic        reg_write_o,
    output logic        mem_read_o,
    output logic        mem_write_o,
    output logic        csr_read_o,
    output logic        csr_write_o,

    output logic [4:0]  rd_o,
    output logic [4:0]  rs1_o,
    output logic [4:0]  rs2_o,
    output logic [63:0] imm_o,

    output nvisc_mem_domain_e mem_domain_o,
    output nvisc_exec_identity_t id_o,

    output logic        illegal_o,
    output logic        trap_o,
    output logic [15:0] trap_code_o,

    // Debug-friendly mirrors.
    output logic [7:0]  dbg_instr_class_o,
    output logic        dbg_any_valid_o
);

    always_comb begin
        alu_valid_o    = 1'b0;
        lsu_valid_o    = 1'b0;
        csr_valid_o    = 1'b0;
        branch_valid_o = 1'b0;
        alu_op_o       = decode_packet_i.alu_op;

        reg_write_o    = 1'b0;
        mem_read_o     = 1'b0;
        mem_write_o    = 1'b0;
        csr_read_o     = 1'b0;
        csr_write_o    = 1'b0;

        rd_o           = decode_packet_i.rd;
        rs1_o          = decode_packet_i.rs1;
        rs2_o          = decode_packet_i.rs2;
        imm_o          = decode_packet_i.imm;

        mem_domain_o   = decode_packet_i.mem_domain;
        id_o           = decode_packet_i.id;

        illegal_o      = 1'b0;
        trap_o         = 1'b0;
        trap_code_o    = 16'd0;

        dbg_instr_class_o = decode_packet_i.instr_class;
        dbg_any_valid_o   = decode_packet_i.valid;

        if (decode_packet_i.valid) begin
            unique case (decode_packet_i.instr_class)
                NV_ICLASS_NOP: begin
                    // No side effects.
                end

                NV_ICLASS_ALU: begin
                    alu_valid_o = 1'b1;
                    reg_write_o = decode_packet_i.reg_write;
                end

                NV_ICLASS_LOAD: begin
                    lsu_valid_o = 1'b1;
                    mem_read_o  = decode_packet_i.mem_read;
                    reg_write_o = decode_packet_i.reg_write;
                end

                NV_ICLASS_STORE: begin
                    lsu_valid_o = 1'b1;
                    mem_write_o = decode_packet_i.mem_write;
                end

                NV_ICLASS_BRANCH: begin
                    branch_valid_o = 1'b1;
                end

                NV_ICLASS_CSR: begin
                    csr_valid_o = 1'b1;
                    csr_read_o  = decode_packet_i.csr_read;
                    csr_write_o = decode_packet_i.csr_write;
                    reg_write_o = decode_packet_i.reg_write;
                end

                default: begin
                    illegal_o   = 1'b1;
                    trap_o      = 1'b1;
                    trap_code_o = 16'h0001;
                end
            endcase

            if (decode_packet_i.illegal) begin
                illegal_o   = 1'b1;
                trap_o      = 1'b1;
                trap_code_o = 16'h0001;
            end
        end
    end

endmodule
