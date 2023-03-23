//Modelling a 16 bit 3 to one multiplexer

`timescale 1ns/1ps

module MUX31_16bit(out, in1, in2, in3, sel);
	input[31:0] in1, in2, in3;
	input[1:0] sel;
	output reg[31:0] out;

	always @(*) begin
		if (sel == 2'b00)
			out = in1;
		else if (sel == 2'b01)
			out = in2;
		else if (sel == 2'b10)
			out = in3;
		else
			out = 16'b0;
	end
endmodule
