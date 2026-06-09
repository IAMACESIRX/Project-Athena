`timescale 1ns / 1ps
import nvisc_quantum_pkg::*;

module tb_nvisc_quantum_domain_engine;
    logic clk, rst_n;
    logic instr_valid;
    nvisc_qop_e qop;
    nvisc_qmode_e qmode;
    logic [3:0] qreg_idx;
    logic [31:0] branch_id, state_id;
    logic [15:0] topology_epoch, thermal_epoch;
    logic [7:0] seed;
    logic audit_allow;
    logic rollback_invalidate;
    logic [31:0] rollback_from_state;
    logic force_timeout, force_low_fidelity;
    logic busy, done, fault;
    nvisc_qfault_e fault_code;
    logic qsync_valid;
    logic [7:0] qsync_value;
    logic qaudit_req;
    logic qcommit_allow;

    nvisc_quantum_domain_engine dut (.*,
        .qhw_force_timeout_i(force_timeout),
        .qhw_force_low_fidelity_i(force_low_fidelity)
    );

    always #5 clk = ~clk;

    task pulse(input nvisc_qop_e op, input nvisc_qmode_e mode);
        begin
            qop = op; qmode = mode; instr_valid = 1'b1;
            @(posedge clk); instr_valid = 1'b0;
            repeat (2) @(posedge clk);
        end
    endtask

    initial begin
        clk = 0; rst_n = 0; instr_valid = 0; qop = QOP_NOP; qmode = QMODE_QSIM;
        qreg_idx = 0; branch_id = 32'hA; state_id = 32'h10;
        topology_epoch = 0; thermal_epoch = 0; seed = 8'd10;
        audit_allow = 0; rollback_invalidate = 0; rollback_from_state = 0;
        force_timeout = 0; force_low_fidelity = 0;
        repeat (4) @(posedge clk); rst_n = 1; repeat (2) @(posedge clk);

        pulse(QOP_QALLOC, QMODE_QSIM);
        pulse(QOP_QPREP, QMODE_QSIM);
        pulse(QOP_QX, QMODE_QSIM);
        pulse(QOP_QH, QMODE_QSIM);
        pulse(QOP_QMEASURE, QMODE_QSIM);
        assert(!fault) else $fatal("QMEASURE faulted unexpectedly");
        pulse(QOP_QSYNC, QMODE_QSIM);
        assert(qsync_valid) else $fatal("QSYNC did not expose deterministic result");
        pulse(QOP_QMEASURE, QMODE_QSIM);
        assert(fault && fault_code == QFAULT_USE_AFTER_COLLAPSE) else $fatal("Use-after-collapse did not fault");
        instr_valid = 0; repeat (2) @(posedge clk);
        audit_allow = 1; pulse(QOP_QAUDIT, QMODE_QSIM);
        pulse(QOP_QCOMMIT, QMODE_QSIM);
        assert(qcommit_allow) else $fatal("QCOMMIT did not require/pass audit allow");
        pulse(QOP_QROLLBACK, QMODE_QSIM);
        force_timeout = 0; pulse(QOP_QHW_DISP, QMODE_QHW);
        force_timeout = 1; pulse(QOP_QHW_DISP, QMODE_QHW); repeat (20) @(posedge clk);
        assert(fault || done) else $fatal("QHW timeout path did not complete/fault");
        $display("Phase 5 quantum smoke tests passed.");
        $finish;
    end
endmodule
