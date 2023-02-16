//Test Bench for Belief Propagation

`timescale 1ns/1ps

module BELIEF_PROPAGATION_TEST_BENCH;
	reg[32 * 6 - 1: 0] received_vector;
	reg start;
	reg clk;
	wire[32 * 6 - 1: 0] sum_vector;
	wire done;

	BELIEF_PROPAGATION_DATA_PATH DUT_DATA_PATH(clk, start_row_processing, start_column_processing, done_row_processing_row_1, done_row_processing_row_2, done_row_processing_row_3, done_column_processing_column_1, done_column_processing_column_2, done_column_processing_column_3, done_column_processing_column_4, done_column_processing_column_5, done_column_processing_column_6, initialize_parity_check_matrix, load_parity_check_matrix, load_sum_vector, select_input_to_parity_check_matrix, reset_count, increment_count, done_iterations, received_vector, sum_vector);
	BELIEF_PROPAGATION_CONTROL_PATH DUT_CONTROL_PATH(clk, start, done, start_row_processing, start_column_processing, done_row_processing_row_1, done_row_processing_row_2, done_row_processing_row_3, done_column_processing_column_1, done_column_processing_column_2, done_column_processing_column_3, done_column_processing_column_4, done_column_processing_column_5, done_column_processing_column_6, initialize_parity_check_matrix, load_parity_check_matrix, load_sum_vector, select_input_to_parity_check_matrix, reset_count, increment_count, done_iterations);

	initial clk = 1'b0;
	always #5 clk = ~clk;

	initial begin
		$dumpfile("BELIEF_PROPAGATION.vcd");
		$dumpvars(0, BELIEF_PROPAGATION_TEST_BENCH);
		//$monitor($time, ": Iteration Number = %4b, Sum Vector = %32b %32b %32b %32b %32b %32b", DUT_DATA_PATH.count, sum_vector[32*6 - 1: 32*5], sum_vector[32*5-1:32*4], sum_vector[32*4-1:32*3], sum_vector[32*3-1:32*2], sum_vector[32*2-1:32], sum_vector[31:0]);
		$monitor("%32b %32b %32b %32b %32b %32b\n%32b %32b %32b %32b %32b %32b\n%32b %32b %32b %32b %32b %32b\n", DUT_DATA_PATH.parity_check_matrix[0][0], DUT_DATA_PATH.parity_check_matrix[0][1], DUT_DATA_PATH.parity_check_matrix[0][2], DUT_DATA_PATH.parity_check_matrix[0][3], DUT_DATA_PATH.parity_check_matrix[0][4], DUT_DATA_PATH.parity_check_matrix[0][5], DUT_DATA_PATH.parity_check_matrix[1][0], DUT_DATA_PATH.parity_check_matrix[1][1], DUT_DATA_PATH.parity_check_matrix[1][2], DUT_DATA_PATH.parity_check_matrix[1][3], DUT_DATA_PATH.parity_check_matrix[1][4], DUT_DATA_PATH.parity_check_matrix[1][5], DUT_DATA_PATH.parity_check_matrix[2][0], DUT_DATA_PATH.parity_check_matrix[2][1], DUT_DATA_PATH.parity_check_matrix[2][2], DUT_DATA_PATH.parity_check_matrix[2][3], DUT_DATA_PATH.parity_check_matrix[2][4], DUT_DATA_PATH.parity_check_matrix[2][5]);
		received_vector[32*6-1:32*5] = 32'b00111111101101110000101000111101;
		received_vector[32*5-1:32*4] = 32'b10111110100111101011100001010010;
		received_vector[32*4-1:32*3] = 32'b00111111000010100011110101110001;
		received_vector[32*3-1:32*2] = 32'b10111110011010111000010100011111;
		received_vector[32*2-1:32*1] = 32'b10111110111100001010001111010111;
		received_vector[31:0] = 32'b00111111010110011001100110011010;
		#2 start = 1'b1;
		#10 start = 1'b0;
		#10000 $finish;
	end
endmodule
