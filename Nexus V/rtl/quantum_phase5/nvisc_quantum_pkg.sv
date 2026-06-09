`timescale 1ns / 1ps

package nvisc_quantum_pkg;

    parameter int QREG_COUNT = 16;
    parameter int QTOKEN_COUNT = 32;
    parameter int HASH_W = 128;
    parameter int PROB_W = 8;
    parameter int FID_W = 8;

    typedef enum logic [3:0] {
        QMODE_NONE = 4'd0,
        QMODE_QSIM = 4'd1,
        QMODE_QHW  = 4'd2
    } nvisc_qmode_e;

    typedef enum logic [5:0] {
        QOP_NOP       = 6'd0,
        QOP_QALLOC    = 6'd1,
        QOP_QFREE     = 6'd2,
        QOP_QPREP     = 6'd3,
        QOP_QRESET    = 6'd4,
        QOP_QGATE     = 6'd5,
        QOP_QH        = 6'd6,
        QOP_QX        = 6'd7,
        QOP_QCNOT     = 6'd8,
        QOP_QMEASURE  = 6'd9,
        QOP_QSYNC     = 6'd10,
        QOP_QAUDIT    = 6'd11,
        QOP_QCOMMIT   = 6'd12,
        QOP_QROLLBACK = 6'd13,
        QOP_QSTATE    = 6'd14,
        QOP_QFID      = 6'd15,
        QOP_QDECOH    = 6'd16,
        QOP_QHW_DISP  = 6'd17
    } nvisc_qop_e;

    typedef enum logic [7:0] {
        QFAULT_NONE               = 8'd0,
        QFAULT_INVALID_QREG       = 8'd1,
        QFAULT_NOT_PREPARED       = 8'd2,
        QFAULT_UNSUPPORTED_GATE   = 8'd3,
        QFAULT_USE_AFTER_COLLAPSE = 8'd4,
        QFAULT_QHW_TIMEOUT        = 8'd5,
        QFAULT_DECOHERENCE        = 8'd6,
        QFAULT_LOW_FIDELITY       = 8'd7,
        QFAULT_AEGIS_DENIED       = 8'd8,
        QFAULT_EXPIRED_QTOKEN     = 8'd9,
        QFAULT_QMODE_MISMATCH     = 8'd10
    } nvisc_qfault_e;

    typedef struct packed {
        logic        valid;
        logic [31:0] qreg_id;
        logic [31:0] branch_id;
        logic [31:0] state_id;
        nvisc_qmode_e qmode;
        logic [7:0]  num_qubits;
        logic [7:0]  gate_depth;
        logic [15:0] topology_epoch;
        logic [15:0] thermal_epoch;
        logic        prepared;
        logic        measured;
        logic        collapsed;
        logic        synced;
        logic        audited;
        logic        committed;
        logic        rollback_valid;
        logic [7:0]  fidelity_score;
        logic [7:0]  decoherence_risk;
    } nvisc_qreg_meta_t;

    typedef struct packed {
        logic        valid;
        logic [31:0] qreg_id;
        logic [15:0] amp0_re;
        logic [15:0] amp0_im;
        logic [15:0] amp1_re;
        logic [15:0] amp1_im;
        logic [7:0]  prob0;
        logic [7:0]  prob1;
    } nvisc_qsim_state_t;

    typedef struct packed {
        logic        valid;
        logic [31:0] qtoken_id;
        logic [31:0] qreg_id;
        logic [31:0] branch_id;
        logic [31:0] state_id;
        logic [7:0]  measurement_value;
        logic [7:0]  probability;
        logic [7:0]  fidelity_score;
        logic [7:0]  decoherence_risk;
        logic [15:0] topology_epoch;
        logic [15:0] thermal_epoch;
        logic        measured;
        logic        synced;
        logic        audited;
        logic        expired;
        logic        rollback_discard;
    } nvisc_quantum_token_t;

    typedef struct packed {
        logic        valid;
        logic [31:0] qreg_id;
        logic [31:0] qtoken_id;
        logic [31:0] branch_id;
        logic [31:0] state_id;
        logic [7:0]  measured_value;
        logic [7:0]  probability;
        logic [7:0]  fidelity_score;
        logic        collapse_complete;
        logic        sync_required;
        logic        audit_required;
    } nvisc_qcollapse_reg_t;

endpackage
