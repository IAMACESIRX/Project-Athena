`timescale 1ns / 1ps

package nexus_v_soc_pkg;

    parameter int SOC_NODE_COUNT = 16;
    parameter int SOC_HASH_W     = 128;
    parameter int SOC_STATE_W    = 32;
    parameter int SOC_BRANCH_W   = 32;

    typedef enum logic [3:0] {
        SOC_OK                 = 4'd0,
        SOC_FAULT_RSM          = 4'd1,
        SOC_FAULT_AEGIS        = 4'd2,
        SOC_FAULT_TOPOLOGY     = 4'd3,
        SOC_FAULT_TENSOR       = 4'd4,
        SOC_FAULT_QUANTUM      = 4'd5,
        SOC_FAULT_COMMIT_DENY  = 4'd6,
        SOC_FAULT_QUARANTINE   = 4'd7
    } nexus_v_soc_fault_e;

    typedef struct packed {
        logic valid;
        logic [31:0] active_branch_id;
        logic [31:0] active_state_id;
        logic [31:0] active_commit_id;
        logic [15:0] topology_epoch;
        logic [15:0] thermal_epoch;
        logic aegis_commit_allow;
        logic aegis_quarantine;
        logic topology_route_done;
        logic tensor_done;
        logic quantum_done;
        nexus_v_soc_fault_e fault_code;
    } nexus_v_soc_status_t;

endpackage
