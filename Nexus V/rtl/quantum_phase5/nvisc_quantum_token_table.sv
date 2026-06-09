`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_quantum_token_table #(
    parameter int QTOKEN_COUNT_P = QTOKEN_COUNT,
    parameter int QTOKEN_IDX_W = $clog2(QTOKEN_COUNT_P)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic create_req_i,
    input  nvisc_qcollapse_reg_t collapse_i,
    input  logic [15:0] topology_epoch_i,
    input  logic [15:0] thermal_epoch_i,
    output logic create_ready_o,
    output logic [QTOKEN_IDX_W-1:0] create_idx_o,
    output nvisc_quantum_token_t create_token_o,

    input  logic audit_mark_i,
    input  logic [QTOKEN_IDX_W-1:0] audit_idx_i,

    input  logic sync_mark_i,
    input  logic [QTOKEN_IDX_W-1:0] sync_idx_i,

    input  logic rollback_invalidate_i,
    input  logic [31:0] rollback_from_state_i,

    input  logic rd_req_i,
    input  logic [QTOKEN_IDX_W-1:0] rd_idx_i,
    output logic rd_valid_o,
    output nvisc_quantum_token_t rd_token_o
);
    nvisc_quantum_token_t tokens [QTOKEN_COUNT_P];
    logic found_free;
    integer i;

    always_comb begin
        found_free = 1'b0;
        create_idx_o = '0;
        for (i = 0; i < QTOKEN_COUNT_P; i++) begin
            if (!found_free && !tokens[i].valid) begin
                found_free = 1'b1;
                create_idx_o = i[QTOKEN_IDX_W-1:0];
            end
        end
        create_ready_o = create_req_i && found_free;
        create_token_o = '0;
        create_token_o.valid = create_ready_o;
        create_token_o.qtoken_id = {{(32-QTOKEN_IDX_W){1'b0}}, create_idx_o};
        create_token_o.qreg_id = collapse_i.qreg_id;
        create_token_o.branch_id = collapse_i.branch_id;
        create_token_o.state_id = collapse_i.state_id;
        create_token_o.measurement_value = collapse_i.measured_value;
        create_token_o.probability = collapse_i.probability;
        create_token_o.fidelity_score = collapse_i.fidelity_score;
        create_token_o.decoherence_risk = 8'd0;
        create_token_o.topology_epoch = topology_epoch_i;
        create_token_o.thermal_epoch = thermal_epoch_i;
        create_token_o.measured = 1'b1;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < QTOKEN_COUNT_P; i++) tokens[i] <= '0;
            rd_valid_o <= 1'b0;
            rd_token_o <= '0;
        end else begin
            rd_valid_o <= 1'b0;
            if (create_ready_o) tokens[create_idx_o] <= create_token_o;
            if (audit_mark_i) tokens[audit_idx_i].audited <= 1'b1;
            if (sync_mark_i) tokens[sync_idx_i].synced <= 1'b1;
            if (rollback_invalidate_i) begin
                for (i = 0; i < QTOKEN_COUNT_P; i++) begin
                    if (tokens[i].valid && tokens[i].state_id > rollback_from_state_i) begin
                        tokens[i].expired <= 1'b1;
                        tokens[i].rollback_discard <= 1'b1;
                    end
                end
            end
            if (rd_req_i) begin
                rd_valid_o <= 1'b1;
                rd_token_o <= tokens[rd_idx_i];
            end
        end
    end
endmodule
