`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module tb_nvisc_data_lane_3d_dram (
    input  logic clk,
    input  logic rst_n,

    // DATA-domain request from router / MMU.
    input  logic        req_valid_i,
    input  logic        req_is_read_i,
    input  logic        req_is_write_i,
    input  logic [63:0] req_paddr_i,
    input  logic [63:0] req_wdata_i,
    input  logic [7:0]  req_size_bytes_i,
    input  nvisc_exec_identity_t req_id_i,

    // DATA-domain response.
    output logic        resp_valid_o,
    output logic [63:0] resp_rdata_o,
    output logic        resp_write_ack_o,

    output logic        fault_o,
    output logic [15:0] fault_code_o,

    input  logic        flush_l1d_i,
    input  logic        flush_3d_i,

    output logic        dbg_l1d_hit_o,
    output logic        dbg_l1d_miss_o,
    output logic        dbg_l1d_fill_o,

    output logic        dbg_3d_hit_o,
    output logic        dbg_3d_miss_o,
    output logic        dbg_3d_fill_o,
    output logic        dbg_3d_store_o,

    output logic        dbg_dram_busy_o
);

    // L1D -> 3D cache wires.
    logic        l1d_mem_req_valid_w;
    logic        l1d_mem_req_is_read_w;
    logic        l1d_mem_req_is_write_w;
    logic [63:0] l1d_mem_req_paddr_w;
    logic [63:0] l1d_mem_req_wdata_w;
    logic [7:0]  l1d_mem_req_size_bytes_w;
    nvisc_mem_domain_e l1d_mem_req_domain_w;
    nvisc_exec_identity_t l1d_mem_req_id_w;

    // 3D+DRAM response back into L1D.
    logic        cache3d_resp_valid_w;
    logic [63:0] cache3d_resp_rdata_w;
    logic        cache3d_resp_write_ack_w;
    logic        cache3d_fault_w;
    logic [15:0] cache3d_fault_code_w;

    logic [7:0] id_flat_w;

    assign id_flat_w = req_id_i.thread_id[7:0];

    nvisc_l1d_cache_stub u_l1d (
        .clk(clk),
        .rst_n(rst_n),

        .flush_i(flush_l1d_i),

        .core_req_valid_i(req_valid_i),
        .core_req_is_read_i(req_is_read_i),
        .core_req_is_write_i(req_is_write_i),
        .core_req_paddr_i(req_paddr_i),
        .core_req_wdata_i(req_wdata_i),
        .core_req_size_bytes_i(req_size_bytes_i),
        .core_req_mem_domain_i(NV_MEM_DATA),
        .core_req_id_i(req_id_i),

        .core_resp_valid_o(resp_valid_o),
        .core_resp_rdata_o(resp_rdata_o),
        .core_resp_write_ack_o(resp_write_ack_o),
        .core_fault_o(fault_o),
        .core_fault_code_o(fault_code_o),

        .mem_req_valid_o(l1d_mem_req_valid_w),
        .mem_req_is_read_o(l1d_mem_req_is_read_w),
        .mem_req_is_write_o(l1d_mem_req_is_write_w),
        .mem_req_paddr_o(l1d_mem_req_paddr_w),
        .mem_req_wdata_o(l1d_mem_req_wdata_w),
        .mem_req_size_bytes_o(l1d_mem_req_size_bytes_w),
        .mem_req_mem_domain_o(l1d_mem_req_domain_w),
        .mem_req_id_o(l1d_mem_req_id_w),

        .mem_resp_valid_i(cache3d_resp_valid_w),
        .mem_resp_rdata_i(cache3d_resp_rdata_w),
        .mem_resp_write_ack_i(cache3d_resp_write_ack_w),
        .mem_fault_i(cache3d_fault_w),
        .mem_fault_code_i(cache3d_fault_code_w),

        .dbg_hit_o(dbg_l1d_hit_o),
        .dbg_miss_o(dbg_l1d_miss_o),
        .dbg_fill_o(dbg_l1d_fill_o),
        .dbg_cached_data_o()
    );

    tb_nvisc_3d_cache_with_dram u_3d_dram (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(l1d_mem_req_valid_w),
        .req_is_read_i(l1d_mem_req_is_read_w),
        .req_is_write_i(l1d_mem_req_is_write_w),
        .req_paddr_i(l1d_mem_req_paddr_w),
        .req_wdata_i(l1d_mem_req_wdata_w),
        .req_size_bytes_i(l1d_mem_req_size_bytes_w),
        .req_id_i(id_flat_w),

        .resp_valid_o(cache3d_resp_valid_w),
        .resp_rdata_o(cache3d_resp_rdata_w),
        .resp_write_ack_o(cache3d_resp_write_ack_w),
        .resp_id_o(),

        .fault_o(cache3d_fault_w),
        .fault_code_o(cache3d_fault_code_w),

        .flush_i(flush_3d_i),

        .dbg_cache_hit_o(dbg_3d_hit_o),
        .dbg_cache_miss_o(dbg_3d_miss_o),
        .dbg_cache_fill_o(dbg_3d_fill_o),
        .dbg_cache_store_o(dbg_3d_store_o),
        .dbg_cache_data_o(),

        .dbg_dram_busy_o(dbg_dram_busy_o),
        .dbg_dram_last_paddr_o(),
        .dbg_dram_last_wdata_o(),
        .dbg_dram_last_rdata_o()
    );

endmodule
