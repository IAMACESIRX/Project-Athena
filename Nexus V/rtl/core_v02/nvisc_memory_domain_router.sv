`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_memory_domain_router (
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

    // DATA lane output.
    output logic        data_req_valid_o,
    output logic        data_req_is_read_o,
    output logic        data_req_is_write_o,
    output logic [63:0] data_req_paddr_o,
    output logic [63:0] data_req_wdata_o,
    output logic [7:0]  data_req_size_bytes_o,
    output nvisc_exec_identity_t data_req_id_o,

    // EXECUTION lane output.
    output logic        exec_req_valid_o,
    output logic        exec_req_is_read_o,
    output logic        exec_req_is_write_o,
    output logic [63:0] exec_req_paddr_o,
    output logic [63:0] exec_req_wdata_o,
    output logic [7:0]  exec_req_size_bytes_o,
    output nvisc_exec_identity_t exec_req_id_o,

    // LIVE/HOT lane output.
    output logic        livehot_req_valid_o,
    output logic        livehot_req_is_read_o,
    output logic        livehot_req_is_write_o,
    output logic [63:0] livehot_req_paddr_o,
    output logic [63:0] livehot_req_wdata_o,
    output logic [7:0]  livehot_req_size_bytes_o,
    output nvisc_exec_identity_t livehot_req_id_o,

    // Router fault for unsupported/invalid domains.
    output logic        router_fault_o,
    output logic [15:0] router_fault_code_o,

    // Debug.
    output logic [2:0]  dbg_selected_domain_o,
    output logic        dbg_routed_o
);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            data_req_valid_o         <= 1'b0;
            data_req_is_read_o       <= 1'b0;
            data_req_is_write_o      <= 1'b0;
            data_req_paddr_o         <= 64'd0;
            data_req_wdata_o         <= 64'd0;
            data_req_size_bytes_o    <= 8'd0;
            data_req_id_o            <= '0;

            exec_req_valid_o         <= 1'b0;
            exec_req_is_read_o       <= 1'b0;
            exec_req_is_write_o      <= 1'b0;
            exec_req_paddr_o         <= 64'd0;
            exec_req_wdata_o         <= 64'd0;
            exec_req_size_bytes_o    <= 8'd0;
            exec_req_id_o            <= '0;

            livehot_req_valid_o      <= 1'b0;
            livehot_req_is_read_o    <= 1'b0;
            livehot_req_is_write_o   <= 1'b0;
            livehot_req_paddr_o      <= 64'd0;
            livehot_req_wdata_o      <= 64'd0;
            livehot_req_size_bytes_o <= 8'd0;
            livehot_req_id_o         <= '0;

            router_fault_o           <= 1'b0;
            router_fault_code_o      <= 16'd0;

            dbg_selected_domain_o    <= 3'd0;
            dbg_routed_o             <= 1'b0;
        end else begin
            data_req_valid_o         <= 1'b0;
            data_req_is_read_o       <= 1'b0;
            data_req_is_write_o      <= 1'b0;
            data_req_paddr_o         <= 64'd0;
            data_req_wdata_o         <= 64'd0;
            data_req_size_bytes_o    <= 8'd0;
            data_req_id_o            <= '0;

            exec_req_valid_o         <= 1'b0;
            exec_req_is_read_o       <= 1'b0;
            exec_req_is_write_o      <= 1'b0;
            exec_req_paddr_o         <= 64'd0;
            exec_req_wdata_o         <= 64'd0;
            exec_req_size_bytes_o    <= 8'd0;
            exec_req_id_o            <= '0;

            livehot_req_valid_o      <= 1'b0;
            livehot_req_is_read_o    <= 1'b0;
            livehot_req_is_write_o   <= 1'b0;
            livehot_req_paddr_o      <= 64'd0;
            livehot_req_wdata_o      <= 64'd0;
            livehot_req_size_bytes_o <= 8'd0;
            livehot_req_id_o         <= '0;

            router_fault_o           <= 1'b0;
            router_fault_code_o      <= 16'd0;

            dbg_selected_domain_o    <= 3'd0;
            dbg_routed_o             <= 1'b0;

            if (req_valid_i) begin
                unique case (req_mem_domain_i)
                    NV_MEM_DATA: begin
                        data_req_valid_o      <= 1'b1;
                        data_req_is_read_o    <= req_is_read_i;
                        data_req_is_write_o   <= req_is_write_i;
                        data_req_paddr_o      <= req_paddr_i;
                        data_req_wdata_o      <= req_wdata_i;
                        data_req_size_bytes_o <= req_size_bytes_i;
                        data_req_id_o         <= req_id_i;

                        dbg_selected_domain_o <= 3'd1;
                        dbg_routed_o          <= 1'b1;
                    end

                    NV_MEM_EXECUTION: begin
                        exec_req_valid_o      <= 1'b1;
                        exec_req_is_read_o    <= req_is_read_i;
                        exec_req_is_write_o   <= req_is_write_i;
                        exec_req_paddr_o      <= req_paddr_i;
                        exec_req_wdata_o      <= req_wdata_i;
                        exec_req_size_bytes_o <= req_size_bytes_i;
                        exec_req_id_o         <= req_id_i;

                        dbg_selected_domain_o <= 3'd2;
                        dbg_routed_o          <= 1'b1;
                    end

                    NV_MEM_LIVE_HOT: begin
                        livehot_req_valid_o      <= 1'b1;
                        livehot_req_is_read_o    <= req_is_read_i;
                        livehot_req_is_write_o   <= req_is_write_i;
                        livehot_req_paddr_o      <= req_paddr_i;
                        livehot_req_wdata_o      <= req_wdata_i;
                        livehot_req_size_bytes_o <= req_size_bytes_i;
                        livehot_req_id_o         <= req_id_i;

                        dbg_selected_domain_o <= 3'd3;
                        dbg_routed_o          <= 1'b1;
                    end

                    default: begin
                        router_fault_o      <= 1'b1;
                        router_fault_code_o <= 16'h0801;
                    end
                endcase
            end
        end
    end

endmodule
