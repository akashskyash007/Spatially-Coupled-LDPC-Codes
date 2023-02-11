module FLOATING_POINT_ADDER_LEADING_ZEROS_COUNTER(out, all_zeros, in);
	input[23:0] in;
	output reg[4:0] out;
	output all_zeros;
	
	wire[4:0] priority_encoder_output;
	reg[4:0] storage_register;

	assign all_zeros = (out == 5'b11000);

	FLOATING_POINT_ADDER_PRIORITY_ENCODER find_position_of_first_1(in, priority_encoder_output);

	always @(*) begin
		storage_register = 5'b11000;
		out = storage_register - priority_encoder_output;
	end
endmodule
