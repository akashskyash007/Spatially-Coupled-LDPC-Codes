//Control Path for Minimum and Second Minimum Calculator

`timescale 1ns/1ps

module minimum_second_minimum_calculator_control_path(clk, start_row_processing, done_row_processing, done_iterations, initialize_min, initialize_second_min, reset_count, calculating_second_min, load_first_min, load_second_min);
	input clk, start_row_processing, done_iterations;
	output reg done_row_processing, initialize_min, initialize_second_min, reset_count, calculating_second_min, load_first_min, load_second_min;

	parameter S0 = 0, S1 = 1, S2 = 2, S3 = 3, S4 = 4, S5 = 5;

	reg[2:0] present_state, next_state;

	always @(posedge clk) begin
		present_state <= next_state;
	end

	always @(*) begin
		case (present_state)
			S0: begin
				#2 if (start_row_processing) begin
					next_state = S1;
					load_first_min = 1; initialize_min = 1; calculating_second_min = 0; reset_count = 1;
				end
			end
			S1: begin
				#2 next_state = S2;
				initialize_min = 0; reset_count = 0;
			end
			S2: begin
				#2 if (done_iterations) begin
					next_state = S3;
					load_first_min = 0; load_second_min = 1; initialize_second_min = 1; calculating_second_min = 1; reset_count = 1;
				end
			end
			S3: begin
				#2 next_state = S4;
				initialize_second_min = 0; reset_count = 0;
			end
			S4: begin
				#2 if (done_iterations) begin
					next_state = S5;
					load_second_min = 0; done_row_processing = 1;
				end
			end
			S5: begin
				#2 next_state = S0;
				done_row_processing = 0; reset_count = 0; initialize_min = 0; initialize_second_min = 0; calculating_second_min = 0; load_first_min = 0; load_second_min = 0; 
			end
			default: begin
				#2 next_state = S0;
				done_row_processing = 0; reset_count = 0; initialize_min = 0; initialize_second_min = 0; calculating_second_min = 0; load_first_min = 0; load_second_min = 0;
			end
		endcase
	end
endmodule
