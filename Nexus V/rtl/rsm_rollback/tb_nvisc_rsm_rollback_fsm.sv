`timescale 1ns / 1ps

import nvisc_rsm_pkg::*;

module tb_nvisc_rsm_rollback_fsm;

    logic clk;
    logic rst_n;

    logic rollback_req;
    logic [31:0] target_state_id;
    logic [31:0] active_branch_id;
    logic [31:0] active_state_id;
    logic aegis_allow;

    logic rollback_busy;
    logic rollback_done;
    logic rollback_fault;
    nvisc_rsm_rollback_fault_e fault_code;

    logic state_meta_rd_req;
    logic [31:0] state_meta_rd_state_id;
    logic state_meta_rd_valid;
    nvisc_state_meta_t state_meta_rd_data;

    logic branch_meta_rd_req;
    logic [31:0] branch_meta_rd_branch_id;
    logic branch_meta_rd_valid;
    nvisc_branch_meta_t branch_meta_rd_data;

    logic branch_meta_wr_req;
    logic [31:0] branch_meta_wr_branch_id;
    nvisc_branch_meta_t branch_meta_wr_data;

    logic active_root_update;
    logic [31:0] active_page_root;
    logic [31:0] new_active_state_id;
    logic [31:0] new_active_commit_id;

    logic invalidate_descendants;
    logic [31:0] invalidate_from_state_id;

    logic delta_log_wr_req;
    nvisc_rsm_delta_entry_t delta_log_entry;

    nvisc_rsm_rollback_fsm dut (
        .clk(clk),
        .rst_n(rst_n),
        .rollback_req_i(rollback_req),
        .target_state_id_i(target_state_id),
        .active_branch_id_i(active_branch_id),
        .active_state_id_i(active_state_id),
        .aegis_rollback_allow_i(aegis_allow),
        .rollback_busy_o(rollback_busy),
        .rollback_done_o(rollback_done),
        .rollback_fault_o(rollback_fault),
        .rollback_fault_code_o(fault_code),
        .state_meta_rd_req_o(state_meta_rd_req),
        .state_meta_rd_state_id_o(state_meta_rd_state_id),
        .state_meta_rd_valid_i(state_meta_rd_valid),
        .state_meta_rd_data_i(state_meta_rd_data),
        .branch_meta_rd_req_o(branch_meta_rd_req),
        .branch_meta_rd_branch_id_o(branch_meta_rd_branch_id),
        .branch_meta_rd_valid_i(branch_meta_rd_valid),
        .branch_meta_rd_data_i(branch_meta_rd_data),
        .branch_meta_wr_req_o(branch_meta_wr_req),
        .branch_meta_wr_branch_id_o(branch_meta_wr_branch_id),
        .branch_meta_wr_data_o(branch_meta_wr_data),
        .active_root_update_o(active_root_update),
        .active_page_root_o(active_page_root),
        .new_active_state_id_o(new_active_state_id),
        .new_active_commit_id_o(new_active_commit_id),
        .invalidate_descendants_o(invalidate_descendants),
        .invalidate_from_state_id_o(invalidate_from_state_id),
        .delta_log_wr_req_o(delta_log_wr_req),
        .delta_log_entry_o(delta_log_entry)
    );

    always #5 clk = ~clk;

    task automatic clear_inputs;
        rollback_req = 1'b0;
        target_state_id = 32'd0;
        active_branch_id = 32'd1;
        active_state_id = 32'd9;
        aegis_allow = 1'b1;
        state_meta_rd_valid = 1'b0;
        state_meta_rd_data = '0;
        branch_meta_rd_valid = 1'b0;
        branch_meta_rd_data = '0;
    endtask

    task automatic drive_valid_state(input logic [31:0] sid, input logic rollback_valid, input logic [31:0] page_root);
        state_meta_rd_data = '0;
        state_meta_rd_data.valid = 1'b1;
        state_meta_rd_data.state_id = sid;
        state_meta_rd_data.branch_id = 32'd1;
        state_meta_rd_data.parent_state_id = 32'd3;
        state_meta_rd_data.commit_id = 32'd77;
        state_meta_rd_data.page_root_id = page_root;
        state_meta_rd_data.rollback_valid = rollback_valid;
        state_meta_rd_data.committed = 1'b1;
        state_meta_rd_valid = 1'b1;
        @(posedge clk);
        state_meta_rd_valid = 1'b0;
    endtask

    task automatic drive_branch_meta;
        branch_meta_rd_data = '0;
        branch_meta_rd_data.valid = 1'b1;
        branch_meta_rd_data.branch_id = 32'd1;
        branch_meta_rd_data.parent_branch_id = 32'd0;
        branch_meta_rd_data.head_state_id = 32'd9;
        branch_meta_rd_data.commit_id = 32'd90;
        branch_meta_rd_data.rollback_allowed = 1'b1;
        branch_meta_rd_valid = 1'b1;
        @(posedge clk);
        branch_meta_rd_valid = 1'b0;
    endtask

    initial begin
        clk = 1'b0;
        rst_n = 1'b0;
        clear_inputs();

        repeat (4) @(posedge clk);
        rst_n = 1'b1;
        repeat (2) @(posedge clk);

        // Valid rollback test.
        target_state_id = 32'd4;
        active_branch_id = 32'd1;
        active_state_id = 32'd9;
        rollback_req = 1'b1;
        @(posedge clk);

        wait (state_meta_rd_req);
        drive_valid_state(32'd4, 1'b1, 32'h0000_4000);

        wait (branch_meta_rd_req);
        drive_branch_meta();

        wait (active_root_update);
        assert(active_page_root == 32'h0000_4000) else $fatal("active_page_root not updated");
        assert(new_active_state_id == 32'd4) else $fatal("active_state_id not updated");
        assert(new_active_commit_id == 32'd77) else $fatal("active_commit_id not updated");

        wait (branch_meta_wr_req);
        assert(branch_meta_wr_data.head_state_id == 32'd4) else $fatal("branch head_state_id not updated");

        wait (invalidate_descendants);
        assert(invalidate_from_state_id == 32'd4 || invalidate_from_state_id == 32'd9) else $fatal("descendant invalidation missing");

        wait (delta_log_wr_req);
        assert(delta_log_entry.rollback_event == 1'b1) else $fatal("rollback delta event missing");
        assert(delta_log_entry.op_kind == DELTA_ROLLBACK) else $fatal("wrong delta op");

        wait (rollback_done);
        rollback_req = 1'b0;
        @(posedge clk);

        // Invalid state test.
        target_state_id = 32'd123;
        rollback_req = 1'b1;
        @(posedge clk);
        wait (state_meta_rd_req);
        state_meta_rd_data = '0;
        state_meta_rd_data.valid = 1'b0;
        state_meta_rd_valid = 1'b1;
        @(posedge clk);
        state_meta_rd_valid = 1'b0;
        wait (rollback_fault);
        assert(fault_code == RB_FAULT_INVALID_TARGET) else $fatal("expected invalid target fault");
        rollback_req = 1'b0;
        @(posedge clk);

        // Non-rollbackable state test.
        target_state_id = 32'd5;
        rollback_req = 1'b1;
        @(posedge clk);
        wait (state_meta_rd_req);
        drive_valid_state(32'd5, 1'b0, 32'h0000_5000);
        wait (rollback_fault);
        assert(fault_code == RB_FAULT_NOT_ROLLBACKABLE) else $fatal("expected not rollbackable fault");
        rollback_req = 1'b0;
        @(posedge clk);

        // Bad page root test.
        target_state_id = 32'd6;
        rollback_req = 1'b1;
        @(posedge clk);
        wait (state_meta_rd_req);
        drive_valid_state(32'd6, 1'b1, 32'h0000_0000);
        wait (rollback_fault);
        assert(fault_code == RB_FAULT_BAD_PAGE_ROOT) else $fatal("expected bad page root fault");
        rollback_req = 1'b0;
        @(posedge clk);

        $display("RSM rollback FSM smoke tests passed.");
        $finish;
    end

endmodule
