`timescale 1ns / 1ps

import nvisc_aegis_pkg::*;

module nvisc_aegis_commit_gate #(
    parameter int HASH_W = 128,
    parameter int SCORE_W = 8,
    parameter logic [SCORE_W-1:0] TRUST_THRESHOLD = 8'd220
)(
    input  logic clk,
    input  logic rst_n,

    input  logic commit_req_i,
    input  logic [31:0] candidate_state_id_i,
    input  logic [31:0] candidate_branch_id_i,
    input  logic [31:0] candidate_commit_id_i,
    input  logic [HASH_W-1:0] candidate_state_hash_i,

    input  logic [15:0] policy_id_i,

    input  logic audit_token_valid_i,
    input  logic [HASH_W-1:0] audit_token_subject_hash_i,

    input  logic [SCORE_W-1:0] trust_score_i,
    input  logic memory_hash_ok_i,
    input  logic rollback_available_i,
    input  logic numeric_integrity_ok_i,
    input  logic thermal_safe_i,
    input  logic tamper_detected_i,
    input  logic safeguard_bypass_i,

    output logic commit_allow_o,
    output logic commit_deny_o,
    output logic commit_refuse_o,
    output logic commit_quarantine_o,

    output logic seal_state_o,
    output logic [31:0] seal_state_id_o,
    output logic seal_branch_o,
    output logic [31:0] seal_branch_id_o,

    output logic attest_req_o,
    output logic [31:0] attest_state_id_o,
    output logic [31:0] attest_branch_id_o,
    output logic [31:0] attest_commit_id_o
);

    logic subject_match;
    logic policy_ok;
    logic trust_ok;
    logic hard_fail;

    assign subject_match = (audit_token_subject_hash_i == candidate_state_hash_i);
    assign policy_ok = (policy_id_i != 16'd0);
    assign trust_ok = (trust_score_i >= TRUST_THRESHOLD);
    assign hard_fail = tamper_detected_i || safeguard_bypass_i;

    always_comb begin
        commit_allow_o      = 1'b0;
        commit_deny_o       = 1'b0;
        commit_refuse_o     = 1'b0;
        commit_quarantine_o = 1'b0;

        seal_state_o     = 1'b0;
        seal_state_id_o  = candidate_state_id_i;
        seal_branch_o    = 1'b0;
        seal_branch_id_o = candidate_branch_id_i;

        attest_req_o       = 1'b0;
        attest_state_id_o  = candidate_state_id_i;
        attest_branch_id_o = candidate_branch_id_i;
        attest_commit_id_o = candidate_commit_id_i;

        if (commit_req_i) begin
            if (hard_fail) begin
                commit_refuse_o     = 1'b1;
                commit_quarantine_o = 1'b1;
            end else if (
                audit_token_valid_i &&
                subject_match &&
                policy_ok &&
                trust_ok &&
                memory_hash_ok_i &&
                rollback_available_i &&
                numeric_integrity_ok_i &&
                thermal_safe_i
            ) begin
                commit_allow_o = 1'b1;
                seal_state_o   = 1'b1;
                seal_branch_o  = 1'b1;
                attest_req_o   = 1'b1;
            end else begin
                commit_deny_o = 1'b1;
            end
        end
    end

endmodule
