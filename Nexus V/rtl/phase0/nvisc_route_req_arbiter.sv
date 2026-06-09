`timescale 1ns / 1ps

import nvisc_pkg::*;

module nvisc_route_req_arbiter (
    input  nvisc_route_req_t alu_req_i,
    input  nvisc_route_req_t g_req_i,
    output nvisc_route_req_t route_req_o
);

    always_comb begin
        route_req_o = '0;

        // Phase 0 policy: explicit G.ROUTE wins over ALU_ROUTE fast path.
        if (g_req_i.valid) begin
            route_req_o = g_req_i;
        end else if (alu_req_i.valid) begin
            route_req_o = alu_req_i;
        end
    end
endmodule
