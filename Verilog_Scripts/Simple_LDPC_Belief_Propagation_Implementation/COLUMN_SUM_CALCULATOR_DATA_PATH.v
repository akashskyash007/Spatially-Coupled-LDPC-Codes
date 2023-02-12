//Data Path of Hardware to Calculate the Column Sum

`timescale 1ns/1ps

module COLUMN_SUM_CALCULATOR_DATA_PATH(clk, clr, done_iterations, sum_out, r1, r2, r3);
	input clk, clr;
	input[31:0] r1, r2, r3;
	output[31:0] sum_out;
	output done_iterations;

	wire[1:0] count;
	wire[31:0] adder_input;
	wire[31:0] sum_in;

	assign done_iterations = (count == 2'b11);

	BUS_MUX_31 select_adder_input(adder_input, r1, r2, r3, count);
	FLOATING_POINT_ADDER_DATA_PATH generate_current_sum(adder_input, sum_out, sum_in);
	COLUMN_SUM_PIPO_REGISTER store_sum_value(clk, clr, sum_out, sum_in);
	COLUMN_SUM_UP_COUNTER generate_column_index(clk, clr, count);
endmodule
