`timescale 1ns / 1ps

module nvisc_3d_cache_stub #(
    parameter int NUM_LINES = 16,
    parameter int ID_W = 8
)(
    input  logic clk,
    input  logic rst_n,

    // Core / upper-cache side.
    input  logic            core_req_valid_i,
    input  logic            core_req_is_read_i,
    input  logic            core_req_is_write_i,
    input  logic [63:0]     core_req_paddr_i,
    input  logic [63:0]     core_req_wdata_i,
    input  logic [7:0]      core_req_size_bytes_i,
    input  logic [ID_W-1:0] core_req_id_i,

    output logic            core_resp_valid_o,
    output logic [63:0]     core_resp_rdata_o,
    output logic            core_resp_write_ack_o,
    output logic [ID_W-1:0] core_resp_id_o,

    output logic            core_fault_o,
    output logic [15:0]     core_fault_code_o,

    // Backing memory side, later wired to DRAM.
    output logic            mem_req_valid_o,
    output logic            mem_req_is_read_o,
    output logic            mem_req_is_write_o,
    output logic [63:0]     mem_req_paddr_o,
    output logic [63:0]     mem_req_wdata_o,
    output logic [7:0]      mem_req_size_bytes_o,
    output logic [ID_W-1:0] mem_req_id_o,

    input  logic            mem_resp_valid_i,
    input  logic [63:0]     mem_resp_rdata_i,
    input  logic            mem_resp_write_ack_i,
    input  logic [ID_W-1:0] mem_resp_id_i,

    input  logic            mem_fault_i,
    input  logic [15:0]     mem_fault_code_i,

    input  logic            flush_i,

    output logic            dbg_hit_o,
    output logic            dbg_miss_o,
    output logic            dbg_fill_o,
    output logic            dbg_store_o,
    output logic [63:0]     dbg_cached_data_o
);

    localparam int IDX_W = (NUM_LINES <= 2) ? 1 : $clog2(NUM_LINES);
    localparam int INDEX_LSB = 3;

    localparam logic [15:0] CACHE_FAULT_NONE       = 16'h0000;
    localparam logic [15:0] CACHE_FAULT_ALIGN      = 16'h0C01;
    localparam logic [15:0] CACHE_FAULT_BAD_SIZE   = 16'h0C02;
    localparam logic [15:0] CACHE_FAULT_BAD_OPCODE = 16'h0C03;

    typedef enum logic [1:0] {
        ST_IDLE,
        ST_WAIT_FILL,
        ST_WAIT_STORE_ACK
    } cache_state_e;

    cache_state_e state_q;

    logic              valid_q [0:NUM_LINES-1];
    logic [63:0]       tag_q   [0:NUM_LINES-1];
    logic [63:0]       data_q  [0:NUM_LINES-1];

    logic [IDX_W-1:0]  index_c;
    logic [63:0]       line_tag_c;
    logic              hit_c;
    logic              aligned_c;
    logic              size_ok_c;
    logic              op_ok_c;

    logic [IDX_W-1:0]  pending_index_q;
    logic [63:0]       pending_tag_q;
    logic [63:0]       pending_paddr_q;
    logic [ID_W-1:0]   pending_id_q;
    logic              pending_read_q;
    logic              pending_write_q;

    assign index_c    = core_req_paddr_i[INDEX_LSB + IDX_W - 1:INDEX_LSB];
    assign line_tag_c = {core_req_paddr_i[63:INDEX_LSB + IDX_W], {INDEX_LSB + IDX_W{1'b0}}};

    assign hit_c      = valid_q[index_c] && (tag_q[index_c] == line_tag_c);
    assign aligned_c  = (core_req_paddr_i[2:0] == 3'b000);
    assign size_ok_c  = (core_req_size_bytes_i == 8);
    assign op_ok_c    = core_req_is_read_i ^ core_req_is_write_i;

    integer i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < NUM_LINES; i = i + 1) begin
                valid_q[i] <= 1'b0;
                tag_q[i]   <= 64'd0;
                data_q[i]  <= 64'd0;
            end

            state_q <= ST_IDLE;

            core_resp_valid_o     <= 1'b0;
            core_resp_rdata_o     <= 64'd0;
            core_resp_write_ack_o <= 1'b0;
            core_resp_id_o        <= '0;

            core_fault_o          <= 1'b0;
            core_fault_code_o     <= CACHE_FAULT_NONE;

            mem_req_valid_o       <= 1'b0;
            mem_req_is_read_o     <= 1'b0;
            mem_req_is_write_o    <= 1'b0;
            mem_req_paddr_o       <= 64'd0;
            mem_req_wdata_o       <= 64'd0;
            mem_req_size_bytes_o  <= 8'd0;
            mem_req_id_o          <= '0;

            pending_index_q       <= '0;
            pending_tag_q         <= 64'd0;
            pending_paddr_q       <= 64'd0;
            pending_id_q          <= '0;
            pending_read_q        <= 1'b0;
            pending_write_q       <= 1'b0;

            dbg_hit_o             <= 1'b0;
            dbg_miss_o            <= 1'b0;
            dbg_fill_o            <= 1'b0;
            dbg_store_o           <= 1'b0;
            dbg_cached_data_o     <= 64'd0;
        end else begin
            core_resp_valid_o     <= 1'b0;
            core_resp_rdata_o     <= 64'd0;
            core_resp_write_ack_o <= 1'b0;
            core_fault_o          <= 1'b0;
            core_fault_code_o     <= CACHE_FAULT_NONE;

            mem_req_valid_o       <= 1'b0;
            mem_req_is_read_o     <= 1'b0;
            mem_req_is_write_o    <= 1'b0;
            mem_req_paddr_o       <= 64'd0;
            mem_req_wdata_o       <= 64'd0;
            mem_req_size_bytes_o  <= 8'd0;
            mem_req_id_o          <= '0;

            dbg_hit_o             <= 1'b0;
            dbg_miss_o            <= 1'b0;
            dbg_fill_o            <= 1'b0;
            dbg_store_o           <= 1'b0;

            if (flush_i) begin
                for (i = 0; i < NUM_LINES; i = i + 1) begin
                    valid_q[i] <= 1'b0;
                end
            end

            unique case (state_q)
                ST_IDLE: begin
                    if (core_req_valid_i) begin
                        if (!aligned_c) begin
                            core_fault_o      <= 1'b1;
                            core_fault_code_o <= CACHE_FAULT_ALIGN;
                        end else if (!size_ok_c) begin
                            core_fault_o      <= 1'b1;
                            core_fault_code_o <= CACHE_FAULT_BAD_SIZE;
                        end else if (!op_ok_c) begin
                            core_fault_o      <= 1'b1;
                            core_fault_code_o <= CACHE_FAULT_BAD_OPCODE;
                        end else if (core_req_is_read_i) begin
                            if (hit_c) begin
                                dbg_hit_o             <= 1'b1;
                                dbg_cached_data_o     <= data_q[index_c];
                                core_resp_valid_o     <= 1'b1;
                                core_resp_rdata_o     <= data_q[index_c];
                                core_resp_id_o        <= core_req_id_i;
                            end else begin
                                dbg_miss_o            <= 1'b1;

                                pending_index_q       <= index_c;
                                pending_tag_q         <= line_tag_c;
                                pending_paddr_q       <= core_req_paddr_i;
                                pending_id_q          <= core_req_id_i;
                                pending_read_q        <= 1'b1;
                                pending_write_q       <= 1'b0;

                                mem_req_valid_o       <= 1'b1;
                                mem_req_is_read_o     <= 1'b1;
                                mem_req_paddr_o       <= core_req_paddr_i;
                                mem_req_size_bytes_o  <= core_req_size_bytes_i;
                                mem_req_id_o          <= core_req_id_i;

                                state_q               <= ST_WAIT_FILL;
                            end
                        end else if (core_req_is_write_i) begin
                            dbg_store_o           <= 1'b1;

                            valid_q[index_c]      <= 1'b1;
                            tag_q[index_c]        <= line_tag_c;
                            data_q[index_c]       <= core_req_wdata_i;
                            dbg_cached_data_o     <= core_req_wdata_i;

                            pending_index_q       <= index_c;
                            pending_tag_q         <= line_tag_c;
                            pending_paddr_q       <= core_req_paddr_i;
                            pending_id_q          <= core_req_id_i;
                            pending_read_q        <= 1'b0;
                            pending_write_q       <= 1'b1;

                            mem_req_valid_o       <= 1'b1;
                            mem_req_is_write_o    <= 1'b1;
                            mem_req_paddr_o       <= core_req_paddr_i;
                            mem_req_wdata_o       <= core_req_wdata_i;
                            mem_req_size_bytes_o  <= core_req_size_bytes_i;
                            mem_req_id_o          <= core_req_id_i;

                            state_q               <= ST_WAIT_STORE_ACK;
                        end
                    end
                end

                ST_WAIT_FILL: begin
                    if (mem_fault_i) begin
                        core_fault_o      <= 1'b1;
                        core_fault_code_o <= mem_fault_code_i;
                        state_q           <= ST_IDLE;
                    end else if (mem_resp_valid_i) begin
                        valid_q[pending_index_q] <= 1'b1;
                        tag_q[pending_index_q]   <= pending_tag_q;
                        data_q[pending_index_q]  <= mem_resp_rdata_i;

                        dbg_fill_o           <= 1'b1;
                        dbg_cached_data_o    <= mem_resp_rdata_i;

                        core_resp_valid_o    <= 1'b1;
                        core_resp_rdata_o    <= mem_resp_rdata_i;
                        core_resp_id_o       <= mem_resp_id_i;

                        state_q              <= ST_IDLE;
                    end
                end

                ST_WAIT_STORE_ACK: begin
                    if (mem_fault_i) begin
                        core_fault_o      <= 1'b1;
                        core_fault_code_o <= mem_fault_code_i;
                        state_q           <= ST_IDLE;
                    end else if (mem_resp_valid_i && mem_resp_write_ack_i) begin
                        core_resp_valid_o     <= 1'b1;
                        core_resp_write_ack_o <= 1'b1;
                        core_resp_id_o        <= mem_resp_id_i;
                        state_q               <= ST_IDLE;
                    end
                end

                default: begin
                    state_q <= ST_IDLE;
                end
            endcase
        end
    end

endmodule
