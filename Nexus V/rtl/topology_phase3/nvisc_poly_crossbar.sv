`timescale 1ns / 1ps

module nvisc_poly_crossbar #(
    parameter int NUM_PORTS = 13,
    parameter int FLIT_W    = 192,
    parameter int PORT_W    = $clog2(NUM_PORTS)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic [NUM_PORTS-1:0]              in_valid_i,
    input  logic [NUM_PORTS-1:0][FLIT_W-1:0] in_flit_i,
    output logic [NUM_PORTS-1:0]              in_ready_o,

    output logic [NUM_PORTS-1:0]              out_valid_o,
    output logic [NUM_PORTS-1:0][FLIT_W-1:0] out_flit_o,
    input  logic [NUM_PORTS-1:0]              out_ready_i,

    input  logic [NUM_PORTS-1:0][PORT_W-1:0] route_sel_i
);

    integer i;
    integer p;

    always_comb begin
        out_valid_o = '0;
        out_flit_o  = '0;
        in_ready_o  = '0;

        // Priority arbitration: lower input port wins if multiple inputs target same output.
        for (i = 0; i < NUM_PORTS; i++) begin
            if (in_valid_i[i]) begin
                p = route_sel_i[i];
                if (p < NUM_PORTS && out_ready_i[p] && !out_valid_o[p]) begin
                    out_valid_o[p] = 1'b1;
                    out_flit_o[p]  = in_flit_i[i];
                    in_ready_o[i]  = 1'b1;
                end
            end
        end
    end

endmodule
