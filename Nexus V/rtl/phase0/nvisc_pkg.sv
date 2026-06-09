package nvisc_pkg;

    parameter int XLEN       = 64;
    parameter int FLEN       = 64;
    parameter int DLEN       = 128;
    parameter int MLEN       = 8;
    parameter int TLEN       = 128;
    parameter int SLEN       = 128;
    parameter int PLEN       = 1;
    parameter int CLEN       = 128;

    parameter int REG_COUNT  = 32;
    parameter int PRED_COUNT = 16;
    parameter int CAP_COUNT  = 16;

    typedef enum logic [3:0] {
        DOMAIN_BIN    = 4'd0,
        DOMAIN_TERN   = 4'd1,
        DOMAIN_QUAD   = 4'd2,
        DOMAIN_NSTATE = 4'd3,
        DOMAIN_DEC    = 4'd4,
        DOMAIN_FLOAT  = 4'd5,
        DOMAIN_TENSOR = 4'd6,
        DOMAIN_STATE  = 4'd7,
        DOMAIN_QSIM   = 4'd8
    } nvisc_domain_e;

    typedef enum logic [5:0] {
        ALU_NOP    = 6'd0,
        ALU_ADD    = 6'd1,
        ALU_SUB    = 6'd2,
        ALU_AND    = 6'd3,
        ALU_OR     = 6'd4,
        ALU_XOR    = 6'd5,
        ALU_NOT    = 6'd6,
        ALU_SHL    = 6'd7,
        ALU_SHR    = 6'd8,
        ALU_CMP    = 6'd9,
        ALU_MSET   = 6'd10,
        ALU_MADD   = 6'd11,
        ALU_PASSA  = 6'd12,
        ALU_PASSB  = 6'd13,
        ALU_ROUTE  = 6'd14
    } nvisc_alu_op_e;

    typedef enum logic [2:0] {
        ROUTE_SRC_LOCAL  = 3'd0,
        ROUTE_SRC_FACE   = 3'd1,
        ROUTE_SRC_EDGE   = 3'd2,
        ROUTE_SRC_VERTEX = 3'd3,
        ROUTE_SRC_Z_UP   = 3'd4,
        ROUTE_SRC_Z_DOWN = 3'd5,
        ROUTE_SRC_ZERO   = 3'd6
    } nvisc_route_src_e;

    typedef enum logic [2:0] {
        ROUTE_FAST      = 3'd0,
        ROUTE_SAFE      = 3'd1,
        ROUTE_COOL      = 3'd2,
        ROUTE_LOW_POWER = 3'd3,
        ROUTE_REDUNDANT = 3'd4
    } nvisc_route_policy_e;

    typedef struct packed {
        logic [31:0] branch_id;
        logic [31:0] state_id;
        logic [31:0] commit_id;
        logic [15:0] topology_epoch;
        logic [15:0] thermal_epoch;
        logic [7:0]  domain;
        logic        valid;
        logic        committed;
        logic        sealed;
        logic        rollback_valid;
    } nvisc_state_token_t;

    typedef struct packed {
        logic                 valid;
        logic [15:0]          source_node;
        logic [15:0]          target_node;
        nvisc_route_policy_e  policy;
        logic [15:0]          topology_epoch;
        logic [15:0]          thermal_epoch;
        logic [31:0]          branch_id;
        logic [31:0]          state_id;
    } nvisc_route_req_t;

    typedef struct packed {
        logic                 valid;
        logic                 ready;
        logic                 fault;
        logic [31:0]          token_id;
        logic [15:0]          route_id;
        logic [15:0]          selected_path_id;
        logic [15:0]          source_node;
        logic [15:0]          target_node;
        nvisc_route_policy_e  policy;
        logic [15:0]          topology_epoch;
        logic [15:0]          thermal_epoch;
    } nvisc_route_resp_t;

    typedef struct packed {
        logic                 valid;
        logic [31:0]          token_id;
        logic [15:0]          source_node;
        logic [15:0]          target_node;
        logic [15:0]          path_id;
        nvisc_route_policy_e  policy;
        logic [15:0]          topology_epoch;
        logic [15:0]          thermal_epoch;
        logic [2:0]           privilege_level;
        logic                 aegis_approved;
    } nvisc_topology_token_t;

endpackage
