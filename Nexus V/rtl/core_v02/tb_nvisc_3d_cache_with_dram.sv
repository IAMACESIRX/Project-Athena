`timescale 1ns / 1ps

module tb_nvisc_3d_cache_with_dram #(
    parameter int ID_W = 8
)(
    input  logic clk,
    input  logic rst_n,

    // Upper side request.
    input  logic            req_valid_i,
    input  logic            req_is_read_i,
    input  logic            req_is_write_i,
    input  logic [63:0]     req_paddr_i,
    input  logic [63:0]     req_wdata_i,
    input  logic [7:0]      req_size_bytes_i,
    input  logic [ID_W-1:0] req_id_i,

    // Upper side response.
    output logic            resp_valid_o,
    output logic [63:0]     resp_rdata_o,
    output logic            resp_write_ack_o,
    output logic [ID_W-1:0] resp_id_o,

    output logic            fault_o,
    output logic [15:0]     fault_code_o,

    input  logic            flush_i,

    // 3D cache debug.
    output logic            dbg_cache_hit_o,
    output logic            dbg_cache_miss_o,
    output logic            dbg_cache_fill_o,
    output logic            dbg_cache_store_o,
    output logic [63:0]     dbg_cache_data_o,

    // DRAM debug.
    output logic            dbg_dram_busy_o,
    output logic [63:0]     dbg_dram_last_paddr_o,
    output logic [63:0]     dbg_dram_last_wdata_o,
    output logic [63:0]     dbg_dram_last_rdata_o
);

    logic            cache_mem_req_valid_w;
    logic            cache_mem_req_is_read_w;
    logic            cache_mem_req_is_write_w;
    logic [63:0]     cache_mem_req_paddr_w;
    logic [63:0]     cache_mem_req_wdata_w;
    logic [7:0]      cache_mem_req_size_bytes_w;
    logic [ID_W-1:0] cache_mem_req_id_w;

    logic            dram_resp_valid_w;
    logic [63:0]     dram_resp_rdata_w;
    logic            dram_resp_write_ack_w;
    logic [ID_W-1:0] dram_resp_id_w;

    logic            dram_fault_w;
    logic [15:0]     dram_fault_code_w;

    nvisc_3d_cache_stub #(
        .NUM_LINES(16),
        .ID_W(ID_W)
    ) u_3d_cache (
        .clk(clk),
        .rst_n(rst_n),

        .core_req_valid_i(req_valid_i),
        .core_req_is_read_i(req_is_read_i),
        .core_req_is_write_i(req_is_write_i),
        .core_req_paddr_i(req_paddr_i),
        .core_req_wdata_i(req_wdata_i),
        .core_req_size_bytes_i(req_size_bytes_i),
        .core_req_id_i(req_id_i),

        .core_resp_valid_o(resp_valid_o),
        .core_resp_rdata_o(resp_rdata_o),
        .core_resp_write_ack_o(resp_write_ack_o),
        .core_resp_id_o(resp_id_o),

        .core_fault_o(fault_o),
        .core_fault_code_o(fault_code_o),

        .mem_req_valid_o(cache_mem_req_valid_w),
        .mem_req_is_read_o(cache_mem_req_is_read_w),
        .mem_req_is_write_o(cache_mem_req_is_write_w),
        .mem_req_paddr_o(cache_mem_req_paddr_w),
        .mem_req_wdata_o(cache_mem_req_wdata_w),
        .mem_req_size_bytes_o(cache_mem_req_size_bytes_w),
        .mem_req_id_o(cache_mem_req_id_w),

        .mem_resp_valid_i(dram_resp_valid_w),
        .mem_resp_rdata_i(dram_resp_rdata_w),
        .mem_resp_write_ack_i(dram_resp_write_ack_w),
        .mem_resp_id_i(dram_resp_id_w),

        .mem_fault_i(dram_fault_w),
        .mem_fault_code_i(dram_fault_code_w),

        .flush_i(flush_i),

        .dbg_hit_o(dbg_cache_hit_o),
        .dbg_miss_o(dbg_cache_miss_o),
        .dbg_fill_o(dbg_cache_fill_o),
        .dbg_store_o(dbg_cache_store_o),
        .dbg_cached_data_o(dbg_cache_data_o)
    );

    nvisc_dram_controller_stub #(
        .BASE_ADDR(64'h0000_0000_8000_0000),
        .MEM_WORDS(1024),
        .LATENCY_CYCLES(3),
        .ID_W(ID_W)
    ) u_dram (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(cache_mem_req_valid_w),
        .req_is_read_i(cache_mem_req_is_read_w),
        .req_is_write_i(cache_mem_req_is_write_w),
        .req_paddr_i(cache_mem_req_paddr_w),
        .req_wdata_i(cache_mem_req_wdata_w),
        .req_size_bytes_i(cache_mem_req_size_bytes_w),
        .req_id_i(cache_mem_req_id_w),

        .resp_valid_o(dram_resp_valid_w),
        .resp_rdata_o(dram_resp_rdata_w),
        .resp_write_ack_o(dram_resp_write_ack_w),
        .resp_id_o(dram_resp_id_w),

        .fault_o(dram_fault_w),
        .fault_code_o(dram_fault_code_w),

        .dbg_busy_o(dbg_dram_busy_o),
        .dbg_last_paddr_o(dbg_dram_last_paddr_o),
        .dbg_last_wdata_o(dbg_dram_last_wdata_o),
        .dbg_last_rdata_o(dbg_dram_last_rdata_o)
    );

endmodule
