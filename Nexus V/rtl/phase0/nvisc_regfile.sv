`timescale 1ns / 1ps

import nvisc_pkg::*;

module nvisc_regfile #(
    parameter int XLEN_P = XLEN,
    parameter int FLEN_P = FLEN,
    parameter int DLEN_P = DLEN,
    parameter int MLEN_P = MLEN,
    parameter int TLEN_P = TLEN,
    parameter int SLEN_P = SLEN,
    parameter int CLEN_P = CLEN
)(
    input  logic clk,
    input  logic rst_n,

    input  logic        r_we,
    input  logic [4:0]  r_waddr,
    input  logic [XLEN_P-1:0] r_wdata,
    input  logic [4:0]  r_raddr_a,
    input  logic [4:0]  r_raddr_b,
    output logic [XLEN_P-1:0] r_rdata_a,
    output logic [XLEN_P-1:0] r_rdata_b,

    input  logic        f_we,
    input  logic [4:0]  f_waddr,
    input  logic [FLEN_P-1:0] f_wdata,
    input  logic [4:0]  f_raddr_a,
    output logic [FLEN_P-1:0] f_rdata_a,

    input  logic        d_we,
    input  logic [4:0]  d_waddr,
    input  logic [DLEN_P-1:0] d_wdata,
    input  logic [4:0]  d_raddr_a,
    output logic [DLEN_P-1:0] d_rdata_a,

    input  logic        m_we,
    input  logic [4:0]  m_waddr,
    input  logic [MLEN_P-1:0] m_wdata,
    input  logic [4:0]  m_raddr_a,
    output logic [MLEN_P-1:0] m_rdata_a,

    input  logic        t_we,
    input  logic [4:0]  t_waddr,
    input  logic [TLEN_P-1:0] t_wdata,
    input  logic [4:0]  t_raddr_a,
    output logic [TLEN_P-1:0] t_rdata_a,

    input  logic        s_we,
    input  logic [4:0]  s_waddr,
    input  logic [SLEN_P-1:0] s_wdata,
    input  logic [4:0]  s_raddr_a,
    output logic [SLEN_P-1:0] s_rdata_a,

    input  logic        p_we,
    input  logic [3:0]  p_waddr,
    input  logic        p_wdata,
    input  logic [3:0]  p_raddr_a,
    output logic        p_rdata_a,

    input  logic        c_we,
    input  logic [3:0]  c_waddr,
    input  logic [CLEN_P-1:0] c_wdata,
    input  logic [3:0]  c_raddr_a,
    output logic [CLEN_P-1:0] c_rdata_a
);

    logic [XLEN_P-1:0] r_file [REG_COUNT];
    logic [FLEN_P-1:0] f_file [REG_COUNT];
    logic [DLEN_P-1:0] d_file [REG_COUNT];
    logic [MLEN_P-1:0] m_file [REG_COUNT];
    logic [TLEN_P-1:0] t_file [REG_COUNT];
    logic [SLEN_P-1:0] s_file [REG_COUNT];
    logic              p_file [PRED_COUNT];
    logic [CLEN_P-1:0] c_file [CAP_COUNT];

    integer i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < REG_COUNT; i++) begin
                r_file[i] <= '0;
                f_file[i] <= '0;
                d_file[i] <= '0;
                m_file[i] <= '0;
                t_file[i] <= '0;
                s_file[i] <= '0;
            end
            for (i = 0; i < PRED_COUNT; i++) p_file[i] <= 1'b0;
            for (i = 0; i < CAP_COUNT; i++) c_file[i] <= '0;
        end else begin
            if (r_we && r_waddr != 5'd0) r_file[r_waddr] <= r_wdata;
            if (f_we) f_file[f_waddr] <= f_wdata;
            if (d_we) d_file[d_waddr] <= d_wdata;
            if (m_we) m_file[m_waddr] <= m_wdata;
            if (t_we) t_file[t_waddr] <= t_wdata;
            if (s_we) s_file[s_waddr] <= s_wdata;
            if (p_we) p_file[p_waddr] <= p_wdata;
            if (c_we) c_file[c_waddr] <= c_wdata;
        end
    end

    assign r_rdata_a = (r_raddr_a == 5'd0) ? '0 : r_file[r_raddr_a];
    assign r_rdata_b = (r_raddr_b == 5'd0) ? '0 : r_file[r_raddr_b];
    assign f_rdata_a = f_file[f_raddr_a];
    assign d_rdata_a = d_file[d_raddr_a];
    assign m_rdata_a = m_file[m_raddr_a];
    assign t_rdata_a = t_file[t_raddr_a];
    assign s_rdata_a = s_file[s_raddr_a];
    assign p_rdata_a = p_file[p_raddr_a];
    assign c_rdata_a = c_file[c_raddr_a];

endmodule
