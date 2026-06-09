`timescale 1ns/1ps
module tb_nexus_v_soc;
    logic clk;
    logic rst_n;

    // The actual nexus_v_soc.sv is instantiated here in the full build.
    // This testbench is a top-level scaffold for compiled RTL vectors.

    always #5 clk = ~clk;

    initial begin
        clk = 1'b0;
        rst_n = 1'b0;
        repeat (10) @(posedge clk);
        rst_n = 1'b1;
        $display("Nexus-V SoC regression scaffold started.");
        repeat (100) @(posedge clk);
        $display("Nexus-V SoC regression scaffold completed.");
        $finish;
    end
endmodule
