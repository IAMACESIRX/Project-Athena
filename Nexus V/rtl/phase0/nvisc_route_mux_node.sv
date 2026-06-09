`timescale 1ns / 1ps

import nvisc_pkg::*;

module nvisc_route_mux_node #(
    parameter int DATA_W     = XLEN,
    parameter int FACE_PORTS = 12,
    parameter int EDGE_PORTS = 24,
    parameter int VERT_PORTS = 14
)(
    input  logic [DATA_W-1:0] local_i,
    input  logic [FACE_PORTS-1:0][DATA_W-1:0] face_i,
    input  logic [EDGE_PORTS-1:0][DATA_W-1:0] edge_i,
    input  logic [VERT_PORTS-1:0][DATA_W-1:0] vertex_i,
    input  logic [DATA_W-1:0] z_up_i,
    input  logic [DATA_W-1:0] z_down_i,

    input  nvisc_route_src_e src_sel_i,
    input  logic [5:0]       port_sel_i,

    output logic [DATA_W-1:0] data_o,
    output logic              fault_o
);

    always_comb begin
        data_o  = '0;
        fault_o = 1'b0;

        unique case (src_sel_i)
            ROUTE_SRC_LOCAL: begin
                data_o = local_i;
            end

            ROUTE_SRC_FACE: begin
                if (port_sel_i < FACE_PORTS) data_o = face_i[port_sel_i];
                else fault_o = 1'b1;
            end

            ROUTE_SRC_EDGE: begin
                if (port_sel_i < EDGE_PORTS) data_o = edge_i[port_sel_i];
                else fault_o = 1'b1;
            end

            ROUTE_SRC_VERTEX: begin
                if (port_sel_i < VERT_PORTS) data_o = vertex_i[port_sel_i];
                else fault_o = 1'b1;
            end

            ROUTE_SRC_Z_UP: begin
                data_o = z_up_i;
            end

            ROUTE_SRC_Z_DOWN: begin
                data_o = z_down_i;
            end

            ROUTE_SRC_ZERO: begin
                data_o = '0;
            end

            default: begin
                data_o  = '0;
                fault_o = 1'b1;
            end
        endcase
    end

endmodule
