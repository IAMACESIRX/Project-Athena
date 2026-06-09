`timescale 1ns / 1ps
import nvisc_rsm_pkg::*;

module nvisc_rsm_phys_alloc #(
    parameter int NUM_PAGES_P  = 256,
    parameter int PADDR_W_P    = PADDR_W,
    parameter int PAGE_BYTES_P = 4096,
    parameter int PAGE_IDX_W_P = $clog2(NUM_PAGES_P),
    parameter logic [PADDR_W_P-1:0] PHYS_BASE_ADDR_P = 32'h0000_0000
)(
    input  logic clk,
    input  logic rst_n,

    input  logic alloc_req_i,
    output logic alloc_ready_o,
    output logic [PADDR_W_P-1:0] alloc_paddr_o,
    output logic [PAGE_IDX_W_P-1:0] alloc_page_idx_o,
    input  logic alloc_take_i,

    input  logic free_req_i,
    input  logic [PADDR_W_P-1:0] free_paddr_i,
    output logic free_ok_o,
    output logic free_fault_o,

    input  logic seal_req_i,
    input  logic [PADDR_W_P-1:0] seal_paddr_i,
    input  logic unseal_req_i,
    input  logic [PADDR_W_P-1:0] unseal_paddr_i,

    output logic empty_o,
    output logic full_o,
    output logic [PAGE_IDX_W_P:0] free_count_o,
    output logic alloc_fault_o
);
    logic [NUM_PAGES_P-1:0] allocated_bitmap;
    logic [NUM_PAGES_P-1:0] sealed_bitmap;
    logic [PAGE_IDX_W_P-1:0] first_free_idx;
    logic found_free;
    logic [PAGE_IDX_W_P-1:0] free_idx;
    logic [PAGE_IDX_W_P-1:0] seal_idx;
    logic [PAGE_IDX_W_P-1:0] unseal_idx;

    integer i;

    function automatic [PADDR_W_P-1:0] idx_to_paddr(input logic [PAGE_IDX_W_P-1:0] idx);
        idx_to_paddr = PHYS_BASE_ADDR_P + (idx * PAGE_BYTES_P);
    endfunction

    function automatic [PAGE_IDX_W_P-1:0] paddr_to_idx(input logic [PADDR_W_P-1:0] paddr);
        paddr_to_idx = (paddr - PHYS_BASE_ADDR_P) / PAGE_BYTES_P;
    endfunction

    always_comb begin
        found_free = 1'b0;
        first_free_idx = '0;
        for (i = 0; i < NUM_PAGES_P; i++) begin
            if (!found_free && !allocated_bitmap[i] && !sealed_bitmap[i]) begin
                found_free = 1'b1;
                first_free_idx = i[PAGE_IDX_W_P-1:0];
            end
        end
    end

    assign alloc_ready_o    = alloc_req_i && found_free;
    assign alloc_page_idx_o = first_free_idx;
    assign alloc_paddr_o    = idx_to_paddr(first_free_idx);
    assign empty_o          = !found_free;
    assign full_o           = ((allocated_bitmap | sealed_bitmap) == {NUM_PAGES_P{1'b1}});
    assign alloc_fault_o    = alloc_req_i && !found_free;

    always_comb begin
        free_count_o = '0;
        for (i = 0; i < NUM_PAGES_P; i++) begin
            if (!allocated_bitmap[i] && !sealed_bitmap[i]) begin
                free_count_o = free_count_o + 1'b1;
            end
        end
    end

    always_comb begin
        free_idx = paddr_to_idx(free_paddr_i);
        seal_idx = paddr_to_idx(seal_paddr_i);
        unseal_idx = paddr_to_idx(unseal_paddr_i);
        free_ok_o = 1'b0;
        free_fault_o = 1'b0;
        if (free_req_i) begin
            if (sealed_bitmap[free_idx] || !allocated_bitmap[free_idx]) begin
                free_fault_o = 1'b1;
            end else begin
                free_ok_o = 1'b1;
            end
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            allocated_bitmap <= '0;
            sealed_bitmap <= '0;
        end else begin
            if (alloc_req_i && alloc_take_i && found_free) begin
                allocated_bitmap[first_free_idx] <= 1'b1;
            end
            if (free_req_i && free_ok_o) begin
                allocated_bitmap[free_idx] <= 1'b0;
            end
            if (seal_req_i) begin
                sealed_bitmap[seal_idx] <= 1'b1;
            end
            if (unseal_req_i) begin
                sealed_bitmap[unseal_idx] <= 1'b0;
            end
        end
    end
endmodule
