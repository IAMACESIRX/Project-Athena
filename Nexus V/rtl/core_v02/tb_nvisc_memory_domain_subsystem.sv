`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module tb_nvisc_memory_domain_subsystem (
    input  logic clk,
    input  logic rst_n,

    // Incoming translated memory request.
    input  logic        req_valid_i,
    input  logic        req_is_read_i,
    input  logic        req_is_write_i,
    input  logic [63:0] req_paddr_i,
    input  logic [63:0] req_wdata_i,
    input  logic [7:0]  req_size_bytes_i,
    input  nvisc_mem_domain_e req_mem_domain_i,
    input  nvisc_exec_identity_t req_id_i,

    // Unified subsystem response.
    output logic        resp_valid_o,
    output logic [63:0] resp_rdata_o,
    output logic        resp_write_ack_o,
    output logic        fault_o,
    output logic [15:0] fault_code_o,

    // DATA hierarchy maintenance controls.
    input  logic        flush_data_l1d_i,
    input  logic        flush_data_3d_i,

    // Cache-maintenance CSR access.
    input  logic        cache_csr_valid_i,
    input  logic        cache_csr_write_i,
    input  logic        cache_csr_read_i,
    input  logic [11:0] cache_csr_addr_i,
    input  logic [63:0] cache_csr_wdata_i,

    output logic        cache_csr_resp_valid_o,
    output logic [63:0] cache_csr_rdata_o,
    output logic        cache_csr_fault_o,
    output logic [15:0] cache_csr_fault_code_o,

    // Debug: router-selected routes.
    output logic        dbg_data_route_valid_o,
    output logic        dbg_exec_route_valid_o,
    output logic        dbg_livehot_route_valid_o,
    output logic        dbg_router_fault_o,
    output logic [15:0] dbg_router_fault_code_o,

    // Debug: backing responses.
    output logic        dbg_data_resp_valid_o,
    output logic [63:0] dbg_data_resp_rdata_o,
    output logic        dbg_data_write_ack_o,

    output logic        dbg_exec_resp_valid_o,
    output logic [63:0] dbg_exec_resp_rdata_o,
    output logic        dbg_exec_write_ack_o,

    output logic        dbg_livehot_resp_valid_o,
    output logic [63:0] dbg_livehot_resp_rdata_o,
    output logic        dbg_livehot_write_ack_o
);

    // Router -> lane request wires.
    logic        data_req_valid_w;
    logic        data_req_is_read_w;
    logic        data_req_is_write_w;
    logic [63:0] data_req_paddr_w;
    logic [63:0] data_req_wdata_w;
    logic [7:0]  data_req_size_bytes_w;
    nvisc_exec_identity_t data_req_id_w;

    logic        exec_req_valid_w;
    logic        exec_req_is_read_w;
    logic        exec_req_is_write_w;
    logic [63:0] exec_req_paddr_w;
    logic [63:0] exec_req_wdata_w;
    logic [7:0]  exec_req_size_bytes_w;
    nvisc_exec_identity_t exec_req_id_w;

    logic        livehot_req_valid_w;
    logic        livehot_req_is_read_w;
    logic        livehot_req_is_write_w;
    logic [63:0] livehot_req_paddr_w;
    logic [63:0] livehot_req_wdata_w;
    logic [7:0]  livehot_req_size_bytes_w;
    nvisc_exec_identity_t livehot_req_id_w;

    logic        router_fault_w;
    logic [15:0] router_fault_code_w;

    // DATA lane response from L1D -> 3D cache -> DRAM wrapper.
    logic        data_resp_valid_w;
    logic [63:0] data_resp_rdata_w;
    logic        data_resp_write_ack_w;
    logic        data_fault_w;
    logic [15:0] data_fault_code_w;

    logic        data_l1d_hit_w;
    logic        data_l1d_miss_w;
    logic        data_l1d_fill_w;
    logic        data_3d_hit_w;
    logic        data_3d_miss_w;
    logic        data_3d_fill_w;
    logic        data_3d_store_w;
    logic        data_dram_busy_w;

    logic        cache_csr_flush_l1d_w;
    logic        cache_csr_flush_3d_w;
    logic        cache_csr_flush_hierarchy_w;
    logic        effective_flush_data_l1d_w;
    logic        effective_flush_data_3d_w;

    assign effective_flush_data_l1d_w = flush_data_l1d_i | cache_csr_flush_l1d_w | cache_csr_flush_hierarchy_w;
    assign effective_flush_data_3d_w  = flush_data_3d_i  | cache_csr_flush_3d_w  | cache_csr_flush_hierarchy_w;

    // EXECMEM response.
    logic        exec_resp_valid_w;
    logic [63:0] exec_resp_rdata_w;
    logic        exec_resp_write_ack_w;
    logic        exec_fault_w;
    logic [15:0] exec_fault_code_w;

    // LIVEHOT response.
    logic        livehot_resp_valid_w;
    logic [63:0] livehot_resp_rdata_w;
    logic        livehot_resp_write_ack_w;
    logic        livehot_fault_w;
    logic [15:0] livehot_fault_code_w;

    nvisc_mem_domain_e pending_domain_q;

    nvisc_memory_domain_router u_router (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(req_valid_i),
        .req_is_read_i(req_is_read_i),
        .req_is_write_i(req_is_write_i),
        .req_paddr_i(req_paddr_i),
        .req_wdata_i(req_wdata_i),
        .req_size_bytes_i(req_size_bytes_i),
        .req_mem_domain_i(req_mem_domain_i),
        .req_id_i(req_id_i),

        .data_req_valid_o(data_req_valid_w),
        .data_req_is_read_o(data_req_is_read_w),
        .data_req_is_write_o(data_req_is_write_w),
        .data_req_paddr_o(data_req_paddr_w),
        .data_req_wdata_o(data_req_wdata_w),
        .data_req_size_bytes_o(data_req_size_bytes_w),
        .data_req_id_o(data_req_id_w),

        .exec_req_valid_o(exec_req_valid_w),
        .exec_req_is_read_o(exec_req_is_read_w),
        .exec_req_is_write_o(exec_req_is_write_w),
        .exec_req_paddr_o(exec_req_paddr_w),
        .exec_req_wdata_o(exec_req_wdata_w),
        .exec_req_size_bytes_o(exec_req_size_bytes_w),
        .exec_req_id_o(exec_req_id_w),

        .livehot_req_valid_o(livehot_req_valid_w),
        .livehot_req_is_read_o(livehot_req_is_read_w),
        .livehot_req_is_write_o(livehot_req_is_write_w),
        .livehot_req_paddr_o(livehot_req_paddr_w),
        .livehot_req_wdata_o(livehot_req_wdata_w),
        .livehot_req_size_bytes_o(livehot_req_size_bytes_w),
        .livehot_req_id_o(livehot_req_id_w),

        .router_fault_o(router_fault_w),
        .router_fault_code_o(router_fault_code_w),

        .dbg_selected_domain_o(),
        .dbg_routed_o()
    );

    nvisc_cache_maintenance_csr u_cache_csr (
        .clk(clk),
        .rst_n(rst_n),

        .csr_valid_i(cache_csr_valid_i),
        .csr_write_i(cache_csr_write_i),
        .csr_read_i(cache_csr_read_i),
        .csr_addr_i(cache_csr_addr_i),
        .csr_wdata_i(cache_csr_wdata_i),

        .csr_resp_valid_o(cache_csr_resp_valid_o),
        .csr_rdata_o(cache_csr_rdata_o),
        .csr_fault_o(cache_csr_fault_o),
        .csr_fault_code_o(cache_csr_fault_code_o),

        .flush_l1d_o(cache_csr_flush_l1d_w),
        .flush_3d_o(cache_csr_flush_3d_w),
        .flush_data_hierarchy_o(cache_csr_flush_hierarchy_w),

        .dbg_status_o()
    );

    tb_nvisc_data_lane_3d_dram u_data_lane (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(data_req_valid_w),
        .req_is_read_i(data_req_is_read_w),
        .req_is_write_i(data_req_is_write_w),
        .req_paddr_i(data_req_paddr_w),
        .req_wdata_i(data_req_wdata_w),
        .req_size_bytes_i(data_req_size_bytes_w),
        .req_id_i(data_req_id_w),

        .resp_valid_o(data_resp_valid_w),
        .resp_rdata_o(data_resp_rdata_w),
        .resp_write_ack_o(data_resp_write_ack_w),

        .fault_o(data_fault_w),
        .fault_code_o(data_fault_code_w),

        .flush_l1d_i(effective_flush_data_l1d_w),

        .flush_3d_i(effective_flush_data_3d_w),

        .dbg_l1d_hit_o(data_l1d_hit_w),
        .dbg_l1d_miss_o(data_l1d_miss_w),
        .dbg_l1d_fill_o(data_l1d_fill_w),

        .dbg_3d_hit_o(data_3d_hit_w),
        .dbg_3d_miss_o(data_3d_miss_w),
        .dbg_3d_fill_o(data_3d_fill_w),
        .dbg_3d_store_o(data_3d_store_w),

        .dbg_dram_busy_o(data_dram_busy_w)
    );


    nvisc_execmem_controller_stub #(
        .MEM_WORDS(256),
        .BASE_ADDR(64'h0000_0000_0000_2000)
    ) u_execmem (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(exec_req_valid_w),
        .req_is_read_i(exec_req_is_read_w),
        .req_is_write_i(exec_req_is_write_w),
        .req_paddr_i(exec_req_paddr_w),
        .req_wdata_i(exec_req_wdata_w),
        .req_size_bytes_i(exec_req_size_bytes_w),
        .req_id_i(exec_req_id_w),

        .resp_valid_o(exec_resp_valid_w),
        .resp_rdata_o(exec_resp_rdata_w),
        .resp_write_ack_o(exec_resp_write_ack_w),

        .fault_o(exec_fault_w),
        .fault_code_o(exec_fault_code_w),

        .dbg_addr_o(),
        .dbg_wdata_o(),
        .dbg_rdata_o(),
        .dbg_write_seen_o(),
        .dbg_read_seen_o()
    );

    nvisc_livehot_controller_stub #(
        .MEM_WORDS(256),
        .BASE_ADDR(64'h0000_0000_0000_3000)
    ) u_livehot (
        .clk(clk),
        .rst_n(rst_n),

        .req_valid_i(livehot_req_valid_w),
        .req_is_read_i(livehot_req_is_read_w),
        .req_is_write_i(livehot_req_is_write_w),
        .req_paddr_i(livehot_req_paddr_w),
        .req_wdata_i(livehot_req_wdata_w),
        .req_size_bytes_i(livehot_req_size_bytes_w),
        .req_id_i(livehot_req_id_w),

        .resp_valid_o(livehot_resp_valid_w),
        .resp_rdata_o(livehot_resp_rdata_w),
        .resp_write_ack_o(livehot_resp_write_ack_w),

        .fault_o(livehot_fault_w),
        .fault_code_o(livehot_fault_code_w),

        .dbg_addr_o(),
        .dbg_wdata_o(),
        .dbg_rdata_o(),
        .dbg_write_seen_o(),
        .dbg_read_seen_o()
    );

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pending_domain_q <= NV_MEM_DATA;
        end else begin
            // Keep the selected domain stable until the next request.
            // Do not reset it in the same cycle a response arrives, or the
            // response mux can select the DATA lane while EXEC/LIVEHOT pulses.
            if (req_valid_i) begin
                pending_domain_q <= req_mem_domain_i;
            end
        end
    end

    always_comb begin
        resp_valid_o     = 1'b0;
        resp_rdata_o     = 64'd0;
        resp_write_ack_o = 1'b0;
        fault_o          = 1'b0;
        fault_code_o     = 16'd0;

        if (router_fault_w) begin
            fault_o      = 1'b1;
            fault_code_o = router_fault_code_w;
        end else begin
            unique case (pending_domain_q)
                NV_MEM_DATA: begin
                    resp_valid_o     = data_resp_valid_w;
                    resp_rdata_o     = data_resp_rdata_w;
                    resp_write_ack_o = data_resp_write_ack_w;
                    fault_o          = data_fault_w;
                    fault_code_o     = data_fault_code_w;
                end

                NV_MEM_EXECUTION: begin
                    resp_valid_o     = exec_resp_valid_w;
                    resp_rdata_o     = exec_resp_rdata_w;
                    resp_write_ack_o = exec_resp_write_ack_w;
                    fault_o          = exec_fault_w;
                    fault_code_o     = exec_fault_code_w;
                end

                NV_MEM_LIVE_HOT: begin
                    resp_valid_o     = livehot_resp_valid_w;
                    resp_rdata_o     = livehot_resp_rdata_w;
                    resp_write_ack_o = livehot_resp_write_ack_w;
                    fault_o          = livehot_fault_w;
                    fault_code_o     = livehot_fault_code_w;
                end

                default: begin
                    fault_o      = 1'b1;
                    fault_code_o = 16'h0801;
                end
            endcase
        end
    end

    assign dbg_data_route_valid_o      = data_req_valid_w;
    assign dbg_exec_route_valid_o      = exec_req_valid_w;
    assign dbg_livehot_route_valid_o   = livehot_req_valid_w;
    assign dbg_router_fault_o          = router_fault_w;
    assign dbg_router_fault_code_o     = router_fault_code_w;

    assign dbg_data_resp_valid_o       = data_resp_valid_w;
    assign dbg_data_resp_rdata_o       = data_resp_rdata_w;
    assign dbg_data_write_ack_o        = data_resp_write_ack_w;

    assign dbg_exec_resp_valid_o       = exec_resp_valid_w;
    assign dbg_exec_resp_rdata_o       = exec_resp_rdata_w;
    assign dbg_exec_write_ack_o        = exec_resp_write_ack_w;

    assign dbg_livehot_resp_valid_o    = livehot_resp_valid_w;
    assign dbg_livehot_resp_rdata_o    = livehot_resp_rdata_w;
    assign dbg_livehot_write_ack_o     = livehot_resp_write_ack_w;

endmodule
