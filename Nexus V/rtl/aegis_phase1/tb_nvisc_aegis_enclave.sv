`timescale 1ns / 1ps

import nvisc_aegis_pkg::*;

module tb_nvisc_aegis_enclave;

    logic clk;
    logic rst_n;

    logic commit_req;
    logic [31:0] candidate_state_id;
    logic [31:0] candidate_branch_id;
    logic [31:0] candidate_commit_id;
    logic [127:0] candidate_state_hash;
    logic [15:0] policy_id;
    logic audit_token_valid;
    logic [127:0] audit_token_subject_hash;

    logic memory_hash_ok;
    logic rsm_integrity_ok;
    logic branch_lineage_ok;
    logic io_provenance_ok;
    logic hid_chain_ok;
    logic gpu_path_ok;
    logic thermal_safe;
    logic voltage_safe;
    logic route_token_valid;
    logic rollback_available;
    logic numeric_integrity_ok;
    logic tamper_detected;
    logic safeguard_bypass;

    logic minrep_req;
    logic [31:0] session_id;

    logic commit_allow;
    logic commit_deny;
    logic commit_refuse;
    logic commit_quarantine;
    logic seal_state;
    logic [31:0] seal_state_id;
    logic seal_branch;
    logic [31:0] seal_branch_id;
    logic attest_valid;
    nvisc_attest_token_t attest_token;
    logic minrep_valid;
    nvisc_minrep_t minrep;
    logic [7:0] session_trust_score;

    nvisc_aegis_enclave dut (
        .clk(clk), .rst_n(rst_n),
        .commit_req_i(commit_req),
        .candidate_state_id_i(candidate_state_id),
        .candidate_branch_id_i(candidate_branch_id),
        .candidate_commit_id_i(candidate_commit_id),
        .candidate_state_hash_i(candidate_state_hash),
        .policy_id_i(policy_id),
        .audit_token_valid_i(audit_token_valid),
        .audit_token_subject_hash_i(audit_token_subject_hash),
        .memory_hash_ok_i(memory_hash_ok),
        .rsm_integrity_ok_i(rsm_integrity_ok),
        .branch_lineage_ok_i(branch_lineage_ok),
        .io_provenance_ok_i(io_provenance_ok),
        .hid_chain_ok_i(hid_chain_ok),
        .gpu_path_ok_i(gpu_path_ok),
        .thermal_safe_i(thermal_safe),
        .voltage_safe_i(voltage_safe),
        .route_token_valid_i(route_token_valid),
        .rollback_available_i(rollback_available),
        .numeric_integrity_ok_i(numeric_integrity_ok),
        .tamper_detected_i(tamper_detected),
        .safeguard_bypass_i(safeguard_bypass),
        .minrep_req_i(minrep_req),
        .session_id_i(session_id),
        .commit_allow_o(commit_allow),
        .commit_deny_o(commit_deny),
        .commit_refuse_o(commit_refuse),
        .commit_quarantine_o(commit_quarantine),
        .seal_state_o(seal_state),
        .seal_state_id_o(seal_state_id),
        .seal_branch_o(seal_branch),
        .seal_branch_id_o(seal_branch_id),
        .attest_valid_o(attest_valid),
        .attest_token_o(attest_token),
        .minrep_valid_o(minrep_valid),
        .minrep_o(minrep),
        .session_trust_score_o(session_trust_score)
    );

    always #5 clk = ~clk;

    task set_clean_inputs;
        begin
            memory_hash_ok = 1'b1;
            rsm_integrity_ok = 1'b1;
            branch_lineage_ok = 1'b1;
            io_provenance_ok = 1'b1;
            hid_chain_ok = 1'b1;
            gpu_path_ok = 1'b1;
            thermal_safe = 1'b1;
            voltage_safe = 1'b1;
            route_token_valid = 1'b1;
            rollback_available = 1'b1;
            numeric_integrity_ok = 1'b1;
            tamper_detected = 1'b0;
            safeguard_bypass = 1'b0;
            audit_token_valid = 1'b1;
            audit_token_subject_hash = candidate_state_hash;
            policy_id = 16'd1;
        end
    endtask

    initial begin
        clk = 1'b0;
        rst_n = 1'b0;
        commit_req = 1'b0;
        minrep_req = 1'b0;
        session_id = 32'h1234_5678;
        candidate_state_id = 32'd11;
        candidate_branch_id = 32'd2;
        candidate_commit_id = 32'd5;
        candidate_state_hash = 128'hA5A5_0000_1111_2222_3333_4444_5555_6666;
        set_clean_inputs();

        repeat (3) @(posedge clk);
        rst_n = 1'b1;
        repeat (3) @(posedge clk);

        // trust score passes when all telemetry inputs are clean
        assert(session_trust_score >= 8'd220) else $fatal("clean trust score did not pass");

        // trust score fails on tamper_detected
        tamper_detected = 1'b1;
        @(posedge clk); @(posedge clk);
        assert(session_trust_score == 8'd0) else $fatal("tamper did not zero trust score");
        tamper_detected = 1'b0;
        repeat (2) @(posedge clk);

        // trust score fails on safeguard_bypass
        safeguard_bypass = 1'b1;
        @(posedge clk); @(posedge clk);
        assert(session_trust_score == 8'd0) else $fatal("safeguard bypass did not zero trust score");
        safeguard_bypass = 1'b0;
        repeat (2) @(posedge clk);

        // commit denied when audit token missing
        audit_token_valid = 1'b0;
        commit_req = 1'b1;
        #1;
        assert(commit_deny && !commit_allow) else $fatal("missing audit token did not deny commit");
        commit_req = 1'b0;
        audit_token_valid = 1'b1;

        // commit denied when audit subject hash mismatches candidate state hash
        audit_token_subject_hash = 128'hDEAD_BEEF;
        commit_req = 1'b1;
        #1;
        assert(commit_deny && !commit_allow) else $fatal("hash mismatch did not deny commit");
        commit_req = 1'b0;
        audit_token_subject_hash = candidate_state_hash;

        // commit denied when trust score below threshold
        thermal_safe = 1'b0;
        voltage_safe = 1'b0;
        io_provenance_ok = 1'b0;
        repeat (2) @(posedge clk);
        commit_req = 1'b1;
        #1;
        assert(commit_deny && !commit_allow) else $fatal("low trust did not deny commit");
        commit_req = 1'b0;
        set_clean_inputs();
        repeat (2) @(posedge clk);

        // commit allowed when all checks pass, seals asserted, ATTEST emitted
        commit_req = 1'b1;
        #1;
        assert(commit_allow && seal_state && seal_branch) else $fatal("clean commit not allowed/sealed");
        @(posedge clk);
        commit_req = 1'b0;
        @(posedge clk);
        assert(attest_valid) else $fatal("ATTEST not emitted after allowed commit");
        assert(attest_token.valid) else $fatal("ATTEST token invalid");

        // MINREP emits only allowed claims and no raw memory/private fields exist in interface
        minrep_req = 1'b1;
        @(posedge clk);
        minrep_req = 1'b0;
        @(posedge clk);
        assert(minrep_valid) else $fatal("MINREP not emitted");
        assert(minrep.valid) else $fatal("MINREP invalid");
        assert(minrep.memory_integrity_verified) else $fatal("MINREP missing allowed memory claim");

        // Aegis refusal path asserts quarantine on hard tamper
        tamper_detected = 1'b1;
        commit_req = 1'b1;
        #1;
        assert(commit_refuse && commit_quarantine) else $fatal("hard tamper did not refuse/quarantine");
        commit_req = 1'b0;
        tamper_detected = 1'b0;

        $display("Aegis Phase 1 smoke tests passed.");
        $finish;
    end

endmodule
