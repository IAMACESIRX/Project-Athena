package nvisc_rsm_pkg;

    parameter int STATE_ID_W   = 32;
    parameter int BRANCH_ID_W  = 32;
    parameter int COMMIT_ID_W  = 32;
    parameter int PAGE_ROOT_W  = 32;
    parameter int PADDR_W      = 32;
    parameter int LOGICAL_PAGE_W = 32;

    typedef enum logic [3:0] {
        RB_IDLE,
        RB_LOOKUP_STATE,
        RB_VALIDATE_STATE,
        RB_LOOKUP_BRANCH,
        RB_VALIDATE_BRANCH,
        RB_FLUSH_DESCENDANTS,
        RB_REBIND_ROOT,
        RB_UPDATE_BRANCH_HEAD,
        RB_INVALIDATE_TOKENS,
        RB_LOG_EVENT,
        RB_DONE,
        RB_FAULT
    } nvisc_rsm_rollback_fsm_e;

    typedef enum logic [7:0] {
        RB_OK                         = 8'd0,
        RB_FAULT_INVALID_TARGET       = 8'd1,
        RB_FAULT_NOT_ROLLBACKABLE     = 8'd2,
        RB_FAULT_BRANCH_MISMATCH      = 8'd3,
        RB_FAULT_PRUNED_STATE         = 8'd4,
        RB_FAULT_AEGIS_DENIED         = 8'd5,
        RB_FAULT_BAD_PAGE_ROOT        = 8'd6,
        RB_FAULT_LINEAGE_CONFLICT     = 8'd7
    } nvisc_rsm_rollback_fault_e;

    typedef enum logic [7:0] {
        DELTA_NONE          = 8'd0,
        DELTA_COW_REMAP     = 8'd1,
        DELTA_STORE_DIRTY   = 8'd2,
        DELTA_BRANCH_CREATE = 8'd3,
        DELTA_COMMIT        = 8'd4,
        DELTA_ROLLBACK      = 8'd5,
        DELTA_SEAL          = 8'd6,
        DELTA_UNSEAL        = 8'd7,
        DELTA_PRUNE         = 8'd8
    } nvisc_rsm_delta_op_e;

    typedef struct packed {
        logic        valid;
        logic [31:0] branch_id;
        logic [31:0] parent_branch_id;
        logic [31:0] root_state_id;
        logic [31:0] head_state_id;
        logic [31:0] commit_id;
        logic [15:0] branch_depth;
        logic [15:0] refcount;
        logic        speculative;
        logic        committed;
        logic        sealed;
        logic        rollback_allowed;
        logic        aegis_trusted;
        logic        pruned;
    } nvisc_branch_meta_t;

    typedef struct packed {
        logic        valid;
        logic [31:0] state_id;
        logic [31:0] branch_id;
        logic [31:0] parent_state_id;
        logic [31:0] commit_id;
        logic [31:0] page_root_id;
        logic [31:0] delta_log_ptr;
        logic [63:0] state_hash_lo;
        logic [63:0] state_hash_hi;
        logic        snapshot;
        logic        committed;
        logic        sealed;
        logic        rollback_valid;
        logic        dirty;
        logic        aegis_audited;
        logic        pruned;
    } nvisc_state_meta_t;

    typedef struct packed {
        logic        valid;
        logic [31:0] delta_id;
        logic [31:0] branch_id;
        logic [31:0] from_state_id;
        logic [31:0] to_state_id;
        logic [31:0] logical_page;
        logic [31:0] old_paddr;
        logic [31:0] new_paddr;
        logic [31:0] commit_id;
        nvisc_rsm_delta_op_e op_kind;
        logic        cow_event;
        logic        rollback_event;
        logic        commit_event;
        logic        sealed_event;
    } nvisc_rsm_delta_entry_t;

endpackage
