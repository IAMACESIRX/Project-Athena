`timescale 1ns / 1ps

module nvisc_dram_controller_stub #(
    parameter logic [63:0] BASE_ADDR  = 64'h0000_0000_8000_0000,
    parameter int          MEM_WORDS  = 1024,
    parameter int          LATENCY_CYCLES = 3,
    parameter int          ID_W = 8
)(
    input  logic clk,
    input  logic rst_n,

    input  logic              req_valid_i,
    input  logic              req_is_read_i,
    input  logic              req_is_write_i,
    input  logic [63:0]       req_paddr_i,
    input  logic [63:0]       req_wdata_i,
    input  logic [7:0]        req_size_bytes_i,
    input  logic [ID_W-1:0]   req_id_i,

    output logic              resp_valid_o,
    output logic [63:0]       resp_rdata_o,
    output logic              resp_write_ack_o,
    output logic [ID_W-1:0]   resp_id_o,

    output logic              fault_o,
    output logic [15:0]       fault_code_o,

    output logic              dbg_busy_o,
    output logic [63:0]       dbg_last_paddr_o,
    output logic [63:0]       dbg_last_wdata_o,
    output logic [63:0]       dbg_last_rdata_o
);

    localparam int IDX_W = (MEM_WORDS <= 2) ? 1 : $clog2(MEM_WORDS);

    localparam logic [15:0] DRAM_FAULT_NONE       = 16'h0000;
    localparam logic [15:0] DRAM_FAULT_RANGE      = 16'h0D01;
    localparam logic [15:0] DRAM_FAULT_ALIGN      = 16'h0D02;
    localparam logic [15:0] DRAM_FAULT_BAD_SIZE   = 16'h0D03;
    localparam logic [15:0] DRAM_FAULT_BAD_OPCODE = 16'h0D04;

    logic [63:0] mem_q [0:MEM_WORDS-1];

    logic [63:0] offset_c;
    logic [63:0] word_index_full_c;
    logic [IDX_W-1:0] word_index_c;
    logic [63:0] mem_words_64_c;

    logic in_range_c;
    logic aligned_c;
    logic size_ok_c;
    logic op_ok_c;
    logic req_ok_c;

    logic busy_q;
    logic [$clog2(LATENCY_CYCLES + 2)-1:0] latency_q;

    logic        pending_read_q;
    logic        pending_write_q;
    logic [63:0] pending_paddr_q;
    logic [63:0] pending_wdata_q;
    logic [IDX_W-1:0] pending_index_q;
    logic [ID_W-1:0] pending_id_q;

    assign offset_c          = req_paddr_i - BASE_ADDR;
    assign word_index_full_c = offset_c >> 3;
    assign word_index_c      = word_index_full_c[IDX_W-1:0];
    assign mem_words_64_c    = 64'(MEM_WORDS);

    always_comb begin
        in_range_c = (req_paddr_i >= BASE_ADDR) && (word_index_full_c < mem_words_64_c);
        aligned_c  = (req_paddr_i[2:0] == 3'b000);
        size_ok_c  = (req_size_bytes_i == 8);
        op_ok_c    = req_is_read_i ^ req_is_write_i;
        req_ok_c   = req_valid_i && in_range_c && aligned_c && size_ok_c && op_ok_c;
    end

    integer i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < MEM_WORDS; i = i + 1) begin
                mem_q[i] <= 64'd0;
            end

            resp_valid_o     <= 1'b0;
            resp_rdata_o     <= 64'd0;
            resp_write_ack_o <= 1'b0;
            resp_id_o        <= '0;

            fault_o          <= 1'b0;
            fault_code_o     <= DRAM_FAULT_NONE;

            busy_q           <= 1'b0;
            latency_q        <= '0;

            pending_read_q   <= 1'b0;
            pending_write_q  <= 1'b0;
            pending_paddr_q  <= 64'd0;
            pending_wdata_q  <= 64'd0;
            pending_index_q  <= '0;
            pending_id_q     <= '0;

            dbg_last_paddr_o <= 64'd0;
            dbg_last_wdata_o <= 64'd0;
            dbg_last_rdata_o <= 64'd0;
        end else begin
            resp_valid_o     <= 1'b0;
            resp_rdata_o     <= 64'd0;
            resp_write_ack_o <= 1'b0;
            fault_o          <= 1'b0;
            fault_code_o     <= DRAM_FAULT_NONE;

            if (req_valid_i && !busy_q) begin
                if (!in_range_c) begin
                    fault_o      <= 1'b1;
                    fault_code_o <= DRAM_FAULT_RANGE;
                end else if (!aligned_c) begin
                    fault_o      <= 1'b1;
                    fault_code_o <= DRAM_FAULT_ALIGN;
                end else if (!size_ok_c) begin
                    fault_o      <= 1'b1;
                    fault_code_o <= DRAM_FAULT_BAD_SIZE;
                end else if (!op_ok_c) begin
                    fault_o      <= 1'b1;
                    fault_code_o <= DRAM_FAULT_BAD_OPCODE;
                end else begin
                    busy_q          <= 1'b1;
                    latency_q       <= LATENCY_CYCLES[$bits(latency_q)-1:0];

                    pending_read_q  <= req_is_read_i;
                    pending_write_q <= req_is_write_i;
                    pending_paddr_q <= req_paddr_i;
                    pending_wdata_q <= req_wdata_i;
                    pending_index_q <= word_index_c;
                    pending_id_q    <= req_id_i;

                    dbg_last_paddr_o <= req_paddr_i;
                    dbg_last_wdata_o <= req_wdata_i;
                end
            end else if (busy_q) begin
                if (latency_q != 0) begin
                    latency_q <= latency_q - 1'b1;
                end else begin
                    busy_q       <= 1'b0;
                    resp_valid_o <= 1'b1;
                    resp_id_o    <= pending_id_q;

                    if (pending_write_q) begin
                        mem_q[pending_index_q] <= pending_wdata_q;
                        resp_write_ack_o       <= 1'b1;
                    end

                    if (pending_read_q) begin
                        resp_rdata_o     <= mem_q[pending_index_q];
                        dbg_last_rdata_o <= mem_q[pending_index_q];
                    end
                end
            end
        end
    end

    assign dbg_busy_o = busy_q;

endmodule
