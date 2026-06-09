`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_qhw_bridge_stub #(
    parameter int TIMEOUT_CYCLES = 16
)(
    input  logic clk,
    input  logic rst_n,
    input  logic qhw_req_i,
    input  logic [31:0] qreg_id_i,
    input  logic [7:0] shots_i,
    input  logic force_timeout_i,
    input  logic force_low_fidelity_i,
    output logic qhw_accept_o,
    output logic qhw_done_o,
    output logic qhw_timeout_o,
    output logic [7:0] qhw_result_o,
    output logic [7:0] qhw_fidelity_o
);
    logic busy_q;
    logic [$clog2(TIMEOUT_CYCLES+1)-1:0] count_q;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            busy_q <= 1'b0;
            count_q <= '0;
            qhw_accept_o <= 1'b0;
            qhw_done_o <= 1'b0;
            qhw_timeout_o <= 1'b0;
            qhw_result_o <= 8'd0;
            qhw_fidelity_o <= 8'd255;
        end else begin
            qhw_accept_o <= 1'b0;
            qhw_done_o <= 1'b0;
            qhw_timeout_o <= 1'b0;
            if (qhw_req_i && !busy_q) begin
                busy_q <= 1'b1;
                count_q <= '0;
                qhw_accept_o <= 1'b1;
            end else if (busy_q) begin
                count_q <= count_q + 1'b1;
                if (force_timeout_i && count_q == TIMEOUT_CYCLES-1) begin
                    qhw_timeout_o <= 1'b1;
                    busy_q <= 1'b0;
                end else if (!force_timeout_i && count_q == 4) begin
                    qhw_done_o <= 1'b1;
                    qhw_result_o <= qreg_id_i[0] ? 8'd1 : 8'd0;
                    qhw_fidelity_o <= force_low_fidelity_i ? 8'd40 : 8'd240;
                    busy_q <= 1'b0;
                end
            end
        end
    end
endmodule
