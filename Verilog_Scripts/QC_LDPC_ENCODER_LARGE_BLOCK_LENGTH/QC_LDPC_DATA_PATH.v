//Modelling the Data Path of the Encoder

`timescale 1ns/1ps

module QC_LDPC_ENCODER_DATA_PATH(clk, clear_7bit_counter, clear_6bit_counter, increment_6bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, counter_7bit_out, counter_6bit_out, info_bit, generated_vector);
	input clk, clear_7bit_counter, clear_6bit_counter, increment_6bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA;
	input info_bit;
	output[16 * 88 - 1:0] generated_vector;
	output[6:0] counter_7bit_out;
	output[5:0] counter_6bit_out;

	wire[16 * 88 - 1:0] SRAA_in;

	//SRAA_16BIT sraa_1(clk, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, SRAA_in[31:16], generated_vector[31:16], info_bit);
	//SRAA_16BIT sraa_2(clk, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, SRAA_in[15:0], generated_vector[15:0], info_bit);
	//MUX31_16bit select_sraa_input(SRAA_in, G_row_1, G_row_2, Q_row, counter_2bit_out);
	COUNTER_6BIT row_block_indicator(clk, clear_6bit_counter, increment_6bit_counter, counter_6bit_out);
	COUNTER_7BIT row_indicator(clk, clear_7bit_counter, counter_7bit_out);
	G_MATRIX_MEMORY select_sraa_input(clk, counter_6bit_out, SRAA_in);

	genvar p;
	generate for (p = 16; p > 0; p = p - 1)
		begin
			SRAA_88BIT sraa_instance(clk, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, SRAA_in[p * 88 - 1: (p - 1) * 88], generated_vector[p * 88 - 1: (p - 1) * 88], info_bit);
		end
	endgenerate
endmodule
