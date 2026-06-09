`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_qsim_state_bank #(
    parameter int QREG_COUNT_P = QREG_COUNT,
    parameter int QREG_IDX_W = $clog2(QREG_COUNT_P)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic wr_req_i,
    input  logic [QREG_IDX_W-1:0] wr_idx_i,
    input  nvisc_qsim_state_t wr_state_i,

    input  logic rd_req_i,
    input  logic [QREG_IDX_W-1:0] rd_idx_i,
    output logic rd_valid_o,
    output nvisc_qsim_state_t rd_state_o,

    input  logic prep_zero_i,
    input  logic [QREG_IDX_W-1:0] prep_idx_i
);
    nvisc_qsim_state_t state_mem [QREG_COUNT_P];
    integer i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < QREG_COUNT_P; i++) state_mem[i] <= '0;
            rd_valid_o <= 1'b0;
            rd_state_o <= '0;
        end else begin
            rd_valid_o <= 1'b0;
            if (prep_zero_i) begin
                state_mem[prep_idx_i].valid <= 1'b1;
                state_mem[prep_idx_i].qreg_id <= {{(32-QREG_IDX_W){1'b0}}, prep_idx_i};
                state_mem[prep_idx_i].amp0_re <= 16'h7fff;
                state_mem[prep_idx_i].amp0_im <= 16'd0;
                state_mem[prep_idx_i].amp1_re <= 16'd0;
                state_mem[prep_idx_i].amp1_im <= 16'd0;
                state_mem[prep_idx_i].prob0 <= 8'd255;
                state_mem[prep_idx_i].prob1 <= 8'd0;
            end
            if (wr_req_i) state_mem[wr_idx_i] <= wr_state_i;
            if (rd_req_i) begin
                rd_valid_o <= 1'b1;
                rd_state_o <= state_mem[rd_idx_i];
            end
        end
    end
endmodule
