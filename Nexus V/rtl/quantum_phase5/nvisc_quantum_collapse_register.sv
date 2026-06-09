`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_quantum_collapse_register (
    input  logic clk,
    input  logic rst_n,
    input  logic wr_req_i,
    input  nvisc_qcollapse_reg_t wr_collapse_i,
    input  logic clear_i,
    output nvisc_qcollapse_reg_t collapse_o
);
    nvisc_qcollapse_reg_t collapse_q;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) collapse_q <= '0;
        else if (clear_i) collapse_q <= '0;
        else if (wr_req_i) collapse_q <= wr_collapse_i;
    end
    assign collapse_o = collapse_q;
endmodule
