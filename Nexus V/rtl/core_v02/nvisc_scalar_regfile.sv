`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_scalar_regfile #(
    parameter int NUM_REGS = 32
)(
    input  logic clk,
    input  logic rst_n,

    // Read port A
    input  logic [NV_REG_ADDR_W-1:0] rs1_addr_i,
    output logic [NV_XLEN-1:0]       rs1_data_o,

    // Read port B
    input  logic [NV_REG_ADDR_W-1:0] rs2_addr_i,
    output logic [NV_XLEN-1:0]       rs2_data_o,

    // Write port
    input  logic                     rd_we_i,
    input  logic [NV_REG_ADDR_W-1:0] rd_addr_i,
    input  logic [NV_XLEN-1:0]       rd_data_i,

    // Debug-friendly mirrors
    output logic [NV_XLEN-1:0]       dbg_r0_o,
    output logic [NV_XLEN-1:0]       dbg_r1_o,
    output logic [NV_XLEN-1:0]       dbg_r2_o,
    output logic [NV_XLEN-1:0]       dbg_r3_o
);

    logic [NV_XLEN-1:0] regs_q [NUM_REGS];

    integer i;

    // Asynchronous reads.
    always_comb begin
        if (rs1_addr_i == '0) begin
            rs1_data_o = '0;
        end else begin
            rs1_data_o = regs_q[rs1_addr_i];
        end

        if (rs2_addr_i == '0) begin
            rs2_data_o = '0;
        end else begin
            rs2_data_o = regs_q[rs2_addr_i];
        end
    end

    // Synchronous write/reset.
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < NUM_REGS; i = i + 1) begin
                regs_q[i] <= '0;
            end
        end else begin
            // r0 is hardwired zero.
            regs_q[0] <= '0;

            if (rd_we_i && rd_addr_i != '0) begin
                regs_q[rd_addr_i] <= rd_data_i;
            end
        end
    end

    assign dbg_r0_o = '0;
    assign dbg_r1_o = regs_q[1];
    assign dbg_r2_o = regs_q[2];
    assign dbg_r3_o = regs_q[3];

endmodule
