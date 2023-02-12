//Test Bench to Test the Column Sum Adder

`timescale 1ns/1ps

module COLUMN_SUM_ADDER_TEST_BENCH;
	reg[31:0] r1, r2, r3;
	reg start;
	reg clk;
	wire[31:0] sum;
	wire done;

	COLUMN_SUM_CALCULATOR_DATA_PATH data_path_column_sum_calculation(clk, clr, done_iterations, sum, r1, r2, r3);
	COLUMN_SUM_CALCULATOR_CONTROL_PATH control_path_column_sum_calculation(clk, done, start, clr, done_iterations);

	initial clk = 1'b0;
	always #5 clk = ~clk;

	initial begin
		$dumpfile("COLUMN_SUM_CALCULATOR.vcd");
		$dumpvars(0, COLUMN_SUM_ADDER_TEST_BENCH);
		$monitor($time, ": Sum = %32b, Done = %b", sum, done);
		r1 = 32'b00111111100110011001100110011010; //r1 = 1.2
		r2 = 32'b01000000000110011001100110011010; //r2 = 2.4
		r3 = 32'b01000000111111001100110011001101; //r3 = 7.9
		#2 start = 1'b1;
		#10 start = 1'b0;
		#100 $finish;
	end
endmodule
