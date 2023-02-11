//24 - Bit Priority Encoder

`timescale 1ns/1ps

module FLOATING_POINT_ADDER_PRIORITY_ENCODER(in, out);
	input[23:0] in;
	output reg[4:0] out;
	
	always @(*) begin
		if (in[23] == 1'b1)
			out = 5'b11000;
		else if (in[22] == 1'b1)
			out = 5'b10111;
		else if (in[21] == 1'b1)
			out = 5'b10110;
		else if (in[20] == 1'b1)
			out = 5'b10101;
		else if (in[19] == 1'b1)
			out = 5'b10100;
		else if (in[18] == 1'b1)
			out = 5'b10011;
		else if (in[17] == 1'b1)
			out = 5'b10010;
		else if (in[16] == 1'b1)
			out = 5'b10001;
		else if (in[15] == 1'b1)
			out = 5'b10000;
		else if (in[14] == 1'b1)
			out = 5'b01111;
		else if (in[13] == 1'b1)
			out = 5'b01110;
		else if (in[12] == 1'b1)
			out = 5'b01101;
		else if (in[11] == 1'b1)
			out = 5'b01100;
		else if (in[10] == 1'b1)
			out = 5'b01011;
		else if (in[9] == 1'b1)
			out = 5'b01010;
		else if (in[8] == 1'b1)
			out = 5'b01001;
		else if (in[7] == 1'b1)
			out = 5'b01000;
		else if (in[6] == 1'b1)
			out = 5'b00111;
		else if (in[5] == 1'b1)
			out = 5'b00110;
		else if (in[4] == 1'b1)
			out = 5'b00101;
		else if (in[3] == 1'b1)
			out = 5'b00100;
		else if (in[2] == 1'b1)
			out = 5'b00011;
		else if (in[1] == 1'b1)
			out = 5'b00010;
		else if (in[0] == 1'b1)
			out = 5'b00001;
		else
			out = 5'b00000;
	end
endmodule
