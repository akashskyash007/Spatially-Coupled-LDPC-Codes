//Test Bench for Row Processing Operation

`timescale 1ns/1ps

module minimum_second_minimum_calculator_test_bench;
	reg clk, start_row_processing;
	reg[32 * 40 - 1: 0] inputs;
	reg[31: 0] temp;
	integer scan_file, i, j, k, fptr;
	wire[31: 0] min, second_min;
	wire[5: 0] pos;

	minimum_second_minimum_calculator_data_path DATA_PATH_DUT(clk, done_iterations, initialize_min, initialize_second_min, reset_count, calculating_second_min, inputs, min, second_min, pos, load_first_min, load_second_min);
	minimum_second_minimum_calculator_control_path CONTROL_PATH_DUT(clk, start_row_processing, done_row_processing, done_iterations, initialize_min, initialize_second_min, reset_count, calculating_second_min, load_first_min, load_second_min);

	initial clk = 1'b0;

	always #5 clk = ~clk;
	
	initial begin
		fptr = $fopen("row_processing_test_inputs.txt", "r");
		for (i = 0; i < 40; i++) begin
			scan_file = $fscanf(fptr, "%32b\n", temp);
			//inputs[i * 32 + 32 - 1: i * 32] = temp;
			j = i * 32 + 32 - 1;
			k = 31;
			while (k >= 0) begin
				inputs[j] = temp[k];
				j = j - 1;
				k = k - 1;
			end
		end
		$fclose(fptr);
	end

	initial begin
		$dumpfile("minimum_second_minimum_calculator.vcd");
		$dumpvars(0, minimum_second_minimum_calculator_test_bench);
		$monitor($time, ": Minimum = %32b, Position of Minimum = %6b, Second Minimum = %32b", min, pos, second_min);
		#2 start_row_processing = 1'b1;
		#10 start_row_processing = 1'b0;
		#10000 $finish;
	end
endmodule
