//Module to implement an 88 bit cyclic shift register

`timescale 1ns/1ps

module CYCLIC_SHIFT_REGISTER_88BIT(clk, load, in, out);
	input clk, load;
	input[87:0] in;
	output reg[87:0] out;

	always @(posedge clk) begin
		if (load)
			out <= in;
		else
			out <= {out[0], out[87:1]};
	end
endmodule
