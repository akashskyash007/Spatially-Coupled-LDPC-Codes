//Module to implement a 16 bit cyclic shift register

`timescale 1ns/1ps

module CYCLIC_SHIFT_REGISTER_16BIT(clk, load, in, out);
	input clk, load;
	input[15:0] in;
	output reg[15:0] out;

	always @(posedge clk) begin
		if (load)
			out <= in;
		else
			out <= {out[0], out[15:1]};
	end
endmodule
