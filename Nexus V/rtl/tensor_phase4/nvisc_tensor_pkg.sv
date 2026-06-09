`timescale 1ns / 1ps

package nvisc_tensor_pkg;

    parameter int NUM_TENSOR_NODES = 16;
    parameter int TENSOR_ID_W      = 32;
    parameter int STATE_ID_W       = 32;
    parameter int BRANCH_ID_W      = 32;
    parameter int DATA_W           = 32;
    parameter int ACC_W            = 64;
    parameter int TILE_W           = 16;
    parameter int ROUTE_ID_W       = 16;

    typedef enum logic [3:0] {
        TENSOR_OP_NOP     = 4'd0,
        TENSOR_OP_TLOAD   = 4'd1,
        TENSOR_OP_TSTORE  = 4'd2,
        TENSOR_OP_TMATMUL = 4'd3,
        TENSOR_OP_TREDUCE = 4'd4,
        TENSOR_OP_TINFER  = 4'd5,
        TENSOR_OP_NPU_SYNC  = 4'd6,
        TENSOR_OP_NPU_AUDIT = 4'd7
    } nvisc_tensor_op_e;

    typedef enum logic [2:0] {
        TENSOR_DTYPE_INT8  = 3'd0,
        TENSOR_DTYPE_INT16 = 3'd1,
        TENSOR_DTYPE_FP16  = 3'd2,
        TENSOR_DTYPE_BF16  = 3'd3,
        TENSOR_DTYPE_FP32  = 3'd4,
        TENSOR_DTYPE_FP64  = 3'd5,
        TENSOR_DTYPE_DEC   = 3'd6,
        TENSOR_DTYPE_MVL   = 3'd7
    } nvisc_tensor_dtype_e;

    typedef enum logic [2:0] {
        TENSOR_LAYOUT_ROW_MAJOR = 3'd0,
        TENSOR_LAYOUT_COL_MAJOR = 3'd1,
        TENSOR_LAYOUT_TILED     = 3'd2,
        TENSOR_LAYOUT_BLOCKED   = 3'd3
    } nvisc_tensor_layout_e;

    typedef enum logic [7:0] {
        TENSOR_FAULT_NONE           = 8'd0,
        TENSOR_FAULT_BAD_DESC       = 8'd1,
        TENSOR_FAULT_SHAPE_MISMATCH = 8'd2,
        TENSOR_FAULT_TOPO_BUSY      = 8'd3,
        TENSOR_FAULT_ROUTE_FAULT    = 8'd4,
        TENSOR_FAULT_NUMERIC        = 8'd5,
        TENSOR_FAULT_NODE_MASKED    = 8'd6,
        TENSOR_FAULT_AEGIS_DENY     = 8'd7
    } nvisc_tensor_fault_e;

    typedef struct packed {
        logic                       valid;
        logic [TENSOR_ID_W-1:0]     tensor_id;
        logic [BRANCH_ID_W-1:0]     branch_id;
        logic [STATE_ID_W-1:0]      state_id;
        logic [15:0]                rows;
        logic [15:0]                cols;
        logic [15:0]                inner_dim;
        nvisc_tensor_dtype_e        dtype;
        nvisc_tensor_layout_e       layout;
        logic [31:0]                base_addr;
        logic [31:0]                stride_row;
        logic [31:0]                stride_col;
        logic [15:0]                topology_epoch;
        logic [15:0]                thermal_epoch;
        logic                       numeric_checked;
        logic                       aegis_audited;
        logic                       sealed;
    } nvisc_tensor_desc_t;

    typedef struct packed {
        logic                       valid;
        logic [15:0]                node_id;
        logic [TENSOR_ID_W-1:0]     tensor_a_id;
        logic [TENSOR_ID_W-1:0]     tensor_b_id;
        logic [TENSOR_ID_W-1:0]     tensor_c_id;
        logic [15:0]                tile_m;
        logic [15:0]                tile_n;
        logic [15:0]                tile_k_start;
        logic [15:0]                tile_k_count;
        logic [BRANCH_ID_W-1:0]     branch_id;
        logic [STATE_ID_W-1:0]      state_id;
    } nvisc_tensor_tile_job_t;

    typedef struct packed {
        logic                       valid;
        logic [ROUTE_ID_W-1:0]      route_id;
        logic [TENSOR_ID_W-1:0]     tensor_id;
        logic [BRANCH_ID_W-1:0]     branch_id;
        logic [STATE_ID_W-1:0]      state_id;
        logic [15:0]                tile_m;
        logic [15:0]                tile_n;
        logic [15:0]                tile_k;
        nvisc_tensor_dtype_e        dtype;
        logic [7:0]                 lane_mask;
        logic [127:0]               payload;
        logic                       partial_sum;
        logic                       last;
    } nvisc_tensor_flit_t;

endpackage
