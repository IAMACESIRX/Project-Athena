`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_interrupt_timer_stub (
    input  logic clk,
    input  logic rst_n,

    // Control.
    input  logic        global_irq_enable_i,
    input  logic        timer_enable_i,
    input  logic [63:0] timer_compare_i,
    input  logic [63:0] irq_vector_base_i,

    // External interrupt source.
    input  logic        external_irq_i,

    // Acknowledge/clear pending interrupt state.
    input  logic        irq_ack_i,

    // Status / interrupt output.
    output logic [63:0] cycle_count_o,
    output logic        timer_pending_o,
    output logic        external_pending_o,

    output logic        irq_pending_o,
    output logic        irq_taken_o,
    output logic [63:0] irq_vector_o,
    output logic [15:0] irq_code_o,

    // Debug.
    output logic        dbg_timer_fire_o,
    output logic        dbg_external_fire_o
);

    localparam logic [15:0] NV_IRQ_CODE_TIMER    = 16'h1001;
    localparam logic [15:0] NV_IRQ_CODE_EXTERNAL = 16'h1002;

    logic [63:0] cycle_count_q;
    logic        timer_pending_q;
    logic        external_pending_q;

    logic timer_fire_c;

    assign timer_fire_c = timer_enable_i && (cycle_count_q >= timer_compare_i);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cycle_count_q      <= 64'd0;
            timer_pending_q    <= 1'b0;
            external_pending_q <= 1'b0;

            dbg_timer_fire_o    <= 1'b0;
            dbg_external_fire_o <= 1'b0;
        end else begin
            cycle_count_q <= cycle_count_q + 64'd1;

            dbg_timer_fire_o    <= 1'b0;
            dbg_external_fire_o <= 1'b0;

            if (irq_ack_i) begin
                timer_pending_q    <= 1'b0;
                external_pending_q <= 1'b0;
            end else begin
                if (timer_fire_c) begin
                    timer_pending_q <= 1'b1;
                    dbg_timer_fire_o <= 1'b1;
                end

                if (external_irq_i) begin
                    external_pending_q <= 1'b1;
                    dbg_external_fire_o <= 1'b1;
                end
            end
        end
    end

    assign cycle_count_o      = cycle_count_q;
    assign timer_pending_o    = timer_pending_q;
    assign external_pending_o = external_pending_q;

    assign irq_pending_o = timer_pending_q || external_pending_q;
    assign irq_taken_o   = global_irq_enable_i && irq_pending_o;

    // Priority: external interrupt beats timer interrupt.
    always_comb begin
        irq_vector_o = irq_vector_base_i;
        irq_code_o   = 16'd0;

        if (external_pending_q) begin
            irq_vector_o = irq_vector_base_i + 64'h20;
            irq_code_o   = NV_IRQ_CODE_EXTERNAL;
        end else if (timer_pending_q) begin
            irq_vector_o = irq_vector_base_i + 64'h10;
            irq_code_o   = NV_IRQ_CODE_TIMER;
        end
    end

endmodule
