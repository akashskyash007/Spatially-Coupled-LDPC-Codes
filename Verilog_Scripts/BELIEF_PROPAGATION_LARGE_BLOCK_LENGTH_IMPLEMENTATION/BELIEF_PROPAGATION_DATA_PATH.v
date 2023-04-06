//Data Path of Module to Implement Layered Decoding of LDPC Codes

`timescale 1ns/1ps

module BELIEF_PROPAGATION_DATA_PATH(clk, start_row_processing, done_row_processing, initialize_storage_matrix, load_storage_matrix, select_input_to_storage_matrix, reset_main_counter, increment_main_counter, reset_layer_indicator_counter, increment_layer_indicator_counter, done_iterations, received_vector);
	
	input clk, start_row_processing, initialize_storage_matrix;
	input load_storage_matrix, load_sum_vector;
	input select_input_to_storage_matrix, reset_main_counter;
	input increment_main_counter, reset_layer_indicator_counter;
	input increment_layer_indicator_counter, reset_layer_counter;
	
	input[3520 * 32 - 1 : 0] received_vector;

	output done_row_processing, done_iterations;

	wire[3:0] main_counter;
	wire[4:0] layer_indicator_counter_out;
	wire done_all_layers;
	
	reg[31:0] storage_matrix[0:15][0:3519];
	reg[31:0] curr_layer_input[0:3519];
	reg[31:0] curr_layer_input_negated[0:3519];
	reg[31:0] curr_layer_difference_result[0:3519];
	reg[31:0] curr_layer_output[0:3519];
	reg[6:0] base_matrix[0:15][0:39];
	reg[31:0] sum_vector[0:3519];

	integer i, j, lcv1;

	assign done_iterations = (main_counter == 4'b1010);
	assign done_all_layers = (layer_indicator_counter_out == 16);

	BELIEF_PROPAGATION_DATA_PATH_UP_COUNTER iteration_indicator(clk, increment_main_counter, reset_main_counter, main_counter);
	BELIEF_PROPAGATION_DATA_PATH_LAYER_INDICATOR_COUNTER layer_indicator(clk, increment_layer_indicator_counter, reset_layer_indicator_counter, layer_indicator_counter_out);

	genvar diff_generator;
	generate for (diff_generator = 0; diff_generator < 3520; diff_generator = diff_generator + 1) 
		begin
			FLOATING_POINT_ADDER_DATA_PATH difference_calculator_instance(sum_vector[diff_generator], curr_layer_input_negated[diff_generator], curr_layer_difference_result[diff_generator])
		end
	endgenerate

	always @(posedge clk) begin
		if (initialize_storage_matrix) begin
			for (i = 0; i < 16; i++) begin
				for (j = 0; j < 3520; j++) begin
					storage_matrix[i][j] = 32'b0;
				end
			end
			for (i = 0; i < 3520; i++) begin
				j = i * 32 + 32 - 1;
				lcv1 = i * 32;
				sum_vector[i] = received_vector[j:lcv1];
			end
		end
		else if (load_storage_matrix) begin
			storage_matrix[layer_indicator] = curr_layer_output;
		end
	end

	always @(*) begin
		for (lcv1 = 0; lcv1 < 3520; lcv1++) begin
			curr_layer_input_negated[lcv1][31] = ~curr_layer_input[lcv1][31];
		       curr_layer_input_negated[lcv1][30:0] = curr_layer_input[lcv1][30:0];	
		end
	end

endmodule
