`timescale 1ns / 1ps

module nvisc_cache_maintenance_csr #(
    parameter logic [11:0] CACHE_CTL_ADDR    = 12'h7D0,
    parameter logic [11:0] CACHE_STATUS_ADDR = 12'h7D1
)(
    input  logic        clk,
    input  logic        rst_n,

    input  logic        csr_valid_i,
    input  logic        csr_write_i,
    input  logic        csr_read_i,
    input  logic [11:0] csr_addr_i,
    input  logic [63:0] csr_wdata_i,

    output logic        csr_resp_valid_o,
    output logic [63:0] csr_rdata_o,

    output logic        csr_fault_o,
    output logic [15:0] csr_fault_code_o,

    output logic        flush_l1d_o,
    output logic        flush_3d_o,
    output logic        flush_data_hierarchy_o,

    output logic [63:0] dbg_status_o
);

    localparam logic [15:0] CACHE_CSR_FAULT_NONE     = 16'h0000;
    localparam logic [15:0] CACHE_CSR_FAULT_BAD_ADDR = 16'h0C80;
    localparam logic [15:0] CACHE_CSR_FAULT_BAD_OP   = 16'h0C81;

    logic [63:0] status_q;

    logic addr_ctl_c;
    logic addr_status_c;
    logic valid_addr_c;
    logic op_ok_c;

    assign addr_ctl_c    = (csr_addr_i == CACHE_CTL_ADDR);
    assign addr_status_c = (csr_addr_i == CACHE_STATUS_ADDR);
    assign valid_addr_c  = addr_ctl_c || addr_status_c;
    assign op_ok_c       = csr_write_i ^ csr_read_i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            csr_resp_valid_o       <= 1'b0;
            csr_rdata_o            <= 64'd0;
            csr_fault_o            <= 1'b0;
            csr_fault_code_o       <= CACHE_CSR_FAULT_NONE;

            flush_l1d_o            <= 1'b0;
            flush_3d_o             <= 1'b0;
            flush_data_hierarchy_o <= 1'b0;

            status_q               <= 64'd0;
        end else begin
            csr_resp_valid_o       <= 1'b0;
            csr_rdata_o            <= 64'd0;
            csr_fault_o            <= 1'b0;
            csr_fault_code_o       <= CACHE_CSR_FAULT_NONE;

            // Flush outputs are pulses.
            flush_l1d_o            <= 1'b0;
            flush_3d_o             <= 1'b0;
            flush_data_hierarchy_o <= 1'b0;

            if (csr_valid_i) begin
                if (!valid_addr_c) begin
                    csr_fault_o      <= 1'b1;
                    csr_fault_code_o <= CACHE_CSR_FAULT_BAD_ADDR;
                end else if (!op_ok_c) begin
                    csr_fault_o      <= 1'b1;
                    csr_fault_code_o <= CACHE_CSR_FAULT_BAD_OP;
                end else begin
                    csr_resp_valid_o <= 1'b1;

                    if (csr_write_i) begin
                        if (addr_ctl_c) begin
                            flush_l1d_o            <= csr_wdata_i[0] | csr_wdata_i[2];
                            flush_3d_o             <= csr_wdata_i[1] | csr_wdata_i[2];
                            flush_data_hierarchy_o <= csr_wdata_i[2];

                            status_q[0] <= csr_wdata_i[0] | csr_wdata_i[2];
                            status_q[1] <= csr_wdata_i[1] | csr_wdata_i[2];
                            status_q[2] <= csr_wdata_i[2];
                        end else begin
                            csr_fault_o        <= 1'b1;
                            csr_fault_code_o   <= CACHE_CSR_FAULT_BAD_OP;
                            csr_resp_valid_o   <= 1'b0;
                        end
                    end else if (csr_read_i) begin
                        if (addr_status_c) begin
                            csr_rdata_o <= status_q;
                        end else if (addr_ctl_c) begin
                            csr_rdata_o <= 64'd0;
                        end
                    end
                end
            end
        end
    end

    assign dbg_status_o = status_q;

endmodule
