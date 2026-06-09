`timescale 1ns / 1ps

import nvisc_aegis_pkg::*;

module nvisc_aegis_attest_token_unit #(
    parameter int HASH_W = 128,
    parameter int DIGEST_W = 128
)(
    input  logic clk,
    input  logic rst_n,

    input  logic attest_req_i,
    input  logic [31:0] state_id_i,
    input  logic [31:0] branch_id_i,
    input  logic [31:0] commit_id_i,
    input  logic [15:0] policy_id_i,
    input  logic [HASH_W-1:0] subject_hash_i,
    input  logic [DIGEST_W-1:0] telemetry_digest_i,

    output logic attest_valid_o,
    output nvisc_attest_token_t attest_token_o
);

    logic [31:0] token_counter_q;
    logic [63:0] monotonic_counter_q;

    function automatic [127:0] mix128(
        input [127:0] a,
        input [127:0] b,
        input [63:0] c,
        input [15:0] p
    );
        mix128 = a ^ {b[63:0], b[127:64]} ^ {48'd0, c, p};
    endfunction

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            token_counter_q <= 32'd0;
            monotonic_counter_q <= 64'd0;
            attest_valid_o <= 1'b0;
            attest_token_o <= '0;
        end else begin
            attest_valid_o <= 1'b0;

            if (attest_req_i) begin
                token_counter_q <= token_counter_q + 32'd1;
                monotonic_counter_q <= monotonic_counter_q + 64'd1;

                attest_valid_o <= 1'b1;
                attest_token_o.valid <= 1'b1;
                attest_token_o.token_id <= token_counter_q + 32'd1;
                attest_token_o.state_id <= state_id_i;
                attest_token_o.branch_id <= branch_id_i;
                attest_token_o.commit_id <= commit_id_i;
                attest_token_o.policy_id <= policy_id_i;
                attest_token_o.subject_hash <= subject_hash_i;
                attest_token_o.telemetry_digest <= telemetry_digest_i;
                attest_token_o.monotonic_counter <= monotonic_counter_q + 64'd1;
                attest_token_o.token_mac <= mix128(subject_hash_i, telemetry_digest_i, monotonic_counter_q + 64'd1, policy_id_i);
            end
        end
    end

endmodule
