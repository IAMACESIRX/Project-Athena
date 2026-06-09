`timescale 1ns / 1ps

import nvisc_pkg::*;
import nexus_v_soc_pkg::*;
import nvisc_tensor_pkg::*;
import nvisc_quantum_pkg::*;

module tb_nexus_v_soc_smoke;
    logic clk;
    logic rst_n;

    logic instr_valid;
    nvisc_alu_op_e alu_op;
    nvisc_domain_e domain;
    logic [4:0] src_a, src_b, dst;
    logic dst_we;
    logic dbg_r_we;
    logic [4:0] dbg_r_waddr;
    logic [XLEN-1:0] dbg_r_wdata;

    logic g_route_valid;
    logic [15:0] g_source_node, g_target_node;
    logic [2:0] g_route_policy;

    logic rollback_req;
    logic [31:0] rollback_state_id;

    logic commit_req;
    logic [31:0] candidate_state_id, candidate_branch_id, candidate_commit_id;
    logic [127:0] candidate_state_hash, audit_token_subject_hash;
    logic [15:0] policy_id;
    logic audit_token_valid;

    logic memory_hash_ok, rsm_integrity_ok, branch_lineage_ok, io_provenance_ok, hid_chain_ok, gpu_path_ok;
    logic thermal_safe, voltage_safe, rollback_available, numeric_integrity_ok, tamper_detected, safeguard_bypass;

    logic minrep_req;
    logic [31:0] session_id;

    logic tensor_instr_valid;
    nvisc_tensor_op_e tensor_op;
    logic [31:0] tensor_a_id, tensor_b_id, tensor_c_id;
    logic [15:0] tensor_rows, tensor_cols, tensor_inner_dim;
    logic tensor_inject_numeric_fault;

    logic quantum_instr_valid;
    nvisc_qop_e qop;
    nvisc_qmode_e qmode;
    logic [$clog2(QREG_COUNT)-1:0] qreg_idx;
    logic [7:0] q_seed;
    logic qhw_force_timeout, qhw_force_low_fidelity;

    logic [15:0] node_fault_mask, node_untrusted_mask, node_hot_mask;

    nexus_v_soc_status_t soc_status;
    logic commit_allow, commit_deny, commit_refuse, commit_quarantine, minrep_valid, attest_valid;

    nexus_v_soc dut (
        .clk(clk), .rst_n(rst_n),
        .instr_valid_i(instr_valid), .alu_op_i(alu_op), .domain_i(domain),
        .src_a_i(src_a), .src_b_i(src_b), .dst_i(dst), .dst_we_i(dst_we),
        .dbg_r_we_i(dbg_r_we), .dbg_r_waddr_i(dbg_r_waddr), .dbg_r_wdata_i(dbg_r_wdata),
        .g_route_valid_i(g_route_valid), .g_source_node_i(g_source_node), .g_target_node_i(g_target_node), .g_route_policy_i(g_route_policy),
        .rollback_req_i(rollback_req), .rollback_state_id_i(rollback_state_id),
        .commit_req_i(commit_req), .candidate_state_id_i(candidate_state_id), .candidate_branch_id_i(candidate_branch_id), .candidate_commit_id_i(candidate_commit_id), .candidate_state_hash_i(candidate_state_hash),
        .policy_id_i(policy_id), .audit_token_valid_i(audit_token_valid), .audit_token_subject_hash_i(audit_token_subject_hash),
        .memory_hash_ok_i(memory_hash_ok), .rsm_integrity_ok_i(rsm_integrity_ok), .branch_lineage_ok_i(branch_lineage_ok), .io_provenance_ok_i(io_provenance_ok), .hid_chain_ok_i(hid_chain_ok), .gpu_path_ok_i(gpu_path_ok),
        .thermal_safe_i(thermal_safe), .voltage_safe_i(voltage_safe), .rollback_available_i(rollback_available), .numeric_integrity_ok_i(numeric_integrity_ok), .tamper_detected_i(tamper_detected), .safeguard_bypass_i(safeguard_bypass),
        .minrep_req_i(minrep_req), .session_id_i(session_id),
        .tensor_instr_valid_i(tensor_instr_valid), .tensor_op_i(tensor_op), .tensor_a_id_i(tensor_a_id), .tensor_b_id_i(tensor_b_id), .tensor_c_id_i(tensor_c_id), .tensor_rows_i(tensor_rows), .tensor_cols_i(tensor_cols), .tensor_inner_dim_i(tensor_inner_dim), .tensor_inject_numeric_fault_i(tensor_inject_numeric_fault),
        .quantum_instr_valid_i(quantum_instr_valid), .qop_i(qop), .qmode_i(qmode), .qreg_idx_i(qreg_idx), .q_seed_i(q_seed), .qhw_force_timeout_i(qhw_force_timeout), .qhw_force_low_fidelity_i(qhw_force_low_fidelity),
        .node_fault_mask_i(node_fault_mask), .node_untrusted_mask_i(node_untrusted_mask), .node_hot_mask_i(node_hot_mask),
        .soc_status_o(soc_status), .commit_allow_o(commit_allow), .commit_deny_o(commit_deny), .commit_refuse_o(commit_refuse), .commit_quarantine_o(commit_quarantine), .minrep_valid_o(minrep_valid), .attest_valid_o(attest_valid)
    );

    always #5 clk = ~clk;

    initial begin
        clk = 1'b0; rst_n = 1'b0;
        instr_valid = 1'b0; alu_op = ALU_NOP; domain = DOMAIN_BIN; src_a = '0; src_b = '0; dst = '0; dst_we = 1'b0;
        dbg_r_we = 1'b0; dbg_r_waddr = '0; dbg_r_wdata = '0;
        g_route_valid = 1'b0; g_source_node = 16'd0; g_target_node = 16'd0; g_route_policy = 3'd0;
        rollback_req = 1'b0; rollback_state_id = 32'd1;
        commit_req = 1'b0; candidate_state_id = 32'd1; candidate_branch_id = 32'd0; candidate_commit_id = 32'd1; candidate_state_hash = 128'hABCD; policy_id = 16'd1; audit_token_valid = 1'b1; audit_token_subject_hash = 128'hABCD;
        memory_hash_ok = 1'b1; rsm_integrity_ok = 1'b1; branch_lineage_ok = 1'b1; io_provenance_ok = 1'b1; hid_chain_ok = 1'b1; gpu_path_ok = 1'b1;
        thermal_safe = 1'b1; voltage_safe = 1'b1; rollback_available = 1'b1; numeric_integrity_ok = 1'b1; tamper_detected = 1'b0; safeguard_bypass = 1'b0;
        minrep_req = 1'b0; session_id = 32'd1234;
        tensor_instr_valid = 1'b0; tensor_op = TENSOR_OP_TLOAD; tensor_a_id = 32'd1; tensor_b_id = 32'd2; tensor_c_id = 32'd3; tensor_rows = 16'd4; tensor_cols = 16'd4; tensor_inner_dim = 16'd4; tensor_inject_numeric_fault = 1'b0;
        quantum_instr_valid = 1'b0; qop = QOP_QALLOC; qmode = QMODE_QSIM; qreg_idx = '0; q_seed = 8'd1; qhw_force_timeout = 1'b0; qhw_force_low_fidelity = 1'b0;
        node_fault_mask = 16'd0; node_untrusted_mask = 16'd0; node_hot_mask = 16'd0;
        repeat (4) @(posedge clk); rst_n = 1'b1; repeat (2) @(posedge clk);

        // Clean commit should pass and emit ATTEST.
        commit_req = 1'b1; @(posedge clk); commit_req = 1'b0; repeat (2) @(posedge clk);
        assert(commit_allow || attest_valid) else $fatal("Expected clean commit/attest path to assert");

        // Fabric route smoke.
        g_route_valid = 1'b1; g_source_node = 16'd0; g_target_node = 16'd3; g_route_policy = 3'd0; @(posedge clk); g_route_valid = 1'b0; repeat (8) @(posedge clk);
        assert(soc_status.topology_route_done || soc_status.fault_code == SOC_OK) else $fatal("Expected topology route path to progress");

        // Tensor smoke.
        tensor_instr_valid = 1'b1; tensor_op = TENSOR_OP_TMATMUL; @(posedge clk); tensor_instr_valid = 1'b0; repeat (8) @(posedge clk);

        // Quantum smoke.
        quantum_instr_valid = 1'b1; qop = QOP_QALLOC; @(posedge clk); quantum_instr_valid = 1'b0; repeat (2) @(posedge clk);
        quantum_instr_valid = 1'b1; qop = QOP_QPREP; @(posedge clk); quantum_instr_valid = 1'b0; repeat (2) @(posedge clk);
        quantum_instr_valid = 1'b1; qop = QOP_QH; @(posedge clk); quantum_instr_valid = 1'b0; repeat (2) @(posedge clk);
        quantum_instr_valid = 1'b1; qop = QOP_QMEASURE; @(posedge clk); quantum_instr_valid = 1'b0; repeat (4) @(posedge clk);

        $display("Nexus-V SoC top-level integration smoke completed.");
        $finish;
    end
endmodule
