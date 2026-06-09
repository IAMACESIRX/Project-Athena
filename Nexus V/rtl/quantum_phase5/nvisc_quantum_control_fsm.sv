`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module nvisc_quantum_control_fsm (
    input  logic clk,
    input  logic rst_n,
    input  logic instr_valid_i,
    input  nvisc_qop_e qop_i,
    input  nvisc_qmode_e qmode_i,
    input  logic audit_allow_i,
    input  logic qhw_done_i,
    input  logic qhw_timeout_i,
    input  logic [7:0] qhw_fidelity_i,
    output logic busy_o,
    output logic done_o,
    output logic fault_o,
    output nvisc_qfault_e fault_code_o,
    output logic audit_req_o,
    output logic commit_allow_o,
    output logic rollback_discard_o
);
    typedef enum logic [4:0] {
        Q_IDLE,
        Q_ALLOC,
        Q_PREP,
        Q_GATE_APPLY,
        Q_HW_DISPATCH,
        Q_HW_WAIT,
        Q_MEASURE,
        Q_COLLAPSE,
        Q_SYNC,
        Q_AUDIT_REQ,
        Q_AUDIT_WAIT,
        Q_COMMIT,
        Q_ROLLBACK,
        Q_FAULT,
        Q_DONE
    } qfsm_e;

    qfsm_e state_q, state_d;
    nvisc_qfault_e fault_q, fault_d;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state_q <= Q_IDLE;
            fault_q <= QFAULT_NONE;
        end else begin
            state_q <= state_d;
            fault_q <= fault_d;
        end
    end

    always_comb begin
        state_d = state_q;
        fault_d = fault_q;
        busy_o = (state_q != Q_IDLE) && (state_q != Q_DONE) && (state_q != Q_FAULT);
        done_o = 1'b0;
        fault_o = 1'b0;
        fault_code_o = fault_q;
        audit_req_o = 1'b0;
        commit_allow_o = 1'b0;
        rollback_discard_o = 1'b0;

        unique case (state_q)
            Q_IDLE: begin
                fault_d = QFAULT_NONE;
                if (instr_valid_i) begin
                    unique case (qop_i)
                        QOP_QALLOC: state_d = Q_ALLOC;
                        QOP_QPREP:  state_d = Q_PREP;
                        QOP_QX, QOP_QH, QOP_QGATE: state_d = Q_GATE_APPLY;
                        QOP_QHW_DISP: state_d = (qmode_i == QMODE_QHW) ? Q_HW_DISPATCH : Q_FAULT;
                        QOP_QMEASURE: state_d = Q_MEASURE;
                        QOP_QSYNC: state_d = Q_SYNC;
                        QOP_QAUDIT: state_d = Q_AUDIT_REQ;
                        QOP_QCOMMIT: state_d = Q_COMMIT;
                        QOP_QROLLBACK: state_d = Q_ROLLBACK;
                        default: begin
                            state_d = Q_FAULT;
                            fault_d = QFAULT_UNSUPPORTED_GATE;
                        end
                    endcase
                end
            end
            Q_ALLOC, Q_PREP, Q_GATE_APPLY, Q_MEASURE, Q_SYNC: state_d = Q_DONE;
            Q_HW_DISPATCH: state_d = Q_HW_WAIT;
            Q_HW_WAIT: begin
                if (qhw_timeout_i) begin
                    state_d = Q_FAULT;
                    fault_d = QFAULT_QHW_TIMEOUT;
                end else if (qhw_done_i) begin
                    if (qhw_fidelity_i < 8'd100) begin
                        state_d = Q_FAULT;
                        fault_d = QFAULT_LOW_FIDELITY;
                    end else state_d = Q_DONE;
                end
            end
            Q_AUDIT_REQ: begin
                audit_req_o = 1'b1;
                state_d = Q_AUDIT_WAIT;
            end
            Q_AUDIT_WAIT: begin
                if (audit_allow_i) state_d = Q_DONE;
                else begin
                    state_d = Q_FAULT;
                    fault_d = QFAULT_AEGIS_DENIED;
                end
            end
            Q_COMMIT: begin
                commit_allow_o = audit_allow_i;
                if (audit_allow_i) state_d = Q_DONE;
                else begin
                    state_d = Q_FAULT;
                    fault_d = QFAULT_AEGIS_DENIED;
                end
            end
            Q_ROLLBACK: begin
                rollback_discard_o = 1'b1;
                state_d = Q_DONE;
            end
            Q_DONE: begin
                done_o = 1'b1;
                if (!instr_valid_i) state_d = Q_IDLE;
            end
            Q_FAULT: begin
                fault_o = 1'b1;
                if (!instr_valid_i) state_d = Q_IDLE;
            end
            default: state_d = Q_FAULT;
        endcase

        if (state_q == Q_IDLE && instr_valid_i && qop_i == QOP_QHW_DISP && qmode_i != QMODE_QHW) begin
            fault_d = QFAULT_QMODE_MISMATCH;
        end
    end
endmodule
