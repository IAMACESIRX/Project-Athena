`timescale 1ns / 1ps
module nvisc_tensor_numeric_integrity_unit #(
    parameter int ACC_W = 64
)(
    input  logic check_i,
    input  logic signed [ACC_W-1:0] value_i,
    input  logic inject_nan_i,
    input  logic inject_overflow_i,
    output logic numeric_ok_o,
    output logic numeric_fault_o
);
    always_comb begin
        numeric_ok_o = 1'b0;
        numeric_fault_o = 1'b0;
        if (check_i) begin
            if (inject_nan_i || inject_overflow_i) begin
                numeric_fault_o = 1'b1;
            end else begin
                numeric_ok_o = 1'b1;
            end
        end
    end
endmodule
