`timescale 1ns / 1ps

module nvisc_tensor_scratchpad #(
    parameter int DEPTH = 1024,
    parameter int DATA_W = 32,
    parameter int ADDR_W = $clog2(DEPTH)
)(
    input  logic clk,
    input  logic wr_en_i,
    input  logic [ADDR_W-1:0] wr_addr_i,
    input  logic [DATA_W-1:0] wr_data_i,
    input  logic rd_en_i,
    input  logic [ADDR_W-1:0] rd_addr_i,
    output logic rd_valid_o,
    output logic [DATA_W-1:0] rd_data_o
);
    logic [DATA_W-1:0] mem [DEPTH];
    always_ff @(posedge clk) begin
        if (wr_en_i) mem[wr_addr_i] <= wr_data_i;
        rd_valid_o <= rd_en_i;
        if (rd_en_i) rd_data_o <= mem[rd_addr_i];
    end
endmodule
