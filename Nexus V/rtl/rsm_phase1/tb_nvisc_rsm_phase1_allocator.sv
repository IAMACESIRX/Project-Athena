`timescale 1ns / 1ps
import nvisc_rsm_pkg::*;

module tb_nvisc_rsm_phase1_allocator;
    localparam int TEST_PAGES = 4;
    localparam int TEST_PAGE_BYTES = 4096;
    localparam logic [31:0] TEST_BASE = 32'h1000_0000;

    logic clk, rst_n;
    logic alloc_req, alloc_ready, alloc_take;
    logic [31:0] alloc_paddr;
    logic [$clog2(TEST_PAGES)-1:0] alloc_idx;
    logic free_req, free_ok, free_fault;
    logic [31:0] free_paddr;
    logic seal_req, unseal_req;
    logic [31:0] seal_paddr, unseal_paddr;
    logic empty, full, alloc_fault;
    logic [$clog2(TEST_PAGES):0] free_count;

    nvisc_rsm_phys_alloc #(
        .NUM_PAGES_P(TEST_PAGES), .PADDR_W_P(32), .PAGE_BYTES_P(TEST_PAGE_BYTES), .PHYS_BASE_ADDR_P(TEST_BASE)
    ) dut (
        .clk(clk), .rst_n(rst_n),
        .alloc_req_i(alloc_req), .alloc_ready_o(alloc_ready), .alloc_paddr_o(alloc_paddr), .alloc_page_idx_o(alloc_idx), .alloc_take_i(alloc_take),
        .free_req_i(free_req), .free_paddr_i(free_paddr), .free_ok_o(free_ok), .free_fault_o(free_fault),
        .seal_req_i(seal_req), .seal_paddr_i(seal_paddr), .unseal_req_i(unseal_req), .unseal_paddr_i(unseal_paddr),
        .empty_o(empty), .full_o(full), .free_count_o(free_count), .alloc_fault_o(alloc_fault)
    );

    always #5 clk = ~clk;

    task automatic alloc_one(output logic [31:0] paddr);
        begin
            alloc_req = 1'b1;
            alloc_take = 1'b0;
            @(posedge clk);
            assert(alloc_ready) else $fatal("allocator not ready");
            paddr = alloc_paddr;
            alloc_take = 1'b1;
            @(posedge clk);
            alloc_req = 1'b0;
            alloc_take = 1'b0;
        end
    endtask

    initial begin
        logic [31:0] p0, p1, p2, p3;
        clk = 0; rst_n = 0;
        alloc_req = 0; alloc_take = 0; free_req = 0; free_paddr = 0;
        seal_req = 0; unseal_req = 0; seal_paddr = 0; unseal_paddr = 0;
        repeat(3) @(posedge clk); rst_n = 1; repeat(2) @(posedge clk);

        assert(free_count == TEST_PAGES) else $fatal("reset did not mark all pages free");
        alloc_one(p0); assert(p0 == TEST_BASE) else $fatal("first allocation wrong");
        alloc_one(p1); assert(p1 == TEST_BASE + TEST_PAGE_BYTES) else $fatal("second allocation wrong");

        free_paddr = p0; free_req = 1; @(posedge clk); assert(free_ok) else $fatal("free failed");
        free_req = 0; @(posedge clk);
        alloc_one(p2); assert(p2 == p0) else $fatal("freed page was not reused");

        seal_paddr = p2; seal_req = 1; @(posedge clk); seal_req = 0; @(posedge clk);
        free_paddr = p2; free_req = 1; @(posedge clk); assert(free_fault) else $fatal("sealed page was freed");
        free_req = 0; @(posedge clk);

        alloc_one(p3);
        alloc_req = 1; alloc_take = 0; @(posedge clk);
        assert(alloc_fault) else $fatal("alloc_fault did not assert when no page available");
        alloc_req = 0;

        $display("RSM Phase 1 allocator smoke tests passed.");
        $finish;
    end
endmodule
