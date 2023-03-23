//Test Bench for the Encoder

`timescale 1ns/1ps

module QC_LDPC_ENCODER_TEST_BENCH;
	reg start;
	reg info_bit;
	reg clk;
	reg[32:0] info_vector;
	reg[31:0] G_row_1, G_row_2, Q_row;
	wire done;
	wire[31:0] generated_vector;
	wire[4:0] counter_5bit_out;
	wire[1:0] counter_2bit_out;
	integer iterator;

	QC_LDPC_ENCODER_DATA_PATH DUT_DATA_PATH(clk, clear_5bit_counter, clear_2bit_counter, increment_2bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, G_row_1, G_row_2, Q_row, counter_5bit_out, counter_2bit_out, info_bit, generated_vector);
	QC_LDPC_ENCODER_CONTROL_PATH DUT_CONTROL_PATH(clk, clear_5bit_counter, clear_2bit_counter, increment_2bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, counter_5bit_out, counter_2bit_out, start, done);

	initial info_vector = 33'b110000111111000101001101110110111;

	initial begin
		G_row_1 = 32'b11111110000000110000111111110000;
		G_row_2 = 32'b11110000001111111111111110000000;
	       	Q_row = 32'b11111111111111111111111111111111;
	end

	initial clk = 1'b0;
	always #5 clk = ~clk;

	initial begin
		$dumpfile("QC_LDPC_ENCODER.vcd");
		$dumpvars(0, QC_LDPC_ENCODER_TEST_BENCH);
		$monitor($time, ": Last 32 Bits of Code Word = %32b", generated_vector);
		#2 start = 1'b1;
		#10 start = 1'b0;
		for (iterator = 32; iterator >= 0; iterator = iterator - 1) begin
			#10 info_bit = info_vector[iterator];
		end
		#100 $finish;
	end
endmodule
