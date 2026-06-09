`timescale 1ns / 1ps

import nvisc_core_v02_pkg::*;

module nvisc_csr_file #(
    parameter logic [NV_CORE_ID_W-1:0] CORE_ID_RESET = 8'd0
)(
    input  logic clk,
    input  logic rst_n,

    input  logic        csr_valid_i,
    input  logic        csr_read_i,
    input  logic        csr_write_i,
    input  logic [11:0] csr_addr_i,
    input  logic [63:0] csr_wdata_i,

    input  logic [NV_THREAD_ID_W-1:0] thread_id_i,
    input  logic [NV_BRANCH_ID_W-1:0] branch_id_i,
    input  logic [NV_STATE_ID_W-1:0]  state_id_i,
    input  logic [NV_COMMIT_ID_W-1:0] commit_id_i,
    input  nvisc_priv_e              privilege_i,
    input  logic [NV_POLICY_ID_W-1:0] aegis_policy_id_i,

    output logic [63:0] csr_rdata_o,
    output logic        csr_rvalid_o,
    output logic        csr_fault_o,
    output logic [15:0] csr_fault_code_o,

    output nvisc_exec_identity_t id_o,

    // Debug-friendly mirrors.
    output logic [NV_CORE_ID_W-1:0]   dbg_core_id_o,
    output logic [NV_THREAD_ID_W-1:0] dbg_thread_id_o,
    output logic [NV_BRANCH_ID_W-1:0] dbg_branch_id_o,
    output logic [NV_STATE_ID_W-1:0]  dbg_state_id_o,
    output logic [NV_COMMIT_ID_W-1:0] dbg_commit_id_o,
    output logic [NV_PRIV_W-1:0]      dbg_privilege_o,
    output logic [NV_POLICY_ID_W-1:0] dbg_aegis_policy_id_o,
    output logic [63:0]               dbg_status_o
);

    logic [NV_CORE_ID_W-1:0]   core_id_q;
    logic [NV_THREAD_ID_W-1:0] thread_id_q;
    logic [NV_BRANCH_ID_W-1:0] branch_id_q;
    logic [NV_STATE_ID_W-1:0]  state_id_q;
    logic [NV_COMMIT_ID_W-1:0] commit_id_q;
    nvisc_priv_e              privilege_q;
    logic [NV_POLICY_ID_W-1:0] aegis_policy_id_q;
    logic [63:0]              status_q;

    logic [63:0] rdata_c;
    logic        addr_valid_c;

    always_comb begin
        rdata_c      = 64'd0;
        addr_valid_c = 1'b1;

        unique case (csr_addr_i)
            CSR_CORE_ID:      rdata_c = {{(64-NV_CORE_ID_W){1'b0}}, core_id_q};
            CSR_THREAD_ID:    rdata_c = {{(64-NV_THREAD_ID_W){1'b0}}, thread_id_q};
            CSR_BRANCH_ID_LO: rdata_c = {{(64-NV_BRANCH_ID_W){1'b0}}, branch_id_q};
            CSR_STATE_ID_LO:  rdata_c = {{(64-NV_STATE_ID_W){1'b0}}, state_id_q};
            CSR_COMMIT_ID_LO: rdata_c = {{(64-NV_COMMIT_ID_W){1'b0}}, commit_id_q};
            CSR_PRIVILEGE:    rdata_c = {{(64-NV_PRIV_W){1'b0}}, privilege_q};
            CSR_AEGIS_POLICY: rdata_c = {{(64-NV_POLICY_ID_W){1'b0}}, aegis_policy_id_q};
            CSR_STATUS:       rdata_c = status_q;
            default: begin
                rdata_c      = 64'd0;
                addr_valid_c = 1'b0;
            end
        endcase
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            core_id_q         <= CORE_ID_RESET;
            thread_id_q       <= '0;
            branch_id_q       <= 32'd1;
            state_id_q        <= 32'd1;
            commit_id_q       <= 32'd0;
            privilege_q       <= NV_PRIV_MACHINE;
            aegis_policy_id_q <= 16'd0;
            status_q          <= 64'd0;

            csr_rdata_o       <= 64'd0;
            csr_rvalid_o      <= 1'b0;
            csr_fault_o       <= 1'b0;
            csr_fault_code_o  <= 16'd0;
        end else begin
            // Live identity inputs update the active identity view every cycle.
            thread_id_q       <= thread_id_i;
            branch_id_q       <= branch_id_i;
            state_id_q        <= state_id_i;
            commit_id_q       <= commit_id_i;
            privilege_q       <= privilege_i;
            aegis_policy_id_q <= aegis_policy_id_i;

            csr_rvalid_o     <= 1'b0;
            csr_fault_o      <= 1'b0;
            csr_fault_code_o <= 16'd0;

            if (csr_valid_i) begin
                if (!addr_valid_c) begin
                    csr_fault_o      <= 1'b1;
                    csr_fault_code_o <= 16'h0002;
                end else begin
                    if (csr_read_i) begin
                        csr_rdata_o  <= rdata_c;
                        csr_rvalid_o <= 1'b1;
                    end

                    if (csr_write_i) begin
                        unique case (csr_addr_i)
                            CSR_STATUS:       status_q          <= csr_wdata_i;
                            CSR_AEGIS_POLICY: aegis_policy_id_q <= csr_wdata_i[NV_POLICY_ID_W-1:0];
                            CSR_PRIVILEGE:    privilege_q       <= nvisc_priv_e'(csr_wdata_i[NV_PRIV_W-1:0]);
                            default: begin
                                // Identity CSRs are read-only for this early v0.2 bring-up.
                                csr_fault_o      <= 1'b1;
                                csr_fault_code_o <= 16'h0003;
                            end
                        endcase
                    end
                end
            end
        end
    end

    assign id_o.core_id         = core_id_q;
    assign id_o.thread_id       = thread_id_q;
    assign id_o.branch_id       = branch_id_q;
    assign id_o.state_id        = state_id_q;
    assign id_o.commit_id       = commit_id_q;
    assign id_o.privilege       = privilege_q;
    assign id_o.aegis_policy_id = aegis_policy_id_q;

    assign dbg_core_id_o         = core_id_q;
    assign dbg_thread_id_o       = thread_id_q;
    assign dbg_branch_id_o       = branch_id_q;
    assign dbg_state_id_o        = state_id_q;
    assign dbg_commit_id_o       = commit_id_q;
    assign dbg_privilege_o       = privilege_q;
    assign dbg_aegis_policy_id_o = aegis_policy_id_q;
    assign dbg_status_o          = status_q;

endmodule
