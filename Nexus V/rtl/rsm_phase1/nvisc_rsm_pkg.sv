package nvisc_rsm_pkg;
    parameter int PADDR_W      = 32;
    parameter int LADDR_W      = 32;
    parameter int NUM_PAGES    = 256;
    parameter int PAGE_BYTES   = 4096;
    parameter int PAGE_IDX_W   = $clog2(NUM_PAGES);
    parameter int NUM_BRANCHES = 64;
    parameter int NUM_STATES   = 256;
    parameter int BRANCH_IDX_W = $clog2(NUM_BRANCHES);
    parameter int STATE_IDX_W  = $clog2(NUM_STATES);

    parameter logic [PADDR_W-1:0] PHYS_BASE_ADDR = 32'h0000_0000;

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
    } nvisc_state_meta_t;

    typedef enum logic [2:0] {
        RSM_IDLE       = 3'd0,
        RSM_CHECK_SEAL = 3'd1,
        RSM_ALLOC      = 3'd2,
        RSM_REMAP      = 3'd3,
        RSM_DONE       = 3'd4,
        RSM_FAULT      = 3'd5
    } nvisc_rsm_fsm_e;
endpackage
