`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_instruction_fetch_unit (
    input  logic clk,
    input  logic rst_n,

    input  logic stall_i,
    input  logic flush_i,

    input  logic [63:0] pc_i,
    input  logic        pc_valid_i,
    input  nvisc_exec_identity_t id_i,

    // Instruction-memory / NexusIBus request.
    output logic        imem_req_valid_o,
    output logic [63:0] imem_req_addr_o,
    output nvisc_exec_identity_t imem_req_id_o,

    // Instruction-memory response.
    input  logic        imem_resp_valid_i,
    input  logic [31:0] imem_resp_instr_i,
    input  logic        imem_resp_fault_i,
    input  logic [15:0] imem_resp_fault_code_i,

    // IF/ID fetch packet output.
    output nvisc_fetch_packet_t fetch_packet_o,
    output logic        fetch_fault_o,
    output logic [15:0] fetch_fault_code_o,

    // C++/Verilator debug-friendly mirrors.
    output logic        dbg_fetch_valid_o,
    output logic [63:0] dbg_fetch_pc_o,
    output logic [31:0] dbg_fetch_instr_o
);

    nvisc_fetch_packet_t fetch_q;
    logic fault_q;
    logic [15:0] fault_code_q;

    assign imem_req_valid_o = pc_valid_i && !stall_i && !flush_i;
    assign imem_req_addr_o  = pc_i;
    assign imem_req_id_o    = id_i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            fetch_q      <= '0;
            fault_q      <= 1'b0;
            fault_code_q <= 16'd0;
        end else begin
            if (flush_i) begin
                fetch_q      <= '0;
                fault_q      <= 1'b0;
                fault_code_q <= 16'd0;
            end else if (!stall_i) begin
                if (imem_resp_valid_i) begin
                    fetch_q.valid <= !imem_resp_fault_i;
                    fetch_q.pc    <= pc_i;
                    fetch_q.instr <= imem_resp_instr_i;
                    fetch_q.id    <= id_i;

                    fault_q      <= imem_resp_fault_i;
                    fault_code_q <= imem_resp_fault_code_i;
                end else begin
                    fetch_q.valid <= 1'b0;
                    fault_q       <= 1'b0;
                    fault_code_q  <= 16'd0;
                end
            end
        end
    end

    assign fetch_packet_o     = fetch_q;
    assign fetch_fault_o      = fault_q;
    assign fetch_fault_code_o = fault_code_q;

    assign dbg_fetch_valid_o  = fetch_q.valid;
    assign dbg_fetch_pc_o     = fetch_q.pc;
    assign dbg_fetch_instr_o  = fetch_q.instr;

endmodule
