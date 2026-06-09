`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_quantum_measure_unit (
    input  logic clk,
    input  logic rst_n,

    input  logic measure_req_i,
    input  nvisc_qreg_meta_t qmeta_i,
    input  nvisc_qsim_state_t qstate_i,
    input  logic [7:0] seed_i,

    output logic measure_valid_o,
    output nvisc_qcollapse_reg_t collapse_o,
    output logic fault_o,
    output nvisc_qfault_e fault_code_o
);
    logic [7:0] measured_value_c;
    logic [7:0] probability_c;

    always_comb begin
        measured_value_c = (seed_i < qstate_i.prob0) ? 8'd0 : 8'd1;
        probability_c = (measured_value_c == 8'd0) ? qstate_i.prob0 : qstate_i.prob1;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            measure_valid_o <= 1'b0;
            collapse_o <= '0;
            fault_o <= 1'b0;
            fault_code_o <= QFAULT_NONE;
        end else begin
            measure_valid_o <= 1'b0;
            fault_o <= 1'b0;
            fault_code_o <= QFAULT_NONE;
            if (measure_req_i) begin
                if (!qmeta_i.valid) begin
                    fault_o <= 1'b1;
                    fault_code_o <= QFAULT_INVALID_QREG;
                end else if (!qmeta_i.prepared) begin
                    fault_o <= 1'b1;
                    fault_code_o <= QFAULT_NOT_PREPARED;
                end else if (qmeta_i.collapsed) begin
                    fault_o <= 1'b1;
                    fault_code_o <= QFAULT_USE_AFTER_COLLAPSE;
                end else begin
                    measure_valid_o <= 1'b1;
                    collapse_o.valid <= 1'b1;
                    collapse_o.qreg_id <= qmeta_i.qreg_id;
                    collapse_o.qtoken_id <= qmeta_i.qreg_id;
                    collapse_o.branch_id <= qmeta_i.branch_id;
                    collapse_o.state_id <= qmeta_i.state_id;
                    collapse_o.measured_value <= measured_value_c;
                    collapse_o.probability <= probability_c;
                    collapse_o.fidelity_score <= qmeta_i.fidelity_score;
                    collapse_o.collapse_complete <= 1'b1;
                    collapse_o.sync_required <= 1'b1;
                    collapse_o.audit_required <= 1'b1;
                end
            end
        end
    end
endmodule
