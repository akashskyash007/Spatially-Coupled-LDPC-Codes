//Modelling the Data Path of the Encoder

`timescale 1ns/1ps

module QC_LDPC_ENCODER_DATA_PATH(clk, clear_5bit_counter, clear_2bit_counter, increment_2bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, G_row_1, G_row_2, Q_row, counter_5bit_out, counter_2bit_out, info_bit, generated_vector);
	input clk, clear_5bit_counter, clear_2bit_counter, increment_2bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA;
	input[31:0] G_row_1, G_row_2, Q_row;
	input info_bit;
	output[31:0] generated_vector;
	output[4:0] counter_5bit_out;
	output[1:0] counter_2bit_out;

	wire[31:0] SRAA_in;

	SRAA_16BIT sraa_1(clk, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, SRAA_in[31:16], generated_vector[31:16], info_bit);
	SRAA_16BIT sraa_2(clk, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, SRAA_in[15:0], generated_vector[15:0], info_bit);
	MUX31_16bit select_sraa_input(SRAA_in, G_row_1, G_row_2, Q_row, counter_2bit_out);
	COUNTER_2BIT row_block_indicator(clk, clear_2bit_counter, increment_2bit_counter, counter_2bit_out);
	COUNTER_5BIT row_indicator(clk, clear_5bit_counter, counter_5bit_out);
endmodule
