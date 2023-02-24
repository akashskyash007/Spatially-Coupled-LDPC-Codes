//Modelling a 16 bit Shift Register Add Accumulate Circuit

`timescale 1ns/1ps

module SRAA_16BIT(clk, load_shift_reg, load_reg, clear, in, out, info_bit);
	input clk, load, clear;
	input info_bit;
	input[15:0] in;
	output[15:0] out;
	input load_shift_reg, load_reg;

	wire[15:0] current_gi;
	reg[15:0] temp;
	reg[15:0] reg_in;
	integer iterator;

	CYCLIC_SHIFT_REGISTER_16BIT current_gi_calculator(clk, load_shift_reg, in, current_gi);
	SHIFT_REGISTER_16_BIT generate_final_output(clk, clear, load_reg, reg_in, out);

	always @(*) begin
		for (iterator = 0; iterator <= 15; iterator = iterator + 1) begin
			temp[iterator] = current_gi[iterator] & info_bit;
			reg_in[iterator] = out[iterator] ^ temp[iterator];
		end
	end
endmodule
