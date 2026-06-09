`timescale 1ns / 1ps

package nvisc_aegis_pkg;

    parameter int HASH_W  = 128;
    parameter int SCORE_W = 8;
    parameter int TOKEN_ID_W = 32;
    parameter int POLICY_ID_W = 16;

    typedef enum logic [2:0] {
        AEGIS_DECISION_NONE       = 3'd0,
        AEGIS_DECISION_ALLOW      = 3'd1,
        AEGIS_DECISION_DENY       = 3'd2,
        AEGIS_DECISION_REFUSE     = 3'd3,
        AEGIS_DECISION_QUARANTINE = 3'd4,
        AEGIS_DECISION_ROLLBACK   = 3'd5
    } nvisc_aegis_decision_e;

    typedef struct packed {
        logic        valid;
        logic [31:0] token_id;
        logic [31:0] state_id;
        logic [31:0] branch_id;
        logic [31:0] commit_id;
        logic [15:0] policy_id;
        logic [127:0] subject_hash;
        logic [127:0] telemetry_digest;
        logic [63:0] monotonic_counter;
        logic [127:0] token_mac;
    } nvisc_attest_token_t;

    typedef struct packed {
        logic        valid;
        logic [31:0] report_id;
        logic [31:0] session_id;
        logic [7:0]  trust_score_bucket;
        logic        game_binary_verified;
        logic        memory_integrity_verified;
        logic        input_chain_trusted;
        logic        gpu_path_verified;
        logic        rollback_available;
        logic        aegis_active;
        logic        unauthorized_overlay_detected;
        logic        tamper_detected;
        logic [127:0] report_mac;
    } nvisc_minrep_t;

endpackage
