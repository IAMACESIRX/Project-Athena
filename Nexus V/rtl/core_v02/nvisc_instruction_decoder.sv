`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_instruction_decoder (
    input  nvisc_fetch_packet_t  fetch_packet_i,
    output nvisc_decode_packet_t decode_packet_o,

    // C++/Verilator debug-friendly mirrors.
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

    nvisc_decode_packet_t dec;

    logic [6:0] opcode;
    logic [4:0] rd;
    logic [4:0] rs1;
    logic [4:0] rs2;
    logic [2:0] funct3;
    logic [6:0] funct7;
    logic [11:0] imm12_i;
    logic [11:0] imm12_s;
    logic [11:0] imm12_selected;
    logic [63:0] imm_ext;

    always_comb begin
        opcode = fetch_packet_i.instr[6:0];
        rd     = fetch_packet_i.instr[11:7];
        funct3 = fetch_packet_i.instr[14:12];
        rs1    = fetch_packet_i.instr[19:15];
        rs2    = fetch_packet_i.instr[24:20];
        funct7 = fetch_packet_i.instr[31:25];
        imm12_i = fetch_packet_i.instr[31:20];
        imm12_s = {fetch_packet_i.instr[31:25], fetch_packet_i.instr[11:7]};

        // Default immediate format. STORE and BRANCH use split S/B-style immediate.
        imm12_selected = imm12_i;
        if (opcode == 7'h03 || opcode == 7'h04) begin
            imm12_selected = imm12_s;
        end

        imm_ext = {{52{imm12_selected[11]}}, imm12_selected};

        dec = '0;

        dec.valid       = fetch_packet_i.valid;
        dec.pc          = fetch_packet_i.pc;
        dec.instr       = fetch_packet_i.instr;
        dec.opcode      = opcode;
        dec.rd          = rd;
        dec.rs1         = rs1;
        dec.rs2         = rs2;
        dec.imm         = imm_ext;
        dec.id          = fetch_packet_i.id;
        dec.mem_domain  = NV_MEM_DATA;
        dec.alu_op      = NV_ALU_ADD;

        unique case (opcode)
            7'h00: begin
                dec.instr_class = NV_ICLASS_NOP;
            end

            7'h01: begin
                dec.instr_class = NV_ICLASS_ALU;
                dec.reg_write   = 1'b1;

                unique case (funct3)
                    3'b000: begin
                        if (funct7 == 7'b0100000) begin
                            dec.alu_op = NV_ALU_SUB;
                        end else begin
                            dec.alu_op = NV_ALU_ADD;
                        end
                    end

                    3'b111: dec.alu_op = NV_ALU_AND;
                    3'b110: dec.alu_op = NV_ALU_OR;
                    3'b100: dec.alu_op = NV_ALU_XOR;
                    3'b010: dec.alu_op = NV_ALU_SLT;

                    default: begin
                        dec.instr_class = NV_ICLASS_ILLEGAL;
                        dec.reg_write   = 1'b0;
                        dec.illegal     = fetch_packet_i.valid;
                    end
                endcase
            end

            7'h02: begin
                dec.instr_class = NV_ICLASS_LOAD;
                dec.mem_read    = 1'b1;
                dec.reg_write   = 1'b1;
                dec.mem_domain  = NV_MEM_DATA;
        dec.alu_op      = NV_ALU_ADD;
            end

            7'h03: begin
                dec.instr_class = NV_ICLASS_STORE;
                dec.mem_write   = 1'b1;
                dec.mem_domain  = NV_MEM_DATA;
        dec.alu_op      = NV_ALU_ADD;
            end

            7'h04: begin
                dec.instr_class = NV_ICLASS_BRANCH;
                dec.branch      = 1'b1;
            end

            7'h05: begin
                dec.instr_class = NV_ICLASS_CSR;
                dec.csr_read    = 1'b1;
                dec.reg_write   = 1'b1;
            end

            default: begin
                dec.instr_class = NV_ICLASS_ILLEGAL;
                dec.illegal     = fetch_packet_i.valid;
            end
        endcase

        if (!fetch_packet_i.valid) begin
            dec.valid   = 1'b0;
            dec.illegal = 1'b0;
        end
    end

    assign decode_packet_o = dec;

    assign dbg_valid_o       = dec.valid;
    assign dbg_pc_o          = dec.pc;
    assign dbg_instr_o       = dec.instr;
    assign dbg_instr_class_o = dec.instr_class;
    assign dbg_opcode_o      = dec.opcode;
    assign dbg_rd_o          = dec.rd;
    assign dbg_rs1_o         = dec.rs1;
    assign dbg_rs2_o         = dec.rs2;
    assign dbg_imm_o         = dec.imm;
    assign dbg_reg_write_o   = dec.reg_write;
    assign dbg_mem_read_o    = dec.mem_read;
    assign dbg_mem_write_o   = dec.mem_write;
    assign dbg_csr_read_o    = dec.csr_read;
    assign dbg_branch_o      = dec.branch;
    assign dbg_illegal_o     = dec.illegal;

endmodule
