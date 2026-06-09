`timescale 1ns / 1ps

interface nvisc_topology_fabric_if;
    import nvisc_pkg::*;

    logic clk;
    logic rst_n;

    nvisc_route_req_t  route_req;
    nvisc_route_resp_t route_resp;

    modport requester (
        input  clk,
        input  rst_n,
        output route_req,
        input  route_resp
    );

    modport fabric (
        input  clk,
        input  rst_n,
        input  route_req,
        output route_resp
    );
endinterface
