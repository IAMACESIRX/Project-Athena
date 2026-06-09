`timescale 1ns / 1ps

import nvisc_aegis_pkg::*;

module nvisc_aegis_minrep_generator #(
    parameter int MAC_W = 128
)(
    input  logic clk,
    input  logic rst_n,

    input  logic minrep_req_i,
    input  logic [31:0] session_id_i,
    input  logic [7:0] trust_score_i,

    input  logic game_binary_verified_i,
    input  logic memory_integrity_verified_i,
    input  logic input_chain_trusted_i,
    input  logic gpu_path_verified_i,
    input  logic rollback_available_i,
    input  logic aegis_active_i,
    input  logic unauthorized_overlay_detected_i,
    input  logic tamper_detected_i,

    output logic minrep_valid_o,
    output nvisc_minrep_t minrep_o
);

    logic [31:0] report_counter_q;

    function automatic [7:0] bucket_score(input logic [7:0] score);
        if (score >= 8'd220) bucket_score = 8'd3;
        else if (score >= 8'd160) bucket_score = 8'd2;
        else if (score >= 8'd80) bucket_score = 8'd1;
        else bucket_score = 8'd0;
    endfunction

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            report_counter_q <= 32'd0;
            minrep_valid_o <= 1'b0;
            minrep_o <= '0;
        end else begin
            minrep_valid_o <= 1'b0;

            if (minrep_req_i) begin
                report_counter_q <= report_counter_q + 32'd1;
                minrep_valid_o <= 1'b1;

                minrep_o.valid <= 1'b1;
                minrep_o.report_id <= report_counter_q + 32'd1;
                minrep_o.session_id <= session_id_i;
                minrep_o.trust_score_bucket <= bucket_score(trust_score_i);
                minrep_o.game_binary_verified <= game_binary_verified_i;
                minrep_o.memory_integrity_verified <= memory_integrity_verified_i;
                minrep_o.input_chain_trusted <= input_chain_trusted_i;
                minrep_o.gpu_path_verified <= gpu_path_verified_i;
                minrep_o.rollback_available <= rollback_available_i;
                minrep_o.aegis_active <= aegis_active_i;
                minrep_o.unauthorized_overlay_detected <= unauthorized_overlay_detected_i;
                minrep_o.tamper_detected <= tamper_detected_i;
                minrep_o.report_mac <= {
                    32'hAEE1_5001,
                    session_id_i,
                    report_counter_q,
                    bucket_score(trust_score_i),
                    game_binary_verified_i,
                    memory_integrity_verified_i,
                    input_chain_trusted_i,
                    gpu_path_verified_i,
                    rollback_available_i,
                    aegis_active_i,
                    unauthorized_overlay_detected_i,
                    tamper_detected_i,
                    48'd0
                };
            end
        end
    end

endmodule
