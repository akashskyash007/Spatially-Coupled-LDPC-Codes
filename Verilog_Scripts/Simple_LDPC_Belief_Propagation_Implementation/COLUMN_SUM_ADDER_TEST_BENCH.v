//Test Bench to Test the Column Sum Adder

`timescale 1ns/1ps

module COLUMN_SUM_ADDER_TEST_BENCH;
	reg[31:0] r1, r2, r3;
	reg start;
	reg clk;
	wire[31:0] sum;
	wire done;

	COLUMN_SUM_CALCULATOR_DATA_PATH data_path_column_sum_calculation(clk, clr, done_iterations, sum, r1, r2, r3, load_sum);
	COLUMN_SUM_CALCULATOR_CONTROL_PATH control_path_column_sum_calculation(clk, done, start, clr, done_iterations, load_sum);

	initial clk = 1'b0;
	always #5 clk = ~clk;

	initial begin
		$dumpfile("COLUMN_SUM_CALCULATOR.vcd");
		$dumpvars(0, COLUMN_SUM_ADDER_TEST_BENCH);
		$monitor($time, ": Sum = %32b, Done = %b", sum, done);
		r1 = 32'b10111111010011001100110011001101; //r1 = -0.8
		r2 = 32'b10111111000110011001100110011010; //r2 = -0.6
		r3 = 32'b00111111000110011001100110011010; //r3 = 0.6
		#2 start = 1'b1;
		#10 start = 1'b0;
		#100 $finish;
	end
endmodule
