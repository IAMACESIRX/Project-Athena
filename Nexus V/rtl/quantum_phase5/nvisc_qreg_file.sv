`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_qreg_file #(
    parameter int QREG_COUNT_P = QREG_COUNT,
    parameter int QREG_IDX_W = $clog2(QREG_COUNT_P)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic wr_req_i,
    input  logic [QREG_IDX_W-1:0] wr_idx_i,
    input  nvisc_qreg_meta_t wr_meta_i,

    input  logic rd_req_i,
    input  logic [QREG_IDX_W-1:0] rd_idx_i,
    output logic rd_valid_o,
    output nvisc_qreg_meta_t rd_meta_o,

    input  logic alloc_req_i,
    input  logic [31:0] branch_id_i,
    input  logic [31:0] state_id_i,
    input  nvisc_qmode_e qmode_i,
    output logic alloc_ready_o,
    output logic [QREG_IDX_W-1:0] alloc_idx_o,
    output nvisc_qreg_meta_t alloc_meta_o
);
    nvisc_qreg_meta_t meta [QREG_COUNT_P];
    logic found_free;
    integer i;

    always_comb begin
        found_free = 1'b0;
        alloc_idx_o = '0;
        for (i = 0; i < QREG_COUNT_P; i++) begin
            if (!found_free && !meta[i].valid) begin
                found_free = 1'b1;
                alloc_idx_o = i[QREG_IDX_W-1:0];
            end
        end
        alloc_ready_o = alloc_req_i && found_free;
        alloc_meta_o = '0;
        alloc_meta_o.valid = alloc_ready_o;
        alloc_meta_o.qreg_id = {{(32-QREG_IDX_W){1'b0}}, alloc_idx_o};
        alloc_meta_o.branch_id = branch_id_i;
        alloc_meta_o.state_id = state_id_i;
        alloc_meta_o.qmode = qmode_i;
        alloc_meta_o.num_qubits = 8'd1;
        alloc_meta_o.fidelity_score = 8'd255;
        alloc_meta_o.rollback_valid = 1'b1;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < QREG_COUNT_P; i++) meta[i] <= '0;
            rd_valid_o <= 1'b0;
            rd_meta_o <= '0;
        end else begin
            rd_valid_o <= 1'b0;
            if (alloc_ready_o) meta[alloc_idx_o] <= alloc_meta_o;
            if (wr_req_i) meta[wr_idx_i] <= wr_meta_i;
            if (rd_req_i) begin
                rd_valid_o <= 1'b1;
                rd_meta_o <= meta[rd_idx_i];
            end
        end
    end
endmodule
