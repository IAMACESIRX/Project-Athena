`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_irq_csr_bridge (
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

    // Status from IRQ/timer.
    input  logic [63:0] cycle_count_i,
    input  logic        irq_pending_i,
    input  logic        irq_taken_i,
    input  logic [63:0] irq_vector_i,
    input  logic [15:0] irq_code_i,

    // Control to IRQ/timer.
    output logic        global_irq_enable_o,
    output logic        timer_enable_o,
    output logic [63:0] timer_compare_o,
    output logic [63:0] irq_vector_base_o,
    output logic        irq_ack_o,

    // Debug.
    output logic        dbg_csr_write_o,
    output logic        dbg_csr_read_o
);

    localparam logic [11:0] CSR_IRQ_GLOBAL_ENABLE = 12'h300;
    localparam logic [11:0] CSR_TIMER_ENABLE      = 12'h304;
    localparam logic [11:0] CSR_TIMER_COMPARE_LO  = 12'h308;
    localparam logic [11:0] CSR_TIMER_COMPARE_HI  = 12'h30C;
    localparam logic [11:0] CSR_IRQ_VECTOR_LO     = 12'h310;
    localparam logic [11:0] CSR_IRQ_VECTOR_HI     = 12'h314;
    localparam logic [11:0] CSR_IRQ_ACK           = 12'h318;

    localparam logic [11:0] CSR_CYCLE_COUNT_LO    = 12'h320;
    localparam logic [11:0] CSR_CYCLE_COUNT_HI    = 12'h324;
    localparam logic [11:0] CSR_IRQ_PENDING       = 12'h328;
    localparam logic [11:0] CSR_IRQ_CODE          = 12'h32C;
    localparam logic [11:0] CSR_IRQ_ACTIVE_VECTOR_LO = 12'h330;
    localparam logic [11:0] CSR_IRQ_ACTIVE_VECTOR_HI = 12'h334;

    logic        global_irq_enable_q;
    logic        timer_enable_q;
    logic [63:0] timer_compare_q;
    logic [63:0] irq_vector_base_q;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            global_irq_enable_q <= 1'b0;
            timer_enable_q      <= 1'b0;
            timer_compare_q     <= 64'hFFFF_FFFF_FFFF_FFFF;
            irq_vector_base_q   <= 64'h0000_0000_8000_0000;

            csr_resp_valid_o    <= 1'b0;
            csr_rdata_o         <= 64'd0;
            csr_fault_o         <= 1'b0;
            csr_fault_code_o    <= 16'd0;

            irq_ack_o           <= 1'b0;

            dbg_csr_write_o     <= 1'b0;
            dbg_csr_read_o      <= 1'b0;
        end else begin
            csr_resp_valid_o <= 1'b0;
            csr_rdata_o      <= 64'd0;
            csr_fault_o      <= 1'b0;
            csr_fault_code_o <= 16'd0;

            irq_ack_o        <= 1'b0;

            dbg_csr_write_o  <= 1'b0;
            dbg_csr_read_o   <= 1'b0;

            if (csr_valid_i) begin
                csr_resp_valid_o <= 1'b1;

                if (csr_write_i && csr_read_i) begin
                    csr_fault_o      <= 1'b1;
                    csr_fault_code_o <= 16'h0701;
                end else if (csr_write_i) begin
                    dbg_csr_write_o <= 1'b1;

                    unique case (csr_addr_i)
                        CSR_IRQ_GLOBAL_ENABLE: begin
                            global_irq_enable_q <= csr_wdata_i[0];
                        end

                        CSR_TIMER_ENABLE: begin
                            timer_enable_q <= csr_wdata_i[0];
                        end

                        CSR_TIMER_COMPARE_LO: begin
                            timer_compare_q[31:0] <= csr_wdata_i[31:0];
                        end

                        CSR_TIMER_COMPARE_HI: begin
                            timer_compare_q[63:32] <= csr_wdata_i[31:0];
                        end

                        CSR_IRQ_VECTOR_LO: begin
                            irq_vector_base_q[31:0] <= csr_wdata_i[31:0];
                        end

                        CSR_IRQ_VECTOR_HI: begin
                            irq_vector_base_q[63:32] <= csr_wdata_i[31:0];
                        end

                        CSR_IRQ_ACK: begin
                            irq_ack_o <= csr_wdata_i[0];
                        end

                        default: begin
                            csr_fault_o      <= 1'b1;
                            csr_fault_code_o <= 16'h0702;
                        end
                    endcase
                end else if (csr_read_i) begin
                    dbg_csr_read_o <= 1'b1;

                    unique case (csr_addr_i)
                        CSR_IRQ_GLOBAL_ENABLE: begin
                            csr_rdata_o <= {63'd0, global_irq_enable_q};
                        end

                        CSR_TIMER_ENABLE: begin
                            csr_rdata_o <= {63'd0, timer_enable_q};
                        end

                        CSR_TIMER_COMPARE_LO: begin
                            csr_rdata_o <= {32'd0, timer_compare_q[31:0]};
                        end

                        CSR_TIMER_COMPARE_HI: begin
                            csr_rdata_o <= {32'd0, timer_compare_q[63:32]};
                        end

                        CSR_IRQ_VECTOR_LO: begin
                            csr_rdata_o <= {32'd0, irq_vector_base_q[31:0]};
                        end

                        CSR_IRQ_VECTOR_HI: begin
                            csr_rdata_o <= {32'd0, irq_vector_base_q[63:32]};
                        end

                        CSR_CYCLE_COUNT_LO: begin
                            csr_rdata_o <= {32'd0, cycle_count_i[31:0]};
                        end

                        CSR_CYCLE_COUNT_HI: begin
                            csr_rdata_o <= {32'd0, cycle_count_i[63:32]};
                        end

                        CSR_IRQ_PENDING: begin
                            csr_rdata_o <= {62'd0, irq_taken_i, irq_pending_i};
                        end

                        CSR_IRQ_CODE: begin
                            csr_rdata_o <= {48'd0, irq_code_i};
                        end

                        CSR_IRQ_ACTIVE_VECTOR_LO: begin
                            csr_rdata_o <= {32'd0, irq_vector_i[31:0]};
                        end

                        CSR_IRQ_ACTIVE_VECTOR_HI: begin
                            csr_rdata_o <= {32'd0, irq_vector_i[63:32]};
                        end

                        default: begin
                            csr_fault_o      <= 1'b1;
                            csr_fault_code_o <= 16'h0702;
                        end
                    endcase
                end else begin
                    csr_fault_o      <= 1'b1;
                    csr_fault_code_o <= 16'h0703;
                end
            end
        end
    end

    assign global_irq_enable_o = global_irq_enable_q;
    assign timer_enable_o      = timer_enable_q;
    assign timer_compare_o     = timer_compare_q;
    assign irq_vector_base_o   = irq_vector_base_q;

endmodule
