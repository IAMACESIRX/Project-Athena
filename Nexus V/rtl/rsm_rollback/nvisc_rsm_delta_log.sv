`timescale 1ns / 1ps

import nvisc_rsm_pkg::*;

module nvisc_rsm_delta_log #(
    parameter int LOG_DEPTH = 256,
    parameter int LOG_IDX_W = $clog2(LOG_DEPTH)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic wr_req_i,
    input  nvisc_rsm_delta_entry_t wr_entry_i,
    output logic wr_ready_o,
    output logic [LOG_IDX_W-1:0] wr_index_o,

    input  logic rd_req_i,
    input  logic [LOG_IDX_W-1:0] rd_index_i,
    output logic rd_valid_o,
    output nvisc_rsm_delta_entry_t rd_entry_o,

    output logic full_o,
    output logic empty_o,
    output logic [LOG_IDX_W:0] count_o
);

    nvisc_rsm_delta_entry_t log_mem [LOG_DEPTH];

    logic [LOG_IDX_W-1:0] wr_ptr_q;
    logic [LOG_IDX_W:0]   count_q;

    assign full_o     = (count_q == LOG_DEPTH[LOG_IDX_W:0]);
    assign empty_o    = (count_q == '0);
    assign wr_ready_o = !full_o;
    assign wr_index_o = wr_ptr_q;
    assign count_o    = count_q;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wr_ptr_q   <= '0;
            count_q    <= '0;
            rd_valid_o <= 1'b0;
            rd_entry_o <= '0;
        end else begin
            rd_valid_o <= 1'b0;

            if (wr_req_i && wr_ready_o) begin
                log_mem[wr_ptr_q] <= wr_entry_i;
                wr_ptr_q <= wr_ptr_q + 1'b1;
                count_q <= count_q + 1'b1;
            end

            if (rd_req_i) begin
                rd_entry_o <= log_mem[rd_index_i];
                rd_valid_o <= 1'b1;
            end
        end
    end

endmodule
