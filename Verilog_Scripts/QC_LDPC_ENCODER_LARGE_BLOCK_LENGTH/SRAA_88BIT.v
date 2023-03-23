//Modelling an 88 bit Shift Register Add Accumulate Circuit

`timescale 1ns/1ps

module SRAA_88BIT(clk, load_shift_reg, load_reg, clear, in, out, info_bit);
	input clk, load, clear;
	input info_bit;
	input[87:0] in;
	output[87:0] out;
	input load_shift_reg, load_reg;

	wire[87:0] current_gi;
	reg[87:0] temp;
	reg[87:0] reg_in;
	integer iterator;

	CYCLIC_SHIFT_REGISTER_88BIT current_gi_calculator(clk, load_shift_reg, in, current_gi);
	SHIFT_REGISTER_88_BIT generate_final_output(clk, clear, load_reg, reg_in, out);

	always @(*) begin
		for (iterator = 0; iterator <= 87; iterator = iterator + 1) begin
			temp[iterator] = current_gi[iterator] & info_bit;
			reg_in[iterator] = out[iterator] ^ temp[iterator];
		end
	end
endmodule
