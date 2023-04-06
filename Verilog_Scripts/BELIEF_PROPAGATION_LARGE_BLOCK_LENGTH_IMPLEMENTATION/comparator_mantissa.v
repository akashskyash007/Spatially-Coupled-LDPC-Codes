`timescale 1ns/1ps

module comparator_mantissa(l, in1, in2);
	input[22:0] in1, in2;
	output l;

	assign l = (in1 < in2);
endmodule
