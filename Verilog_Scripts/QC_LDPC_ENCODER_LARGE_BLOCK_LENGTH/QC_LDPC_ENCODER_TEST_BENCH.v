//Test Bench for the Encoder

`timescale 1ns/1ps

module QC_LDPC_ENCODER_TEST_BENCH;
	reg start;
	reg info_bit;
	reg clk;
	reg[2126:0] info_vector;
	wire done;
	wire[16 * 88 - 1:0] generated_vector;
	wire[6:0] counter_7bit_out;
	wire[5:0] counter_6bit_out;
	integer iterator;
	integer fptr;
	integer scan_file;

	QC_LDPC_ENCODER_DATA_PATH DUT_DATA_PATH(clk, clear_7bit_counter, clear_6bit_counter, increment_6bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, counter_7bit_out, counter_6bit_out, info_bit, generated_vector);
	QC_LDPC_ENCODER_CONTROL_PATH DUT_CONTROL_PATH(clk, clear_7bit_counter, clear_6bit_counter, increment_6bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, counter_7bit_out, counter_6bit_out, start, done);

	initial begin
		fptr = $fopen("information_vector.txt", "r");
		scan_file = $fscanf(fptr, "%2127b", info_vector);
		$fclose(fptr);
	end

	initial clk = 1'b0;
	always #5 clk = ~clk;

	initial begin
		$dumpfile("QC_LDPC_ENCODER.vcd");
		$dumpvars(0, QC_LDPC_ENCODER_TEST_BENCH);
		$monitor($time, ": Last 1408 Bits of Code Word = %1408b", generated_vector);
		#2 start = 1'b1;
		#10 start = 1'b0;
		for (iterator = 2126; iterator >= 0; iterator = iterator - 1) begin
			#10 info_bit = info_vector[iterator];
		end
		#100000 $finish;
	end
endmodule
