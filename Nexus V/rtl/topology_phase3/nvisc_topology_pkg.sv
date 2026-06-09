`timescale 1ns / 1ps

package nvisc_topology_pkg;
    import nvisc_pkg::*;

    parameter int NODE_ID_W      = 16;
    parameter int ROUTE_ID_W     = 16;
    parameter int BRANCH_ID_W    = 32;
    parameter int STATE_ID_W     = 32;
    parameter int EPOCH_W        = 16;
    parameter int PAYLOAD_W      = 64;
    parameter int FLIT_W         = 192;
    parameter int NUM_NODES_DFLT = 16;
    parameter int NUM_PORTS_DFLT = 13;

    /* route policy enum provided by nvisc_pkg */

    typedef enum logic [3:0] {
        PORT_LOCAL   = 4'd0,
        PORT_FACE0   = 4'd1,
        PORT_FACE1   = 4'd2,
        PORT_FACE2   = 4'd3,
        PORT_FACE3   = 4'd4,
        PORT_EDGE0   = 4'd5,
        PORT_EDGE1   = 4'd6,
        PORT_EDGE2   = 4'd7,
        PORT_EDGE3   = 4'd8,
        PORT_VERTEX0 = 4'd9,
        PORT_VERTEX1 = 4'd10,
        PORT_Z_UP    = 4'd11,
        PORT_Z_DOWN  = 4'd12
    } nvisc_topology_port_e;

    
    typedef struct packed {
        logic        valid;
        logic [15:0] route_id;
        logic [15:0] src_node;
        logic [15:0] dst_node;
        logic [15:0] current_node;
        logic [7:0]  hop_count;
        nvisc_route_policy_e policy;
        logic [31:0] branch_id;
        logic [31:0] state_id;
        logic [15:0] topology_epoch;
        logic [15:0] thermal_epoch;
        logic [63:0] payload;
        logic        last;
    } nvisc_route_flit_t;

typedef struct packed {
        logic        valid;
        logic [15:0] route_id;
        logic [15:0] src_node;
        logic [15:0] dst_node;
        logic [15:0] path_id;
        nvisc_route_policy_e policy;
        logic [31:0] branch_id;
        logic [31:0] state_id;
        logic [15:0] topology_epoch;
        logic [15:0] thermal_epoch;
        logic        aegis_approved;
        logic        completed;
        logic        faulted;
    } nvisc_topology_token_t;

endpackage
