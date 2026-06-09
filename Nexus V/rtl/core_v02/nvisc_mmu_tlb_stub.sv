`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_mmu_tlb_stub (
    input  logic clk,
    input  logic rst_n,

    input  logic        req_valid_i,
    input  logic        req_is_read_i,
    input  logic        req_is_write_i,
    input  logic [63:0] req_vaddr_i,
    input  logic [63:0] req_wdata_i,
    input  logic [7:0]  req_size_bytes_i,
    input  nvisc_mem_domain_e req_mem_domain_i,
    input  nvisc_exec_identity_t req_id_i,

    output logic        resp_valid_o,
    output logic        resp_is_read_o,
    output logic        resp_is_write_o,
    output logic [63:0] resp_vaddr_o,
    output logic [63:0] resp_paddr_o,
    output logic [63:0] resp_wdata_o,
    output logic [7:0]  resp_size_bytes_o,
    output nvisc_mem_domain_e resp_mem_domain_o,
    output nvisc_exec_identity_t resp_id_o,

    output logic        mmu_fault_o,
    output logic [15:0] mmu_fault_code_o,

    // Debug-friendly mirrors.
    output logic        dbg_translate_valid_o,
    output logic [63:0] dbg_vaddr_o,
    output logic [63:0] dbg_paddr_o,
    output logic        dbg_page_fault_o,
    output logic        dbg_align_fault_o
);

    logic page_fault_c;
    logic align_fault_c;

    always_comb begin
        // Bring-up rule:
        // Addresses in 0xFFFF_xxxx_xxxx_xxxx are treated as unmapped.
        page_fault_c = req_valid_i && (req_vaddr_i[63:48] == 16'hFFFF);

        align_fault_c = 1'b0;
        if (req_valid_i) begin
            unique case (req_size_bytes_i)
                8'd1: align_fault_c = 1'b0;
                8'd2: align_fault_c = req_vaddr_i[0] != 1'b0;
                8'd4: align_fault_c = req_vaddr_i[1:0] != 2'b00;
                8'd8: align_fault_c = req_vaddr_i[2:0] != 3'b000;
                default: align_fault_c = 1'b1;
            endcase
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            resp_valid_o      <= 1'b0;
            resp_is_read_o    <= 1'b0;
            resp_is_write_o   <= 1'b0;
            resp_vaddr_o      <= 64'd0;
            resp_paddr_o      <= 64'd0;
            resp_wdata_o      <= 64'd0;
            resp_size_bytes_o <= 8'd0;
            resp_mem_domain_o <= NV_MEM_DATA;
            resp_id_o         <= '0;

            mmu_fault_o       <= 1'b0;
            mmu_fault_code_o  <= 16'd0;
        end else begin
            resp_valid_o      <= 1'b0;
            resp_is_read_o    <= 1'b0;
            resp_is_write_o   <= 1'b0;
            resp_vaddr_o      <= 64'd0;
            resp_paddr_o      <= 64'd0;
            resp_wdata_o      <= 64'd0;
            resp_size_bytes_o <= 8'd0;
            resp_mem_domain_o <= NV_MEM_DATA;
            resp_id_o         <= '0;

            mmu_fault_o       <= 1'b0;
            mmu_fault_code_o  <= 16'd0;

            if (req_valid_i) begin
                if (page_fault_c) begin
                    mmu_fault_o      <= 1'b1;
                    mmu_fault_code_o <= 16'h0301;
                end else if (align_fault_c) begin
                    mmu_fault_o      <= 1'b1;
                    mmu_fault_code_o <= 16'h0302;
                end else begin
                    resp_valid_o      <= 1'b1;
                    resp_is_read_o    <= req_is_read_i;
                    resp_is_write_o   <= req_is_write_i;
                    resp_vaddr_o      <= req_vaddr_i;

                    // Stub translation:
                    // identity map for now.
                    resp_paddr_o      <= req_vaddr_i;

                    resp_wdata_o      <= req_wdata_i;
                    resp_size_bytes_o <= req_size_bytes_i;
                    resp_mem_domain_o <= req_mem_domain_i;
                    resp_id_o         <= req_id_i;
                end
            end
        end
    end

    assign dbg_translate_valid_o = resp_valid_o;
    assign dbg_vaddr_o           = resp_vaddr_o;
    assign dbg_paddr_o           = resp_paddr_o;
    assign dbg_page_fault_o      = page_fault_c;
    assign dbg_align_fault_o     = align_fault_c;

endmodule
