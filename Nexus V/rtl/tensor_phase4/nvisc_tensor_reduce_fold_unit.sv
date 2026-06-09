`timescale 1ns / 1ps
module nvisc_tensor_reduce_fold_unit #(
    parameter int NUM_NODES = 16,
    parameter int ACC_W = 64
)(
    input  logic signed [ACC_W-1:0] acc_i [NUM_NODES],
    input  logic [NUM_NODES-1:0] valid_mask_i,
    output logic result_valid_o,
    output logic signed [ACC_W-1:0] sum_o
);
    integer i;
    always_comb begin
        sum_o = '0;
        result_valid_o = &valid_mask_i;
        for (i = 0; i < NUM_NODES; i++) begin
            if (valid_mask_i[i]) sum_o = sum_o + acc_i[i];
        end
    end
endmodule
