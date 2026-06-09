`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_mem_domain_csr_bridge (
    input  logic clk,
    input  logic rst_n,

    // CSR access.
    input  logic        csr_valid_i,
    input  logic        csr_write_i,
    input  logic        csr_read_i,
    input  logic [11:0] csr_addr_i,
    input  logic [63:0] csr_wdata_i,

    output logic        csr_resp_valid_o,
    output logic [63:0] csr_rdata_o,
    output logic        csr_fault_o,
    output logic [15:0] csr_fault_code_o,

    // Normal decoder/core-selected memory domain.
    input  logic [2:0]  core_mem_domain_i,

    // Effective memory domain to memory subsystem.
    output logic        mem_domain_override_enable_o,
    output logic [2:0]  mem_domain_select_o,
    output logic [2:0]  effective_mem_domain_o,

    // Debug.
    output logic        dbg_csr_write_o,
    output logic        dbg_csr_read_o
);

    localparam logic [11:0] CSR_MEM_DOMAIN_SELECT          = 12'h340;
    localparam logic [11:0] CSR_MEM_DOMAIN_OVERRIDE_ENABLE = 12'h344;
    localparam logic [11:0] CSR_MEM_DOMAIN_STATUS          = 12'h348;

    logic [2:0] mem_domain_select_q;
    logic       mem_domain_override_enable_q;

    logic [2:0] effective_domain_c;
    logic       selected_domain_valid_c;

    assign selected_domain_valid_c =
        (csr_wdata_i[2:0] == NV_MEM_DATA) ||
        (csr_wdata_i[2:0] == NV_MEM_EXECUTION) ||
        (csr_wdata_i[2:0] == NV_MEM_LIVE_HOT);

    assign effective_domain_c =
        mem_domain_override_enable_q ? mem_domain_select_q : core_mem_domain_i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            mem_domain_select_q          <= NV_MEM_DATA;
            mem_domain_override_enable_q <= 1'b0;

            csr_resp_valid_o             <= 1'b0;
            csr_rdata_o                  <= 64'd0;
            csr_fault_o                  <= 1'b0;
            csr_fault_code_o             <= 16'd0;

            dbg_csr_write_o              <= 1'b0;
            dbg_csr_read_o               <= 1'b0;
        end else begin
            csr_resp_valid_o <= 1'b0;
            csr_rdata_o      <= 64'd0;
            csr_fault_o      <= 1'b0;
            csr_fault_code_o <= 16'd0;

            dbg_csr_write_o  <= 1'b0;
            dbg_csr_read_o   <= 1'b0;

            if (csr_valid_i) begin
                csr_resp_valid_o <= 1'b1;

                if (csr_write_i && csr_read_i) begin
                    csr_fault_o      <= 1'b1;
                    csr_fault_code_o <= 16'h0B01;
                end else if (csr_write_i) begin
                    dbg_csr_write_o <= 1'b1;

                    unique case (csr_addr_i)
                        CSR_MEM_DOMAIN_SELECT: begin
                            if (selected_domain_valid_c) begin
                                mem_domain_select_q <= csr_wdata_i[2:0];
                            end else begin
                                csr_fault_o      <= 1'b1;
                                csr_fault_code_o <= 16'h0B02;
                            end
                        end

                        CSR_MEM_DOMAIN_OVERRIDE_ENABLE: begin
                            mem_domain_override_enable_q <= csr_wdata_i[0];
                        end

                        default: begin
                            csr_fault_o      <= 1'b1;
                            csr_fault_code_o <= 16'h0B03;
                        end
                    endcase
                end else if (csr_read_i) begin
                    dbg_csr_read_o <= 1'b1;

                    unique case (csr_addr_i)
                        CSR_MEM_DOMAIN_SELECT: begin
                            csr_rdata_o <= {61'd0, mem_domain_select_q};
                        end

                        CSR_MEM_DOMAIN_OVERRIDE_ENABLE: begin
                            csr_rdata_o <= {63'd0, mem_domain_override_enable_q};
                        end

                        CSR_MEM_DOMAIN_STATUS: begin
                            csr_rdata_o <= {
                                56'd0,
                                effective_domain_c,
                                core_mem_domain_i,
                                mem_domain_override_enable_q,
                                1'b0
                            };
                        end

                        default: begin
                            csr_fault_o      <= 1'b1;
                            csr_fault_code_o <= 16'h0B03;
                        end
                    endcase
                end else begin
                    csr_fault_o      <= 1'b1;
                    csr_fault_code_o <= 16'h0B04;
                end
            end
        end
    end

    assign mem_domain_override_enable_o = mem_domain_override_enable_q;
    assign mem_domain_select_o          = mem_domain_select_q;
    assign effective_mem_domain_o       = effective_domain_c;

endmodule
