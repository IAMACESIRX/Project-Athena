`timescale 1ns / 1ps
import nvisc_tensor_pkg::*;

module nvisc_tensor_descriptor_table #(
    parameter int NUM_DESCS = 32,
    parameter int ADDR_W = $clog2(NUM_DESCS)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic wr_en_i,
    input  logic [ADDR_W-1:0] wr_idx_i,
    input  nvisc_tensor_desc_t wr_desc_i,

    input  logic rd_en_i,
    input  logic [ADDR_W-1:0] rd_idx_i,
    output logic rd_valid_o,
    output nvisc_tensor_desc_t rd_desc_o
);
    nvisc_tensor_desc_t desc_mem [NUM_DESCS];
    integer i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < NUM_DESCS; i++) begin
                desc_mem[i] <= '0;
            end
            rd_valid_o <= 1'b0;
            rd_desc_o <= '0;
        end else begin
            rd_valid_o <= 1'b0;
            if (wr_en_i) begin
                desc_mem[wr_idx_i] <= wr_desc_i;
            end
            if (rd_en_i) begin
                rd_desc_o <= desc_mem[rd_idx_i];
                rd_valid_o <= desc_mem[rd_idx_i].valid;
            end
        end
    end
endmodule
