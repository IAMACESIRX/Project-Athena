`timescale 1ns / 1ps
import nvisc_rsm_pkg::*;

typedef enum logic [2:0] {
    RSM_IDLE,
    RSM_CHECK_SEAL,
    RSM_ALLOC,
    RSM_REMAP,
    RSM_DONE,
    RSM_FAULT
} nvisc_rsm_fsm_e;

module nvisc_rsm_cow_map #(
    parameter int NUM_PAGES_P  = 256,
    parameter int PAGE_IDX_W_P = $clog2(NUM_PAGES_P),
    parameter int PADDR_W_P    = PADDR_W
)(
    input  logic clk,
    input  logic rst_n,

    input  logic cow_fault_i,
    input  logic [PAGE_IDX_W_P-1:0] logical_page_i,
    input  logic sealed_branch_i,
    input  logic sealed_state_i,
    input  logic sealed_page_i,

    output logic alloc_req_o,
    input  logic alloc_ready_i,
    input  logic [PADDR_W_P-1:0] alloc_paddr_i,
    output logic alloc_take_o,

    output logic remap_valid_o,
    output logic [PAGE_IDX_W_P-1:0] remap_lpage_o,
    output logic [PADDR_W_P-1:0] remap_paddr_o,
    output logic cow_resolved_o,
    output logic cow_fault_o
);
    logic [PADDR_W_P-1:0] page_map_q [NUM_PAGES_P];
    logic [NUM_PAGES_P-1:0] page_valid_q;
    nvisc_rsm_fsm_e state_q, state_d;

    always_comb begin
        state_d = state_q;
        alloc_req_o = 1'b0;
        alloc_take_o = 1'b0;
        remap_valid_o = 1'b0;
        remap_lpage_o = logical_page_i;
        remap_paddr_o = alloc_paddr_i;
        cow_resolved_o = 1'b0;
        cow_fault_o = 1'b0;

        unique case (state_q)
            RSM_IDLE: begin
                if (cow_fault_i) state_d = RSM_CHECK_SEAL;
            end
            RSM_CHECK_SEAL: begin
                if (sealed_branch_i || sealed_state_i || sealed_page_i) state_d = RSM_FAULT;
                else state_d = RSM_ALLOC;
            end
            RSM_ALLOC: begin
                alloc_req_o = 1'b1;
                if (alloc_ready_i) begin
                    alloc_take_o = 1'b1;
                    state_d = RSM_REMAP;
                end
            end
            RSM_REMAP: begin
                remap_valid_o = 1'b1;
                state_d = RSM_DONE;
            end
            RSM_DONE: begin
                cow_resolved_o = 1'b1;
                state_d = RSM_IDLE;
            end
            RSM_FAULT: begin
                cow_fault_o = 1'b1;
                state_d = RSM_IDLE;
            end
            default: state_d = RSM_IDLE;
        endcase
    end

    integer i;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state_q <= RSM_IDLE;
            page_valid_q <= '0;
            for (i = 0; i < NUM_PAGES_P; i++) page_map_q[i] <= '0;
        end else begin
            state_q <= state_d;
            if (remap_valid_o) begin
                page_map_q[logical_page_i] <= alloc_paddr_i;
                page_valid_q[logical_page_i] <= 1'b1;
            end
        end
    end
endmodule
