`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_l1d_cache_stub #(
    parameter int LINES = 16
)(
    input  logic clk,
    input  logic rst_n,

    input  logic        flush_i,

    // Core-side translated memory request.
    input  logic        core_req_valid_i,
    input  logic        core_req_is_read_i,
    input  logic        core_req_is_write_i,
    input  logic [63:0] core_req_paddr_i,
    input  logic [63:0] core_req_wdata_i,
    input  logic [7:0]  core_req_size_bytes_i,
    input  nvisc_mem_domain_e core_req_mem_domain_i,
    input  nvisc_exec_identity_t core_req_id_i,

    // Core-side response.
    output logic        core_resp_valid_o,
    output logic [63:0] core_resp_rdata_o,
    output logic        core_resp_write_ack_o,
    output logic        core_fault_o,
    output logic [15:0] core_fault_code_o,

    // Backing memory request.
    output logic        mem_req_valid_o,
    output logic        mem_req_is_read_o,
    output logic        mem_req_is_write_o,
    output logic [63:0] mem_req_paddr_o,
    output logic [63:0] mem_req_wdata_o,
    output logic [7:0]  mem_req_size_bytes_o,
    output nvisc_mem_domain_e mem_req_mem_domain_o,
    output nvisc_exec_identity_t mem_req_id_o,

    // Backing memory response.
    input  logic        mem_resp_valid_i,
    input  logic [63:0] mem_resp_rdata_i,
    input  logic        mem_resp_write_ack_i,
    input  logic        mem_fault_i,
    input  logic [15:0] mem_fault_code_i,

    // Debug.
    output logic        dbg_hit_o,
    output logic        dbg_miss_o,
    output logic        dbg_fill_o,
    output logic [63:0] dbg_cached_data_o
);

    localparam int INDEX_W = $clog2(LINES);
    localparam int OFFSET_BITS = 3;

    typedef enum logic [1:0] {
        L1D_IDLE,
        L1D_WAIT_FILL
    } l1d_state_e;

    l1d_state_e state_q;

    logic [LINES-1:0] valid_q;
    logic [63:0]      tag_q  [LINES];
    logic [63:0]      data_q [LINES];

    logic [INDEX_W-1:0] index_c;
    logic [63:0]        tag_c;
    logic               hit_c;

    logic [INDEX_W-1:0] miss_index_q;
    logic [63:0]        miss_tag_q;
    logic [63:0]        miss_paddr_q;
    logic [7:0]         miss_size_q;
    nvisc_mem_domain_e  miss_domain_q;
    nvisc_exec_identity_t miss_id_q;

    logic flush_q;

    integer i;

    assign index_c = core_req_paddr_i[OFFSET_BITS + INDEX_W - 1:OFFSET_BITS];
    assign tag_c   = core_req_paddr_i >> (OFFSET_BITS + INDEX_W);
    assign hit_c   = core_req_valid_i && !flush_i && !flush_q &&
                     core_req_is_read_i &&
                     valid_q[index_c] &&
                     (tag_q[index_c] == tag_c);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state_q <= L1D_IDLE;

            valid_q <= '0;
            flush_q <= 1'b0;
            for (i = 0; i < LINES; i = i + 1) begin
                tag_q[i]  <= 64'd0;
                data_q[i] <= 64'd0;
            end

            core_resp_valid_o     <= 1'b0;
            core_resp_rdata_o     <= 64'd0;
            core_resp_write_ack_o <= 1'b0;
            core_fault_o          <= 1'b0;
            core_fault_code_o     <= 16'd0;

            mem_req_valid_o      <= 1'b0;
            mem_req_is_read_o    <= 1'b0;
            mem_req_is_write_o   <= 1'b0;
            mem_req_paddr_o      <= 64'd0;
            mem_req_wdata_o      <= 64'd0;
            mem_req_size_bytes_o <= 8'd0;
            mem_req_mem_domain_o <= NV_MEM_DATA;
            mem_req_id_o         <= '0;

            miss_index_q <= '0;
            miss_tag_q   <= 64'd0;
            miss_paddr_q <= 64'd0;
            miss_size_q  <= 8'd0;
            miss_domain_q <= NV_MEM_DATA;
            miss_id_q     <= '0;

            dbg_hit_o         <= 1'b0;
            dbg_miss_o        <= 1'b0;
            dbg_fill_o        <= 1'b0;

            dbg_cached_data_o <= 64'd0;
        end else begin
            core_resp_valid_o     <= 1'b0;
            core_resp_rdata_o     <= 64'd0;
            core_resp_write_ack_o <= 1'b0;
            core_fault_o          <= 1'b0;
            core_fault_code_o     <= 16'd0;

            mem_req_valid_o      <= 1'b0;
            mem_req_is_read_o    <= 1'b0;
            mem_req_is_write_o   <= 1'b0;
            mem_req_paddr_o      <= 64'd0;
            mem_req_wdata_o      <= 64'd0;
            mem_req_size_bytes_o <= 8'd0;
            mem_req_mem_domain_o <= NV_MEM_DATA;
            mem_req_id_o         <= '0;

            dbg_hit_o  <= 1'b0;
            dbg_miss_o <= 1'b0;
            dbg_fill_o <= 1'b0;
            flush_q           <= flush_i;

            if (flush_i) begin
                valid_q <= '0;
                for (i = 0; i < LINES; i = i + 1) begin
                    tag_q[i]  <= 64'd0;
                    data_q[i] <= 64'd0;
                end
                state_q <= L1D_IDLE;
                miss_index_q <= '0;
                miss_tag_q <= '0;
                miss_paddr_q <= 64'd0;
                miss_size_q <= 8'd0;
                miss_domain_q <= NV_MEM_DATA;
                miss_id_q <= '0;
            end

            unique case (state_q)
                L1D_IDLE: begin
                    if (core_req_valid_i && !flush_i && !flush_q) begin
                        if (core_req_size_bytes_i != 8'd8) begin
                            core_fault_o      <= 1'b1;
                            core_fault_code_o <= 16'h0501;
                        end else if (core_req_is_read_i && core_req_is_write_i) begin
                            core_fault_o      <= 1'b1;
                            core_fault_code_o <= 16'h0502;
                        end else if (core_req_is_read_i) begin
                            if (hit_c) begin
                                core_resp_valid_o <= 1'b1;
                                core_resp_rdata_o <= data_q[index_c];
                                dbg_hit_o         <= 1'b1;
                                dbg_cached_data_o <= data_q[index_c];
                            end else begin
                                mem_req_valid_o      <= 1'b1;
                                mem_req_is_read_o    <= 1'b1;
                                mem_req_is_write_o   <= 1'b0;
                                mem_req_paddr_o      <= core_req_paddr_i;
                                mem_req_wdata_o      <= 64'd0;
                                mem_req_size_bytes_o <= core_req_size_bytes_i;
                                mem_req_mem_domain_o <= core_req_mem_domain_i;
                                mem_req_id_o         <= core_req_id_i;

                                miss_index_q  <= index_c;
                                miss_tag_q    <= tag_c;
                                miss_paddr_q  <= core_req_paddr_i;
                                miss_size_q   <= core_req_size_bytes_i;
                                miss_domain_q <= core_req_mem_domain_i;
                                miss_id_q     <= core_req_id_i;

                                dbg_miss_o <= 1'b1;
                                state_q    <= L1D_WAIT_FILL;
                            end
                        end else if (core_req_is_write_i) begin
                            // Write-through, write-allocate update if line already present.
                            if (valid_q[index_c] && tag_q[index_c] == tag_c) begin
                                data_q[index_c] <= core_req_wdata_i;
                            end

                            mem_req_valid_o      <= 1'b1;
                            mem_req_is_read_o    <= 1'b0;
                            mem_req_is_write_o   <= 1'b1;
                            mem_req_paddr_o      <= core_req_paddr_i;
                            mem_req_wdata_o      <= core_req_wdata_i;
                            mem_req_size_bytes_o <= core_req_size_bytes_i;
                            mem_req_mem_domain_o <= core_req_mem_domain_i;
                            mem_req_id_o         <= core_req_id_i;
                        end else begin
                            core_fault_o      <= 1'b1;
                            core_fault_code_o <= 16'h0503;
                        end
                    end
                end

                L1D_WAIT_FILL: begin
                    if (mem_fault_i) begin
                        core_fault_o      <= 1'b1;
                        core_fault_code_o <= mem_fault_code_i;
                        state_q           <= L1D_IDLE;
                    end else if (mem_resp_valid_i) begin
                        valid_q[miss_index_q] <= 1'b1;
                        tag_q[miss_index_q]   <= miss_tag_q;
                        data_q[miss_index_q]  <= mem_resp_rdata_i;

                        core_resp_valid_o <= 1'b1;
                        core_resp_rdata_o <= mem_resp_rdata_i;

                        dbg_fill_o        <= 1'b1;
                        dbg_cached_data_o <= mem_resp_rdata_i;

                        state_q <= L1D_IDLE;
                    end
                end

                default: begin
                    state_q <= L1D_IDLE;
                end
            endcase

            if (mem_fault_i && state_q == L1D_IDLE) begin
                core_fault_o      <= 1'b1;
                core_fault_code_o <= mem_fault_code_i;
            end

            if (mem_resp_write_ack_i) begin
                core_resp_valid_o     <= 1'b1;
                core_resp_write_ack_o <= 1'b1;
            end
        end
    end

endmodule
