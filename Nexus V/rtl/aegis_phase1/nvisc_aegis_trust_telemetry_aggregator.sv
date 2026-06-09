`timescale 1ns / 1ps

import nvisc_aegis_pkg::*;

module nvisc_aegis_trust_telemetry_aggregator #(
    parameter int SCORE_W = 8,
    parameter int DIGEST_W = 128
)(
    input  logic clk,
    input  logic rst_n,

    input  logic memory_hash_ok_i,
    input  logic rsm_integrity_ok_i,
    input  logic branch_lineage_ok_i,
    input  logic io_provenance_ok_i,
    input  logic hid_chain_ok_i,
    input  logic gpu_path_ok_i,
    input  logic thermal_safe_i,
    input  logic voltage_safe_i,
    input  logic route_token_valid_i,
    input  logic rollback_available_i,
    input  logic numeric_integrity_ok_i,
    input  logic tamper_detected_i,
    input  logic safeguard_bypass_i,

    output logic [SCORE_W-1:0] trust_score_o,
    output logic trust_pass_o,
    output logic trust_warn_o,
    output logic trust_fail_o,
    output logic [DIGEST_W-1:0] telemetry_digest_o
);

    logic [15:0] score_tmp;
    logic [SCORE_W-1:0] score_c;

    always_comb begin
        score_tmp = 16'd255;

        if (!memory_hash_ok_i)       score_tmp = score_tmp - 16'd40;
        if (!rsm_integrity_ok_i)     score_tmp = score_tmp - 16'd32;
        if (!branch_lineage_ok_i)    score_tmp = score_tmp - 16'd24;
        if (!io_provenance_ok_i)     score_tmp = score_tmp - 16'd24;
        if (!hid_chain_ok_i)         score_tmp = score_tmp - 16'd16;
        if (!gpu_path_ok_i)          score_tmp = score_tmp - 16'd16;
        if (!thermal_safe_i)         score_tmp = score_tmp - 16'd24;
        if (!voltage_safe_i)         score_tmp = score_tmp - 16'd24;
        if (!route_token_valid_i)    score_tmp = score_tmp - 16'd16;
        if (!rollback_available_i)   score_tmp = score_tmp - 16'd16;
        if (!numeric_integrity_ok_i) score_tmp = score_tmp - 16'd16;

        if (tamper_detected_i)       score_tmp = 16'd0;
        if (safeguard_bypass_i)      score_tmp = 16'd0;

        if (score_tmp[15]) begin
            score_c = '0;
        end else if (score_tmp > 16'd255) begin
            score_c = 8'd255;
        end else begin
            score_c = score_tmp[SCORE_W-1:0];
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            trust_score_o <= '0;
        end else begin
            trust_score_o <= score_c;
        end
    end

    assign trust_pass_o = trust_score_o >= 8'd220;
    assign trust_warn_o = (trust_score_o >= 8'd160) && (trust_score_o < 8'd220);
    assign trust_fail_o = trust_score_o < 8'd160;

    assign telemetry_digest_o = {
        32'hA3615EED,
        8'(trust_score_o),
        memory_hash_ok_i,
        rsm_integrity_ok_i,
        branch_lineage_ok_i,
        io_provenance_ok_i,
        hid_chain_ok_i,
        gpu_path_ok_i,
        thermal_safe_i,
        voltage_safe_i,
        route_token_valid_i,
        rollback_available_i,
        numeric_integrity_ok_i,
        tamper_detected_i,
        safeguard_bypass_i,
        74'd0
    };

endmodule
