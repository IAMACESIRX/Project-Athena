`timescale 1ns / 1ps

import nvisc_topology_pkg::*;

module nvisc_topology_token_table #(
    parameter int DEPTH = 64,
    parameter int IDX_W = $clog2(DEPTH)
)(
    input  logic clk,
    input  logic rst_n,

    input  logic wr_req_i,
    input  nvisc_topology_token_t wr_token_i,
    output logic wr_ready_o,
    output logic [IDX_W-1:0] wr_index_o,

    input  logic invalidate_by_epoch_i,
    input  logic [15:0] current_topology_epoch_i,
    input  logic [15:0] current_thermal_epoch_i,

    input  logic rd_req_i,
    input  logic [IDX_W-1:0] rd_index_i,
    output logic rd_valid_o,
    output nvisc_topology_token_t rd_token_o
);

    nvisc_topology_token_t token_table [0:DEPTH-1];
    logic [IDX_W-1:0] wr_ptr_q;
    integer i;

    assign wr_ready_o = 1'b1;
    assign wr_index_o = wr_ptr_q;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wr_ptr_q <= '0;
            rd_valid_o <= 1'b0;
            rd_token_o <= '0;
            for (i = 0; i < DEPTH; i++) begin
                token_table[i] <= '0;
            end
        end else begin
            rd_valid_o <= 1'b0;

            if (wr_req_i && wr_ready_o) begin
                token_table[wr_ptr_q] <= wr_token_i;
                wr_ptr_q <= wr_ptr_q + 1'b1;
            end

            if (invalidate_by_epoch_i) begin
                for (i = 0; i < DEPTH; i++) begin
                    if (token_table[i].valid &&
                       ((token_table[i].topology_epoch != current_topology_epoch_i) ||
                        (token_table[i].thermal_epoch != current_thermal_epoch_i))) begin
                        token_table[i].valid <= 1'b0;
                        token_table[i].faulted <= 1'b1;
                    end
                end
            end

            if (rd_req_i) begin
                rd_token_o <= token_table[rd_index_i];
                rd_valid_o <= token_table[rd_index_i].valid;
            end
        end
    end

endmodule
