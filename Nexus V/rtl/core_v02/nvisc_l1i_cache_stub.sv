`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_l1i_cache_stub #(
    parameter int LINES = 16
)(
    input  logic clk,
    input  logic rst_n,

    // Fetch-side request from core/frontend.
    input  logic        fetch_req_valid_i,
    input  logic [63:0] fetch_req_addr_i,
    input  logic        flush_i,

    // Fetch-side response back to frontend.
    output logic        fetch_resp_valid_o,
    output logic [31:0] fetch_resp_instr_o,
    output logic        fetch_resp_fault_o,
    output logic [15:0] fetch_resp_fault_code_o,

    // Backing instruction memory request.
    output logic        imem_req_valid_o,
    output logic [63:0] imem_req_addr_o,

    // Backing instruction memory response.
    input  logic        imem_resp_valid_i,
    input  logic [31:0] imem_resp_instr_i,
    input  logic        imem_resp_fault_i,
    input  logic [15:0] imem_resp_fault_code_i,

    // Debug.
    output logic        dbg_hit_o,
    output logic        dbg_miss_o,
    output logic        dbg_fill_o,
    output logic [31:0] dbg_cached_instr_o
);

    localparam int INDEX_W = $clog2(LINES);
    localparam int OFFSET_BITS = 2; // 32-bit instruction words.

    typedef enum logic [1:0] {
        L1I_IDLE,
        L1I_WAIT_FILL
    } l1i_state_e;

    l1i_state_e state_q;

    logic [LINES-1:0] valid_q;
    logic [63:0]      tag_q   [LINES];
    logic [31:0]      instr_q [LINES];

    logic [INDEX_W-1:0] index_c;
    logic [63:0]        tag_c;
    logic               hit_c;
    logic               align_fault_c;

    logic [INDEX_W-1:0] miss_index_q;
    logic [63:0]        miss_tag_q;
    logic [63:0]        miss_addr_q;

    integer i;

    assign index_c = fetch_req_addr_i[OFFSET_BITS + INDEX_W - 1:OFFSET_BITS];
    assign tag_c   = fetch_req_addr_i >> (OFFSET_BITS + INDEX_W);

    assign hit_c = fetch_req_valid_i &&
                   valid_q[index_c] &&
                   (tag_q[index_c] == tag_c);

    assign align_fault_c = fetch_req_valid_i && (fetch_req_addr_i[1:0] != 2'b00);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state_q <= L1I_IDLE;

            valid_q <= '0;
            for (i = 0; i < LINES; i = i + 1) begin
                tag_q[i]   <= 64'd0;
                instr_q[i] <= 32'd0;
            end

            fetch_resp_valid_o      <= 1'b0;
            fetch_resp_instr_o      <= 32'd0;
            fetch_resp_fault_o      <= 1'b0;
            fetch_resp_fault_code_o <= 16'd0;

            imem_req_valid_o <= 1'b0;
            imem_req_addr_o  <= 64'd0;

            miss_index_q <= '0;
            miss_tag_q   <= 64'd0;
            miss_addr_q  <= 64'd0;

            dbg_hit_o          <= 1'b0;
            dbg_miss_o         <= 1'b0;
            dbg_fill_o         <= 1'b0;
            dbg_cached_instr_o <= 32'd0;
        end else begin
            fetch_resp_valid_o      <= 1'b0;
            fetch_resp_instr_o      <= 32'd0;
            fetch_resp_fault_o      <= 1'b0;
            fetch_resp_fault_code_o <= 16'd0;

            imem_req_valid_o <= 1'b0;
            imem_req_addr_o  <= 64'd0;

            dbg_hit_o  <= 1'b0;
            dbg_miss_o <= 1'b0;
            dbg_fill_o <= 1'b0;

            if (flush_i) begin
                valid_q <= '0;
                state_q <= L1I_IDLE;
            end else begin
                unique case (state_q)
                    L1I_IDLE: begin
                        if (fetch_req_valid_i) begin
                            if (align_fault_c) begin
                                fetch_resp_fault_o      <= 1'b1;
                                fetch_resp_fault_code_o <= 16'h0601;
                            end else if (hit_c) begin
                                fetch_resp_valid_o <= 1'b1;
                                fetch_resp_instr_o <= instr_q[index_c];

                                dbg_hit_o          <= 1'b1;
                                dbg_cached_instr_o <= instr_q[index_c];
                            end else begin
                                imem_req_valid_o <= 1'b1;
                                imem_req_addr_o  <= fetch_req_addr_i;

                                miss_index_q <= index_c;
                                miss_tag_q   <= tag_c;
                                miss_addr_q  <= fetch_req_addr_i;

                                dbg_miss_o <= 1'b1;
                                state_q    <= L1I_WAIT_FILL;
                            end
                        end
                    end

                    L1I_WAIT_FILL: begin
                        if (imem_resp_fault_i) begin
                            fetch_resp_fault_o      <= 1'b1;
                            fetch_resp_fault_code_o <= imem_resp_fault_code_i;
                            state_q                 <= L1I_IDLE;
                        end else if (imem_resp_valid_i) begin
                            valid_q[miss_index_q] <= 1'b1;
                            tag_q[miss_index_q]   <= miss_tag_q;
                            instr_q[miss_index_q] <= imem_resp_instr_i;

                            fetch_resp_valid_o <= 1'b1;
                            fetch_resp_instr_o <= imem_resp_instr_i;

                            dbg_fill_o         <= 1'b1;
                            dbg_cached_instr_o <= imem_resp_instr_i;

                            state_q <= L1I_IDLE;
                        end
                    end

                    default: begin
                        state_q <= L1I_IDLE;
                    end
                endcase
            end
        end
    end

endmodule
