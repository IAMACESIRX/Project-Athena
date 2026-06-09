`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_lsu_stub (
    input  logic clk,
    input  logic rst_n,

    input  logic        lsu_valid_i,
    input  logic        mem_read_i,
    input  logic        mem_write_i,

    input  logic [63:0] base_value_i,
    input  logic [63:0] imm_i,
    input  logic [63:0] store_data_i,

    input  logic [7:0]  size_bytes_i,
    input  nvisc_mem_domain_e mem_domain_i,
    input  nvisc_exec_identity_t id_i,

    output nvisc_mem_req_t mem_req_o,

    output logic        lsu_fault_o,
    output logic [15:0] lsu_fault_code_o,

    // Debug-friendly mirrors.
    output logic        dbg_req_valid_o,
    output logic        dbg_req_is_read_o,
    output logic        dbg_req_is_write_o,
    output logic [63:0] dbg_req_vaddr_o,
    output logic [63:0] dbg_req_paddr_o,
    output logic [63:0] dbg_req_wdata_o,
    output logic [7:0]  dbg_req_size_bytes_o,
    output logic [2:0]  dbg_req_mem_domain_o
);

    nvisc_mem_req_t req_q;
    logic [63:0] eff_addr_c;
    logic bad_size_c;
    logic both_read_write_c;
    logic no_op_c;

    assign eff_addr_c = base_value_i + imm_i;

    always_comb begin
        bad_size_c = !(
            size_bytes_i == 8'd1 ||
            size_bytes_i == 8'd2 ||
            size_bytes_i == 8'd4 ||
            size_bytes_i == 8'd8
        );

        both_read_write_c = mem_read_i && mem_write_i;
        no_op_c           = !mem_read_i && !mem_write_i;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            req_q            <= '0;
            lsu_fault_o      <= 1'b0;
            lsu_fault_code_o <= 16'd0;
        end else begin
            req_q            <= '0;
            lsu_fault_o      <= 1'b0;
            lsu_fault_code_o <= 16'd0;

            if (lsu_valid_i) begin
                if (bad_size_c) begin
                    lsu_fault_o      <= 1'b1;
                    lsu_fault_code_o <= 16'h0101;
                end else if (both_read_write_c) begin
                    lsu_fault_o      <= 1'b1;
                    lsu_fault_code_o <= 16'h0102;
                end else if (no_op_c) begin
                    lsu_fault_o      <= 1'b1;
                    lsu_fault_code_o <= 16'h0103;
                end else begin
                    req_q.valid      <= 1'b1;
                    req_q.tx_id      <= 32'h0000_0001;
                    req_q.is_read    <= mem_read_i;
                    req_q.is_write   <= mem_write_i;
                    req_q.is_atomic  <= 1'b0;
                    req_q.vaddr      <= eff_addr_c;

                    // Stub behavior:
                    // no MMU translation yet, so paddr = vaddr.
                    req_q.paddr      <= eff_addr_c;

                    req_q.wdata      <= store_data_i;
                    req_q.size_bytes <= size_bytes_i;
                    req_q.burst_len  <= 8'd1;
                    req_q.mem_domain <= mem_domain_i;
                    req_q.id         <= id_i;
                end
            end
        end
    end

    assign mem_req_o = req_q;

    assign dbg_req_valid_o      = req_q.valid;
    assign dbg_req_is_read_o    = req_q.is_read;
    assign dbg_req_is_write_o   = req_q.is_write;
    assign dbg_req_vaddr_o      = req_q.vaddr;
    assign dbg_req_paddr_o      = req_q.paddr;
    assign dbg_req_wdata_o      = req_q.wdata;
    assign dbg_req_size_bytes_o = req_q.size_bytes;
    assign dbg_req_mem_domain_o = req_q.mem_domain;

endmodule
