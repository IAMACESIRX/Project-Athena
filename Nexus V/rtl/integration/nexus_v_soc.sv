`timescale 1ns / 1ps

// Nexus-V SoC top-level integration wrapper.
// This module is an integration skeleton that physically instantiates the Phase 0 through Phase 5 blocks
// and wires the major route, state, RSM, Aegis, tensor, and quantum boundaries together.
// It is intentionally conservative: final arbitration, clock-domain crossing, and full issue/retire logic
// remain Phase 6+ work.

import nexus_v_soc_pkg::*;

module nexus_v_soc #(
    parameter int NUM_NODES = 16,
    parameter int HASH_W    = 128
)(
    input  logic clk,
    input  logic rst_n,

    // Phase 0 scalar/front-end execution control.
    input  logic                 instr_valid_i,
    input  nvisc_pkg::nvisc_alu_op_e alu_op_i,
    input  nvisc_pkg::nvisc_domain_e domain_i,
    input  logic [4:0]           src_a_i,
    input  logic [4:0]           src_b_i,
    input  logic [4:0]           dst_i,
    input  logic                 dst_we_i,
    input  logic                 dbg_r_we_i,
    input  logic [4:0]           dbg_r_waddr_i,
    input  logic [nvisc_pkg::XLEN-1:0] dbg_r_wdata_i,

    // Decoded G.ROUTE / G.GEO_PATH input.
    input  logic                 g_route_valid_i,
    input  logic [15:0]          g_source_node_i,
    input  logic [15:0]          g_target_node_i,
    input  logic [2:0]           g_route_policy_i,

    // RSM rollback input.
    input  logic                 rollback_req_i,
    input  logic [31:0]          rollback_state_id_i,

    // Commit/Aegis input.
    input  logic                 commit_req_i,
    input  logic [31:0]          candidate_state_id_i,
    input  logic [31:0]          candidate_branch_id_i,
    input  logic [31:0]          candidate_commit_id_i,
    input  logic [HASH_W-1:0]    candidate_state_hash_i,
    input  logic [15:0]          policy_id_i,
    input  logic                 audit_token_valid_i,
    input  logic [HASH_W-1:0]    audit_token_subject_hash_i,

    // Telemetry and provenance inputs for the Aegis trust aggregator.
    input  logic                 memory_hash_ok_i,
    input  logic                 rsm_integrity_ok_i,
    input  logic                 branch_lineage_ok_i,
    input  logic                 io_provenance_ok_i,
    input  logic                 hid_chain_ok_i,
    input  logic                 gpu_path_ok_i,
    input  logic                 thermal_safe_i,
    input  logic                 voltage_safe_i,
    input  logic                 rollback_available_i,
    input  logic                 numeric_integrity_ok_i,
    input  logic                 tamper_detected_i,
    input  logic                 safeguard_bypass_i,

    // MINREP request.
    input  logic                 minrep_req_i,
    input  logic [31:0]          session_id_i,

    // Phase 4 tensor/NPU command path.
    input  logic                 tensor_instr_valid_i,
    input  nvisc_tensor_pkg::nvisc_tensor_op_e tensor_op_i,
    input  logic [31:0]          tensor_a_id_i,
    input  logic [31:0]          tensor_b_id_i,
    input  logic [31:0]          tensor_c_id_i,
    input  logic [15:0]          tensor_rows_i,
    input  logic [15:0]          tensor_cols_i,
    input  logic [15:0]          tensor_inner_dim_i,
    input  logic                 tensor_inject_numeric_fault_i,

    // Phase 5 quantum command path.
    input  logic                 quantum_instr_valid_i,
    input  nvisc_quantum_pkg::nvisc_qop_e qop_i,
    input  nvisc_quantum_pkg::nvisc_qmode_e qmode_i,
    input  logic [$clog2(nvisc_quantum_pkg::QREG_COUNT)-1:0] qreg_idx_i,
    input  logic [7:0]           q_seed_i,
    input  logic                 qhw_force_timeout_i,
    input  logic                 qhw_force_low_fidelity_i,

    // Node health masks used by topology and tensor mapping.
    input  logic [NUM_NODES-1:0] node_fault_mask_i,
    input  logic [NUM_NODES-1:0] node_untrusted_mask_i,
    input  logic [NUM_NODES-1:0] node_hot_mask_i,

    output nexus_v_soc_status_t  soc_status_o,
    output logic                 commit_allow_o,
    output logic                 commit_deny_o,
    output logic                 commit_refuse_o,
    output logic                 commit_quarantine_o,
    output logic                 minrep_valid_o,
    output logic                 attest_valid_o
);

    // -------------------------------------------------------------------------
    // Phase 0 front-end / ALU / direct route compatibility path.
    // -------------------------------------------------------------------------
    nvisc_pkg::nvisc_state_token_t phase0_state_token;
    nvisc_pkg::nvisc_route_resp_t  phase0_route_resp;
    nvisc_pkg::nvisc_topology_token_t phase0_topology_token;

    logic [nvisc_pkg::XLEN-1:0] alu_result;
    logic alu_valid, alu_zero, alu_negative;
    logic phase0_route_done, phase0_route_fault;
    logic [15:0] phase0_route_id;

    nexus_v_phase0_core u_phase0_core (
        .clk(clk), .rst_n(rst_n),
        .instr_valid_i(instr_valid_i),
        .alu_op_i(alu_op_i),
        .domain_i(domain_i),
        .src_a_i(src_a_i), .src_b_i(src_b_i), .dst_i(dst_i), .dst_we_i(dst_we_i),
        .dbg_r_we_i(dbg_r_we_i), .dbg_r_waddr_i(dbg_r_waddr_i), .dbg_r_wdata_i(dbg_r_wdata_i),
        .token_state_advance_i(1'b0), .next_state_id_i(32'd0),
        .g_route_valid_i(g_route_valid_i), .g_source_node_i(g_source_node_i), .g_target_node_i(g_target_node_i),
        .g_route_policy_i(nvisc_pkg::nvisc_route_policy_e'(g_route_policy_i)),
        .alu_route_policy_i(nvisc_pkg::ROUTE_FAST),
        .node_trusted_i(~node_untrusted_mask_i[15:0]),
        .node_hot_i(node_hot_mask_i[15:0]),
        .node_fault_i(node_fault_mask_i[15:0]),
        .aegis_route_approved_i(!commit_quarantine_o),
        .alu_result_o(alu_result), .alu_valid_o(alu_valid), .zero_o(alu_zero), .negative_o(alu_negative),
        .state_token_o(phase0_state_token),
        .route_done_o(phase0_route_done), .route_fault_o(phase0_route_fault), .route_id_o(phase0_route_id),
        .route_resp_o(phase0_route_resp), .topology_token_o(phase0_topology_token)
    );

    // -------------------------------------------------------------------------
    // Phase 3 topology fabric path. This is the SoC-level fabric; Phase 0's local
    // route path remains as a compatibility/fallback path.
    // -------------------------------------------------------------------------
    nvisc_topology_pkg::nvisc_route_flit_t fabric_inject_flit;
    nvisc_topology_pkg::nvisc_topology_token_t fabric_route_token;
    logic fabric_inject_valid;
    logic fabric_route_done, fabric_route_fault;
    logic [15:0] fabric_trace_hops;
    logic [NUM_NODES-1:0] fabric_trace_visited;

    // Tensor route signals feed the fabric unless the scalar G.ROUTE path is active.
    logic tensor_route_req_valid;
    logic [15:0] tensor_route_src_node;
    logic [15:0] tensor_route_dst_node;
    logic [2:0]  tensor_route_policy;

    always_comb begin
        fabric_inject_valid = g_route_valid_i || tensor_route_req_valid;
        fabric_inject_flit = '0;
        fabric_inject_flit.valid = fabric_inject_valid;
        fabric_inject_flit.src_node = g_route_valid_i ? g_source_node_i : tensor_route_src_node;
        fabric_inject_flit.dst_node = g_route_valid_i ? g_target_node_i : tensor_route_dst_node;
        fabric_inject_flit.current_node = fabric_inject_flit.src_node;
        fabric_inject_flit.policy = nvisc_topology_pkg::nvisc_route_policy_e'(g_route_valid_i ? g_route_policy_i : tensor_route_policy);
        fabric_inject_flit.branch_id = phase0_state_token.branch_id;
        fabric_inject_flit.state_id = phase0_state_token.state_id;
        fabric_inject_flit.topology_epoch = phase0_state_token.topology_epoch;
        fabric_inject_flit.thermal_epoch = phase0_state_token.thermal_epoch;
        fabric_inject_flit.payload = 64'd0;
        fabric_inject_flit.last = 1'b1;
    end

    nvisc_rhombic_dodeca_fabric_v0 #(.NUM_NODES(NUM_NODES)) u_topology_fabric (
        .clk(clk), .rst_n(rst_n),
        .inject_valid_i(fabric_inject_valid),
        .inject_flit_i(fabric_inject_flit),
        .aegis_route_allow_i(!commit_quarantine_o),
        .aegis_route_deny_i(commit_quarantine_o),
        .node_fault_mask_i(node_fault_mask_i),
        .node_untrusted_mask_i(node_untrusted_mask_i),
        .node_hot_mask_i(node_hot_mask_i),
        .current_topology_epoch_i(phase0_state_token.topology_epoch),
        .current_thermal_epoch_i(phase0_state_token.thermal_epoch),
        .route_done_o(fabric_route_done),
        .route_fault_o(fabric_route_fault),
        .route_token_o(fabric_route_token),
        .trace_hop_count_o(fabric_trace_hops),
        .trace_visited_o(fabric_trace_visited)
    );

    // -------------------------------------------------------------------------
    // Phase 4 Tensor/NPU spatial engine.
    // -------------------------------------------------------------------------
    logic tensor_busy, tensor_done, tensor_fault, tensor_result_valid, tensor_numeric_ok, tensor_audit_req, tensor_sync_valid;
    nvisc_tensor_pkg::nvisc_tensor_fault_e tensor_fault_code;
    logic [31:0] tensor_result_id;

    nvisc_tensor_npu_engine #(.NUM_NODES(NUM_NODES)) u_tensor_npu (
        .clk(clk), .rst_n(rst_n),
        .instr_valid_i(tensor_instr_valid_i),
        .tensor_op_i(tensor_op_i),
        .branch_id_i(phase0_state_token.branch_id),
        .state_id_i(phase0_state_token.state_id),
        .tensor_a_id_i(tensor_a_id_i), .tensor_b_id_i(tensor_b_id_i), .tensor_c_id_i(tensor_c_id_i),
        .rows_i(tensor_rows_i), .cols_i(tensor_cols_i), .inner_dim_i(tensor_inner_dim_i),
        .node_available_mask_i(~node_fault_mask_i),
        .node_trust_mask_i(~node_untrusted_mask_i),
        .node_cool_mask_i(~node_hot_mask_i),
        .route_req_ready_i(1'b1),
        .route_done_i(fabric_route_done),
        .route_fault_i(fabric_route_fault),
        .inject_numeric_fault_i(tensor_inject_numeric_fault_i),
        .busy_o(tensor_busy), .done_o(tensor_done), .fault_o(tensor_fault), .fault_code_o(tensor_fault_code),
        .tensor_result_valid_o(tensor_result_valid), .tensor_result_id_o(tensor_result_id),
        .numeric_ok_o(tensor_numeric_ok), .npu_audit_req_o(tensor_audit_req), .npu_sync_valid_o(tensor_sync_valid),
        .route_req_valid_o(tensor_route_req_valid), .route_src_node_o(tensor_route_src_node),
        .route_dst_node_o(tensor_route_dst_node), .route_policy_o(tensor_route_policy)
    );

    // -------------------------------------------------------------------------
    // Phase 5 Hybrid Quantum domain.
    // -------------------------------------------------------------------------
    logic quantum_busy, quantum_done, quantum_fault, qsync_valid, qaudit_req, qcommit_allow;
    logic [7:0] qsync_value;
    nvisc_quantum_pkg::nvisc_qfault_e quantum_fault_code;

    nvisc_quantum_domain_engine u_quantum (
        .clk(clk), .rst_n(rst_n),
        .instr_valid_i(quantum_instr_valid_i),
        .qop_i(qop_i), .qmode_i(qmode_i), .qreg_idx_i(qreg_idx_i),
        .branch_id_i(phase0_state_token.branch_id),
        .state_id_i(phase0_state_token.state_id),
        .topology_epoch_i(phase0_state_token.topology_epoch),
        .thermal_epoch_i(phase0_state_token.thermal_epoch),
        .seed_i(q_seed_i),
        .audit_allow_i(commit_allow_o),
        .rollback_invalidate_i(rollback_req_i),
        .rollback_from_state_i(rollback_state_id_i),
        .qhw_force_timeout_i(qhw_force_timeout_i),
        .qhw_force_low_fidelity_i(qhw_force_low_fidelity_i),
        .busy_o(quantum_busy), .done_o(quantum_done), .fault_o(quantum_fault), .fault_code_o(quantum_fault_code),
        .qsync_valid_o(qsync_valid), .qsync_value_o(qsync_value), .qaudit_req_o(qaudit_req), .qcommit_allow_o(qcommit_allow)
    );

    // -------------------------------------------------------------------------
    // Phase 1 RSM rollback integration. Metadata table ports remain explicit so the
    // memory hierarchy can be replaced by true SRAM/table instances in the next pass.
    // -------------------------------------------------------------------------
    nvisc_rsm_pkg::nvisc_state_meta_t  rsm_state_meta_stub;
    nvisc_rsm_pkg::nvisc_branch_meta_t rsm_branch_meta_stub;
    logic rsm_state_meta_rd_req, rsm_branch_meta_rd_req, rsm_branch_meta_wr_req;
    logic rollback_busy, rollback_done, rollback_fault;
    nvisc_rsm_pkg::nvisc_rsm_rollback_fault_e rollback_fault_code;
    logic active_root_update, invalidate_descendants, delta_log_full;
    logic [31:0] active_page_root, new_active_state_id, new_active_commit_id, invalidate_from_state_id, delta_log_count;

    always_comb begin
        rsm_state_meta_stub = '0;
        rsm_state_meta_stub.valid = 1'b1;
        rsm_state_meta_stub.state_id = rollback_state_id_i;
        rsm_state_meta_stub.branch_id = phase0_state_token.branch_id;
        rsm_state_meta_stub.commit_id = candidate_commit_id_i;
        rsm_state_meta_stub.page_root_id = 32'h0000_1000;
        rsm_state_meta_stub.rollback_valid = rollback_available_i;
        rsm_state_meta_stub.sealed = 1'b1;
        rsm_state_meta_stub.aegis_audited = audit_token_valid_i;

        rsm_branch_meta_stub = '0;
        rsm_branch_meta_stub.valid = 1'b1;
        rsm_branch_meta_stub.branch_id = phase0_state_token.branch_id;
        rsm_branch_meta_stub.head_state_id = phase0_state_token.state_id;
        rsm_branch_meta_stub.commit_id = candidate_commit_id_i;
        rsm_branch_meta_stub.rollback_allowed = rollback_available_i;
        rsm_branch_meta_stub.aegis_trusted = commit_allow_o;
    end

    nvisc_rsm_controller_phase1_rollback u_rsm_rollback (
        .clk(clk), .rst_n(rst_n),
        .rollback_req_i(rollback_req_i), .rollback_state_id_i(rollback_state_id_i),
        .active_branch_id_i(phase0_state_token.branch_id), .active_state_id_i(phase0_state_token.state_id),
        .aegis_rollback_allow_i(!commit_quarantine_o),
        .state_meta_rd_data_i(rsm_state_meta_stub), .state_meta_rd_valid_i(1'b1),
        .state_meta_rd_req_o(rsm_state_meta_rd_req), .state_meta_rd_state_id_o(),
        .branch_meta_rd_data_i(rsm_branch_meta_stub), .branch_meta_rd_valid_i(1'b1),
        .branch_meta_rd_req_o(rsm_branch_meta_rd_req), .branch_meta_rd_branch_id_o(),
        .branch_meta_wr_req_o(rsm_branch_meta_wr_req), .branch_meta_wr_branch_id_o(), .branch_meta_wr_data_o(),
        .rollback_busy_o(rollback_busy), .rollback_done_o(rollback_done), .rollback_fault_o(rollback_fault), .rollback_fault_code_o(rollback_fault_code),
        .active_root_update_o(active_root_update), .active_page_root_o(active_page_root),
        .new_active_state_id_o(new_active_state_id), .new_active_commit_id_o(new_active_commit_id),
        .invalidate_descendants_o(invalidate_descendants), .invalidate_from_state_id_o(invalidate_from_state_id),
        .delta_log_full_o(delta_log_full), .delta_log_count_o(delta_log_count)
    );

    // -------------------------------------------------------------------------
    // Phase 1 Aegis Enclave / commit gate.
    // -------------------------------------------------------------------------
    nvisc_aegis_pkg::nvisc_attest_token_t attest_token;
    nvisc_aegis_pkg::nvisc_minrep_t minrep;
    logic [7:0] session_trust_score;
    logic seal_state, seal_branch;
    logic [31:0] seal_state_id, seal_branch_id;

    nvisc_aegis_enclave u_aegis (
        .clk(clk), .rst_n(rst_n),
        .commit_req_i(commit_req_i),
        .candidate_state_id_i(candidate_state_id_i), .candidate_branch_id_i(candidate_branch_id_i), .candidate_commit_id_i(candidate_commit_id_i),
        .candidate_state_hash_i(candidate_state_hash_i), .policy_id_i(policy_id_i),
        .audit_token_valid_i(audit_token_valid_i), .audit_token_subject_hash_i(audit_token_subject_hash_i),
        .memory_hash_ok_i(memory_hash_ok_i), .rsm_integrity_ok_i(rsm_integrity_ok_i && !rollback_fault && !delta_log_full),
        .branch_lineage_ok_i(branch_lineage_ok_i), .io_provenance_ok_i(io_provenance_ok_i), .hid_chain_ok_i(hid_chain_ok_i),
        .gpu_path_ok_i(gpu_path_ok_i), .thermal_safe_i(thermal_safe_i), .voltage_safe_i(voltage_safe_i),
        .route_token_valid_i(fabric_route_token.valid || phase0_topology_token.valid),
        .rollback_available_i(rollback_available_i && !rollback_fault),
        .numeric_integrity_ok_i(numeric_integrity_ok_i && tensor_numeric_ok),
        .tamper_detected_i(tamper_detected_i), .safeguard_bypass_i(safeguard_bypass_i),
        .minrep_req_i(minrep_req_i), .session_id_i(session_id_i),
        .commit_allow_o(commit_allow_o), .commit_deny_o(commit_deny_o), .commit_refuse_o(commit_refuse_o), .commit_quarantine_o(commit_quarantine_o),
        .seal_state_o(seal_state), .seal_state_id_o(seal_state_id), .seal_branch_o(seal_branch), .seal_branch_id_o(seal_branch_id),
        .attest_valid_o(attest_valid_o), .attest_token_o(attest_token),
        .minrep_valid_o(minrep_valid_o), .minrep_o(minrep),
        .session_trust_score_o(session_trust_score)
    );

    // -------------------------------------------------------------------------
    // Status aggregation.
    // -------------------------------------------------------------------------
    always_comb begin
        soc_status_o = '0;
        soc_status_o.valid = 1'b1;
        soc_status_o.active_branch_id = phase0_state_token.branch_id;
        soc_status_o.active_state_id = rollback_done ? new_active_state_id : phase0_state_token.state_id;
        soc_status_o.active_commit_id = rollback_done ? new_active_commit_id : candidate_commit_id_i;
        soc_status_o.topology_epoch = phase0_state_token.topology_epoch;
        soc_status_o.thermal_epoch = phase0_state_token.thermal_epoch;
        soc_status_o.aegis_commit_allow = commit_allow_o;
        soc_status_o.aegis_quarantine = commit_quarantine_o;
        soc_status_o.topology_route_done = fabric_route_done || phase0_route_done;
        soc_status_o.tensor_done = tensor_done;
        soc_status_o.quantum_done = quantum_done;

        if (rollback_fault) soc_status_o.fault_code = SOC_FAULT_RSM;
        else if (commit_quarantine_o || commit_refuse_o) soc_status_o.fault_code = SOC_FAULT_QUARANTINE;
        else if (fabric_route_fault || phase0_route_fault) soc_status_o.fault_code = SOC_FAULT_TOPOLOGY;
        else if (tensor_fault) soc_status_o.fault_code = SOC_FAULT_TENSOR;
        else if (quantum_fault) soc_status_o.fault_code = SOC_FAULT_QUANTUM;
        else if (commit_deny_o) soc_status_o.fault_code = SOC_FAULT_COMMIT_DENY;
        else soc_status_o.fault_code = SOC_OK;
    end

endmodule
