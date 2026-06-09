`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_quantum_gate_unit (
    input  logic valid_i,
    input  nvisc_qop_e gate_i,
    input  nvisc_qsim_state_t state_i,
    output logic valid_o,
    output nvisc_qsim_state_t state_o,
    output logic fault_o,
    output nvisc_qfault_e fault_code_o
);
    always_comb begin
        valid_o = valid_i;
        state_o = state_i;
        fault_o = 1'b0;
        fault_code_o = QFAULT_NONE;

        if (valid_i && !state_i.valid) begin
            valid_o = 1'b0;
            fault_o = 1'b1;
            fault_code_o = QFAULT_INVALID_QREG;
        end else if (valid_i) begin
            unique case (gate_i)
                QOP_QX: begin
                    state_o.prob0 = state_i.prob1;
                    state_o.prob1 = state_i.prob0;
                    state_o.amp0_re = state_i.amp1_re;
                    state_o.amp1_re = state_i.amp0_re;
                end
                QOP_QH: begin
                    state_o.prob0 = 8'd128;
                    state_o.prob1 = 8'd128;
                    state_o.amp0_re = 16'h5a82;
                    state_o.amp1_re = 16'h5a82;
                end
                QOP_QGATE: begin
                    state_o = state_i;
                end
                default: begin
                    valid_o = 1'b0;
                    fault_o = 1'b1;
                    fault_code_o = QFAULT_UNSUPPORTED_GATE;
                end
            endcase
        end
    end
endmodule
