//Test Bench for Row Processing Operation

`timescale 1ns/1ps

module minimum_second_minimum_calculator_test_bench;
	reg clk, start_row_processing;
	reg[31:0] r1, r2, r3;
	wire[31:0] min, second_min;
	wire[1:0] pos;

	minimum_second_minimum_calculator_data_path DATA_PATH_DUT(clk, done_iterations, initialize_min, initialize_second_min, reset_count, calculating_second_min, r1, r2, r3, min, second_min, pos, load_first_min, load_second_min);
	minimum_second_minimum_calculator_control_path CONTROL_PATH_DUT(clk, start_row_processing, done_row_processing, done_iterations, initialize_min, initialize_second_min, reset_count, calculating_second_min, load_first_min, load_second_min);

	initial clk = 1'b0;

	always #5 clk = ~clk;

	initial begin
		$dumpfile("minimum_second_minimum_calculator.vcd");
		$dumpvars(0, minimum_second_minimum_calculator_test_bench);
		$monitor($time, ": Minimum = %32b, Position of Minimum = %2b, Second Minimum = %32b", min, pos, second_min);
		r3 = 32'b00111111100110011001100110011010; r1 = 32'b01000010110010000000000000000000; r2 = 32'b00111110100110011001100110011001;
		//r3 = 1.2 r1 = 100 r2 = 0.3
		#2 start_row_processing = 1'b1;
		#10 start_row_processing = 1'b0;
		#100 $finish;
	end
endmodule
