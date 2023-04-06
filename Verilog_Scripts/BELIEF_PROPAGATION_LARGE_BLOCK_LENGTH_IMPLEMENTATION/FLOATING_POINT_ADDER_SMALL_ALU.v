//Module that compares the two exponents and generates their difference

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_SMALL_ALU(l, diff, exp1, exp2);
	input[7:0] exp1, exp2;
	output l;
	output reg[7:0] diff;

	assign l = (exp1 < exp2);

	always @(*) begin
		if (l)
			diff = exp2 - exp1;
		else
			diff = exp1 - exp2;
	end
endmodule
