`timescale 1ns / 1ps

import nvisc_aegis_pkg::*;

module nvisc_aegis_enclave #(
    parameter int HASH_W = 128
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

    input  logic minrep_req_i,
    input  logic [31:0] session_id_i,

    output logic commit_allow_o,
    output logic commit_deny_o,
    output logic commit_refuse_o,
    output logic commit_quarantine_o,

    output logic seal_state_o,
    output logic [31:0] seal_state_id_o,
    output logic seal_branch_o,
    output logic [31:0] seal_branch_id_o,

    output logic attest_valid_o,
    output nvisc_attest_token_t attest_token_o,

    output logic minrep_valid_o,
    output nvisc_minrep_t minrep_o,

    output logic [7:0] session_trust_score_o
);

    logic trust_pass;
    logic trust_warn;
    logic trust_fail;
    logic [127:0] telemetry_digest;

    logic attest_req;
    logic [31:0] attest_state_id;
    logic [31:0] attest_branch_id;
    logic [31:0] attest_commit_id;

    nvisc_aegis_trust_telemetry_aggregator u_trust (
        .clk(clk),
        .rst_n(rst_n),
        .memory_hash_ok_i(memory_hash_ok_i),
        .rsm_integrity_ok_i(rsm_integrity_ok_i),
        .branch_lineage_ok_i(branch_lineage_ok_i),
        .io_provenance_ok_i(io_provenance_ok_i),
        .hid_chain_ok_i(hid_chain_ok_i),
        .gpu_path_ok_i(gpu_path_ok_i),
        .thermal_safe_i(thermal_safe_i),
        .voltage_safe_i(voltage_safe_i),
        .route_token_valid_i(route_token_valid_i),
        .rollback_available_i(rollback_available_i),
        .numeric_integrity_ok_i(numeric_integrity_ok_i),
        .tamper_detected_i(tamper_detected_i),
        .safeguard_bypass_i(safeguard_bypass_i),
        .trust_score_o(session_trust_score_o),
        .trust_pass_o(trust_pass),
        .trust_warn_o(trust_warn),
        .trust_fail_o(trust_fail),
        .telemetry_digest_o(telemetry_digest)
    );

    nvisc_aegis_commit_gate u_commit_gate (
        .clk(clk),
        .rst_n(rst_n),
        .commit_req_i(commit_req_i),
        .candidate_state_id_i(candidate_state_id_i),
        .candidate_branch_id_i(candidate_branch_id_i),
        .candidate_commit_id_i(candidate_commit_id_i),
        .candidate_state_hash_i(candidate_state_hash_i),
        .policy_id_i(policy_id_i),
        .audit_token_valid_i(audit_token_valid_i),
        .audit_token_subject_hash_i(audit_token_subject_hash_i),
        .trust_score_i(session_trust_score_o),
        .memory_hash_ok_i(memory_hash_ok_i),
        .rollback_available_i(rollback_available_i),
        .numeric_integrity_ok_i(numeric_integrity_ok_i),
        .thermal_safe_i(thermal_safe_i),
        .tamper_detected_i(tamper_detected_i),
        .safeguard_bypass_i(safeguard_bypass_i),
        .commit_allow_o(commit_allow_o),
        .commit_deny_o(commit_deny_o),
        .commit_refuse_o(commit_refuse_o),
        .commit_quarantine_o(commit_quarantine_o),
        .seal_state_o(seal_state_o),
        .seal_state_id_o(seal_state_id_o),
        .seal_branch_o(seal_branch_o),
        .seal_branch_id_o(seal_branch_id_o),
        .attest_req_o(attest_req),
        .attest_state_id_o(attest_state_id),
        .attest_branch_id_o(attest_branch_id),
        .attest_commit_id_o(attest_commit_id)
    );

    nvisc_aegis_attest_token_unit u_attest (
        .clk(clk),
        .rst_n(rst_n),
        .attest_req_i(attest_req),
        .state_id_i(attest_state_id),
        .branch_id_i(attest_branch_id),
        .commit_id_i(attest_commit_id),
        .policy_id_i(policy_id_i),
        .subject_hash_i(candidate_state_hash_i),
        .telemetry_digest_i(telemetry_digest),
        .attest_valid_o(attest_valid_o),
        .attest_token_o(attest_token_o)
    );

    nvisc_aegis_minrep_generator u_minrep (
        .clk(clk),
        .rst_n(rst_n),
        .minrep_req_i(minrep_req_i),
        .session_id_i(session_id_i),
        .trust_score_i(session_trust_score_o),
        .game_binary_verified_i(memory_hash_ok_i),
        .memory_integrity_verified_i(memory_hash_ok_i),
        .input_chain_trusted_i(io_provenance_ok_i && hid_chain_ok_i),
        .gpu_path_verified_i(gpu_path_ok_i),
        .rollback_available_i(rollback_available_i),
        .aegis_active_i(1'b1),
        .unauthorized_overlay_detected_i(!gpu_path_ok_i),
        .tamper_detected_i(tamper_detected_i || safeguard_bypass_i),
        .minrep_valid_o(minrep_valid_o),
        .minrep_o(minrep_o)
    );

endmodule
