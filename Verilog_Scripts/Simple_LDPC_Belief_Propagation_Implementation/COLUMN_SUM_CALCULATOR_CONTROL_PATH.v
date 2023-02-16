//Control Path of Module to Calculate Column Sum

`timescale 1ns/1ps

module COLUMN_SUM_CALCULATOR_CONTROL_PATH(clk, done, start, clr, done_iterations, load_sum);
	input clk, start, done_iterations;
	output reg done, clr;
	output reg load_sum;

	parameter S0 = 0, S1 = 1, S2 = 2, S3 = 3;

	reg[1:0] present_state, next_state;

	always @(posedge clk)
		present_state <= next_state;

	always @(*) begin
		case (present_state)
			S0: begin
				#2 if (start) begin
					next_state = S1; 
					clr = 1'b1;
				end
			end
			S1: begin
				#2 next_state = S2;
				clr = 1'b0;
				load_sum = 1'b1;
			end
			S2: begin
				#2 if (done_iterations) begin
					next_state = S3;
					done = 1'b1;
				end
			end
			S3: begin
				#2 next_state = S0;
				done = 1'b0; clr = 1'b0;
				load_sum = 1'b0;
			end
			default: begin
				#2 next_state = S0;
				clr = 1'b0; done = 1'b0;
				load_sum = 1'b0;
			end
		endcase
	end
endmodule
