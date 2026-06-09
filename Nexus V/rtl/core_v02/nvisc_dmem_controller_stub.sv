`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_dmem_controller_stub #(
    parameter int MEM_WORDS = 256,
    parameter logic [63:0] BASE_ADDR = 64'h0000_0000_0000_0000
)(
    input  logic clk,
    input  logic rst_n,

    input  logic        req_valid_i,
    input  logic        req_is_read_i,
    input  logic        req_is_write_i,
    input  logic [63:0] req_paddr_i,
    input  logic [63:0] req_wdata_i,
    input  logic [7:0]  req_size_bytes_i,
    input  nvisc_mem_domain_e req_mem_domain_i,
    input  nvisc_exec_identity_t req_id_i,

    output logic        resp_valid_o,
    output logic [63:0] resp_rdata_o,
    output logic        resp_write_ack_o,

    output logic        fault_o,
    output logic [15:0] fault_code_o,

    // Debug-friendly mirrors.
    output logic [63:0] dbg_addr_o,
    output logic [63:0] dbg_wdata_o,
    output logic [63:0] dbg_rdata_o,
    output logic        dbg_write_seen_o,
    output logic        dbg_read_seen_o
);

    localparam int ADDR_LSB = 3;

    logic [63:0] mem_q [MEM_WORDS];

    logic [63:0] offset_c;
    logic [63:0] word_index_full_c;
    logic [$clog2(MEM_WORDS)-1:0] word_index_c;
    logic        in_range_c;
    logic        size_ok_c;
    logic        aligned_c;
    logic        op_ok_c;

    integer i;

    assign offset_c     = req_paddr_i - BASE_ADDR;
    assign word_index_full_c = offset_c >> ADDR_LSB;
    assign word_index_c      = word_index_full_c[$clog2(MEM_WORDS)-1:0];

    always_comb begin
        in_range_c = (word_index_full_c < 64'(MEM_WORDS));

        // This stub is intentionally 64-bit only for v0.2 bring-up.
        size_ok_c  = (req_size_bytes_i == 8'd8);
        aligned_c  = (req_paddr_i[2:0] == 3'b000);
        op_ok_c    = req_is_read_i ^ req_is_write_i;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < MEM_WORDS; i = i + 1) begin
                mem_q[i] <= 64'd0;
            end

            resp_valid_o     <= 1'b0;
            resp_rdata_o     <= 64'd0;
            resp_write_ack_o <= 1'b0;

            fault_o          <= 1'b0;
            fault_code_o     <= 16'd0;

            dbg_addr_o       <= 64'd0;
            dbg_wdata_o      <= 64'd0;
            dbg_rdata_o      <= 64'd0;
            dbg_write_seen_o <= 1'b0;
            dbg_read_seen_o  <= 1'b0;
        end else begin
            resp_valid_o     <= 1'b0;
            resp_rdata_o     <= 64'd0;
            resp_write_ack_o <= 1'b0;

            fault_o          <= 1'b0;
            fault_code_o     <= 16'd0;

            dbg_write_seen_o <= 1'b0;
            dbg_read_seen_o  <= 1'b0;

            if (req_valid_i) begin
                dbg_addr_o  <= req_paddr_i;
                dbg_wdata_o <= req_wdata_i;

                if (!op_ok_c) begin
                    fault_o      <= 1'b1;
                    fault_code_o <= 16'h0401;
                end else if (!size_ok_c) begin
                    fault_o      <= 1'b1;
                    fault_code_o <= 16'h0402;
                end else if (!aligned_c) begin
                    fault_o      <= 1'b1;
                    fault_code_o <= 16'h0403;
                end else if (!in_range_c) begin
                    fault_o      <= 1'b1;
                    fault_code_o <= 16'h0404;
                end else if (req_is_write_i) begin
                    mem_q[word_index_c] <= req_wdata_i;
                    resp_valid_o        <= 1'b1;
                    resp_write_ack_o    <= 1'b1;
                    dbg_write_seen_o    <= 1'b1;
                end else if (req_is_read_i) begin
                    resp_valid_o    <= 1'b1;
                    resp_rdata_o    <= mem_q[word_index_c];
                    dbg_rdata_o     <= mem_q[word_index_c];
                    dbg_read_seen_o <= 1'b1;
                end
            end
        end
    end

endmodule
