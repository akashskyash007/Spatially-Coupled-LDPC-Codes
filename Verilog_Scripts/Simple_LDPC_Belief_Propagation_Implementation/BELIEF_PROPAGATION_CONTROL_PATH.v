//Control Path for Belief Propagation

`timescale 1ns/1ps

module BELIEF_PROPAGATION_CONTROL_PATH(clk, start, done, start_row_processing, start_column_processing, done_row_processing_row_1, done_row_processing_row_2, done_row_processing_row_3, done_column_processing_column_1, done_column_processing_column_2, done_column_processing_column_3, done_column_processing_column_4, done_column_processing_column_5, done_column_processing_column_6, initialize_parity_check_matrix, load_parity_check_matrix, load_sum_vector, select_input_to_parity_check_matrix, reset_count, increment_count, done_iterations);
	input clk, start;
	input done_row_processing_row_1, done_row_processing_row_2, done_row_processing_row_3;
	input done_column_processing_column_1, done_column_processing_column_2, done_column_processing_column_3;
	input done_column_processing_column_4, done_column_processing_column_5, done_column_processing_column_6;
	input done_iterations;
	output reg done;
	output reg start_row_processing, start_column_processing;
	output reg initialize_parity_check_matrix, load_parity_check_matrix, load_sum_vector;
	output reg select_input_to_parity_check_matrix, reset_count, increment_count;

	reg[3:0] PS, NS;
	wire done_row_processing, done_column_processing;

	parameter S0 = 0, S1 = 1, S2 = 2, S3 = 3, S4 = 4, S5 = 5, S6 = 6, S7 = 7, S8 = 8, S9 = 9;

	assign done_row_processing = done_row_processing_row_1 & done_row_processing_row_2 & done_row_processing_row_3;
	assign done_column_processing = done_column_processing_column_1 & done_column_processing_column_2 & done_column_processing_column_3 & done_column_processing_column_4 & done_column_processing_column_5 & done_column_processing_column_6;
	
	always @(posedge clk) begin
		PS <= NS;
	end

	always @(*) begin
		case (PS) 
			S0: begin
				#2 if (start) begin
					NS = S1;
					initialize_parity_check_matrix = 1'b1; reset_count = 1'b1;
				end
			end
			S1: begin
				#2 NS = S2;
				initialize_parity_check_matrix = 1'b0; reset_count = 1'b0;
				start_row_processing = 1'b1;
			end
			S2: begin
				#2 NS = S3;
				start_row_processing = 1'b0;
			end
			S3: begin
				#2 if (done_row_processing) begin
					NS = S4;
					load_parity_check_matrix = 1'b1;
				end
			end
			S4: begin
				#2 NS = S5;
				load_parity_check_matrix = 1'b0;
				start_column_processing = 1'b1;
			end
			S5: begin
				#2 NS = S6;
				start_column_processing = 1'b0;
			end
			S6: begin
				#2 if (done_column_processing) begin
					NS = S7;
					load_sum_vector = 1'b1;
				end
			end
			S7: begin
				#2 NS = S8;
				load_sum_vector = 1'b0;
				load_parity_check_matrix = 1'b1; increment_count = 1'b1; select_input_to_parity_check_matrix = 1'b1;
			end
			S8: begin
				#2 if (done_iterations) begin
					NS = S9;
					load_parity_check_matrix = 1'b0; increment_count = 1'b0; select_input_to_parity_check_matrix = 1'b0; done = 1'b1;
				end
				else begin
					NS = S2;
					load_parity_check_matrix = 1'b0; increment_count = 1'b0; select_input_to_parity_check_matrix = 1'b0;
					start_row_processing = 1'b1;
				end
			end
			S9: begin
				#2 NS = S9;
			end
			default: begin
				NS = S0;
				done = 1'b0; start_row_processing = 1'b0; start_column_processing = 1'b0; initialize_parity_check_matrix = 1'b0;
				load_parity_check_matrix = 1'b0; load_sum_vector = 1'b0; select_input_to_parity_check_matrix = 1'b0;
				reset_count = 1'b0; increment_count = 1'b0;
			end
		endcase
	end
endmodule
