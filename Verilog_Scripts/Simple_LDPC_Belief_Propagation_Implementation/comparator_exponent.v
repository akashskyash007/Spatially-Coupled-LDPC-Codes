`timescale 1ns/1ps

module comparator_exponent(l, g, in1, in2);
	input[7:0] in1;
	input[7:0] in2;
	output l, g;

	assign l = in1 < in2;
	assign g = in1 > in2;
endmodule
