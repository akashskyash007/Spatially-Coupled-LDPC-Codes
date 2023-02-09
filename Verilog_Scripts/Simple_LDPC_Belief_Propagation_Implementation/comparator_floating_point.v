`timescale 1ns/1ps

module comparator_floating_point(l, in1, in2);
	input[31:0] in1, in2;
	output l;

	wire mantissa_l;
	wire exponent_l, exponent_g;
	wire t0, t1;

	comparator_mantissa COMPARE_MANTISSAS(mantissa_l, in1[22:0], in2[22:0]);
	comparator_exponent COMPARE_EXPONENTS(exponent_l, exponent_g, in1[30:23], in2[30:23]);
	not G1(t0, exponent_g);
	and G2(t1, mantissa_l, t0);
	or G3(l, exponent_l, t1);
endmodule
