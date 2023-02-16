//Hardware Modelling of Data Path for Belief Propagation

`timescale 1ns/1ps

module BELIEF_PROPAGATION_DATA_PATH(clk, start_row_processing, start_column_processing, done_row_processing_row_1, done_row_processing_row_2, done_row_processing_row_3, done_column_processing_column_1, done_column_processing_column_2, done_column_processing_column_3, done_column_processing_column_4, done_column_processing_column_5, done_column_processing_column_6, initialize_parity_check_matrix, load_parity_check_matrix, load_sum_vector,select_input_to_parity_check_matrix, reset_count, increment_count, done_iterations, received_vector, sum_vector);
	input clk;
	input start_row_processing, start_column_processing;
	input initialize_parity_check_matrix;
	input load_sum_vector, load_parity_check_matrix;
	input select_input_to_parity_check_matrix;
	input reset_count, increment_count;
	
	output done_row_processing_row_1, done_row_processing_row_2, done_row_processing_row_3;
	output done_column_processing_column_1, done_column_processing_column_2, done_column_processing_column_3, done_column_processing_column_4, done_column_processing_column_5, done_column_processing_column_6;
	output done_iterations;

	input[32 * 6 - 1:0] received_vector;
	output reg[32 * 6 - 1:0] sum_vector;

	reg[31:0] parity_check_matrix[0:2][0:5];
	
	wire[31:0] min_row_1, min_row_2, min_row_3;
	wire[31:0] second_min_row_1, second_min_row_2, second_min_row_3;
	wire[1:0] pos_row_1, pos_row_2, pos_row_3;

	wire[31:0] sum_column_1, sum_column_2, sum_column_3, sum_column_4, sum_column_5, sum_column_6;

	wire[31:0] parity_check_matrix_00_in, parity_check_matrix_04_in, parity_check_matrix_05_in;
	wire[31:0] parity_check_matrix_11_in, parity_check_matrix_13_in, parity_check_matrix_15_in;
	wire[31:0] parity_check_matrix_22_in, parity_check_matrix_23_in, parity_check_matrix_24_in;

	wire[31:0] column_updated_00, column_updated_04, column_updated_05, sign_inverted_00, sign_inverted_04, sign_inverted_05;
	wire[31:0] column_updated_11, column_updated_13, column_updated_15, sign_inverted_11, sign_inverted_13, sign_inverted_15;
	wire[31:0] column_updated_22, column_updated_23, column_updated_24, sign_inverted_22, sign_inverted_23, sign_inverted_24;

	reg[31:0] row_updated_00, row_updated_04, row_updated_05;
	reg[31:0] row_updated_11, row_updated_13, row_updated_15;
	reg[31:0] row_updated_22, row_updated_23, row_updated_24;

	wire row1_sign, row2_sign, row3_sign;

	wire[3:0] count;

	assign row1_sign = ~(parity_check_matrix[0][0][31] ^ parity_check_matrix[0][4][31] ^ parity_check_matrix[0][5][31]);
	assign row2_sign = ~(parity_check_matrix[1][1][31] ^ parity_check_matrix[1][3][31] ^ parity_check_matrix[1][5][31]);
	assign row3_sign = ~(parity_check_matrix[2][2][31] ^ parity_check_matrix[2][3][31] ^ parity_check_matrix[2][4][31]);

	assign sign_inverted_00 = {~parity_check_matrix[0][0][31], parity_check_matrix[0][0][30:0]};
	assign sign_inverted_04 = {~parity_check_matrix[0][4][31], parity_check_matrix[0][4][30:0]};
	assign sign_inverted_05 = {~parity_check_matrix[0][5][31], parity_check_matrix[0][5][30:0]};
	assign sign_inverted_11 = {~parity_check_matrix[1][1][31], parity_check_matrix[1][1][30:0]};
	assign sign_inverted_13 = {~parity_check_matrix[1][3][31], parity_check_matrix[1][3][30:0]};
	assign sign_inverted_15 = {~parity_check_matrix[1][5][31], parity_check_matrix[1][5][30:0]};
	assign sign_inverted_22 = {~parity_check_matrix[2][2][31], parity_check_matrix[2][2][30:0]};
	assign sign_inverted_23 = {~parity_check_matrix[2][3][31], parity_check_matrix[2][3][30:0]};
	assign sign_inverted_24 = {~parity_check_matrix[2][4][31], parity_check_matrix[2][4][30:0]};

	assign done_iterations = (count == 4'b1010);

	minimum_second_minimum_calculator_data_path data_path_row1_processor(clk, done_iterations_row_1, initialize_min_row_1, initialize_second_min_row_1, reset_count_row_1, calculating_second_min_row_1, parity_check_matrix[0][0], parity_check_matrix[0][4], parity_check_matrix[0][5], min_row_1, second_min_row_1, pos_row_1, load_first_min_row_1, load_second_min_row_1);
	minimum_second_minimum_calculator_control_path control_path_row_1_processor(clk, start_row_processing, done_row_processing_row_1, done_iterations_row_1, initialize_min_row_1, initialize_second_min_row_1, reset_count_row_1, calculating_second_min_row_1, load_first_min_row_1, load_second_min_row_1);
	minimum_second_minimum_calculator_data_path data_path_row2_processor(clk, done_iterations_row_2, initialize_min_row_2, initialize_second_min_row_2, reset_count_row_2, calculating_second_min_row_2, parity_check_matrix[1][1], parity_check_matrix[1][3], parity_check_matrix[1][5], min_row_2, second_min_row_2, pos_row_2, load_first_min_row_2, load_second_min_row_2);
        minimum_second_minimum_calculator_control_path control_path_row_2_processor(clk, start_row_processing, done_row_processing_row_2, done_iterations_row_2, initialize_min_row_2, initialize_second_min_row_2, reset_count_row_2, calculating_second_min_row_2, load_first_min_row_2, load_second_min_row_2);
	minimum_second_minimum_calculator_data_path data_path_row3_processor(clk, done_iterations_row_3, initialize_min_row_3, initialize_second_min_row_3, reset_count_row_3, calculating_second_min_row_3, parity_check_matrix[2][2], parity_check_matrix[2][3], parity_check_matrix[2][4], min_row_3, second_min_row_3, pos_row_3, load_first_min_row_3, load_second_min_row_3);
        minimum_second_minimum_calculator_control_path control_path_row_3_processor(clk, start_row_processing, done_row_processing_row_3, done_iterations_row_3, initialize_min_row_3, initialize_second_min_row_3, reset_count_row_3, calculating_second_min_row_3, load_first_min_row_3, load_second_min_row_3);

	COLUMN_SUM_CALCULATOR_DATA_PATH data_path_column1_processor(clk, clr_column_1, done_iterations_column_1, sum_column_1, parity_check_matrix[0][0], parity_check_matrix[1][0], received_vector[32*6-1:32*5], load_sum);
	COLUMN_SUM_CALCULATOR_CONTROL_PATH control_path_column1_processor(clk, done_column_processing_column_1, start_column_processing, clr_column_1, done_iterations_column_1, load_sum);
        COLUMN_SUM_CALCULATOR_DATA_PATH data_path_column2_processor(clk, clr_column_2, done_iterations_column_2, sum_column_2, parity_check_matrix[0][1], parity_check_matrix[1][1], received_vector[32*5-1:32*4], load_sum);
        COLUMN_SUM_CALCULATOR_CONTROL_PATH control_path_column2_processor(clk, done_column_processing_column_2, start_column_processing, clr_column_2, done_iterations_column_2, load_sum);
        COLUMN_SUM_CALCULATOR_DATA_PATH data_path_column3_processor(clk, clr_column_3, done_iterations_column_3, sum_column_3, parity_check_matrix[0][2], received_vector[32*4-1:32*3], parity_check_matrix[2][2], load_sum);
        COLUMN_SUM_CALCULATOR_CONTROL_PATH control_path_column3_processor(clk, done_column_processing_column_3, start_column_processing, clr_column_3, done_iterations_column_3, load_sum);
        COLUMN_SUM_CALCULATOR_DATA_PATH data_path_column4_processor(clk, clr_column_4, done_iterations_column_4, sum_column_4, received_vector[32*3-1:32*2], parity_check_matrix[1][3], parity_check_matrix[2][3], load_sum);
        COLUMN_SUM_CALCULATOR_CONTROL_PATH control_path_column4_processor(clk, done_column_processing_column_4, start_column_processing, clr_column_4, done_iterations_column_4, load_sum);
        COLUMN_SUM_CALCULATOR_DATA_PATH data_path_column5_processor(clk, clr_column_5, done_iterations_column_5, sum_column_5, parity_check_matrix[0][4], received_vector[32*2-1:32], parity_check_matrix[2][4], load_sum);
        COLUMN_SUM_CALCULATOR_CONTROL_PATH control_path_column5_processor(clk, done_column_processing_column_5, start_column_processing, clr_column_5, done_iterations_column_5, load_sum);
        COLUMN_SUM_CALCULATOR_DATA_PATH data_path_column6_processor(clk, clr_column_6, done_iterations_column_6, sum_column_6, parity_check_matrix[0][5], parity_check_matrix[1][5], received_vector[31:0], load_sum);
        COLUMN_SUM_CALCULATOR_CONTROL_PATH control_path_column6_processor(clk, done_column_processing_column_6, start_column_processing, clr_column_6, done_iterations_column_6, load_sum);

	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_00(sum_column_1, sign_inverted_00, column_updated_00);
	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_04(sum_column_5, sign_inverted_04, column_updated_04);
	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_05(sum_column_6, sign_inverted_05, column_updated_05);
	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_11(sum_column_2, sign_inverted_11, column_updated_11);
	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_13(sum_column_4, sign_inverted_13, column_updated_13);
	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_15(sum_column_6, sign_inverted_15, column_updated_15);
	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_22(sum_column_3, sign_inverted_22, column_updated_22);
	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_23(sum_column_4, sign_inverted_23, column_updated_23);
	FLOATING_POINT_ADDER_DATA_PATH generate_column_updated_24(sum_column_5, sign_inverted_24, column_updated_24);

	BUS_MUX_21 generate_input_00(parity_check_matrix_00_in, row_updated_00, column_updated_00, select_input_to_parity_check_matrix);
	BUS_MUX_21 generate_input_04(parity_check_matrix_04_in, row_updated_04, column_updated_04, select_input_to_parity_check_matrix);
	BUS_MUX_21 generate_input_05(parity_check_matrix_05_in, row_updated_05, column_updated_05, select_input_to_parity_check_matrix);
	BUS_MUX_21 generate_input_11(parity_check_matrix_11_in, row_updated_11, column_updated_11, select_input_to_parity_check_matrix);
	BUS_MUX_21 generate_input_13(parity_check_matrix_13_in, row_updated_13, column_updated_13, select_input_to_parity_check_matrix);
	BUS_MUX_21 generate_input_15(parity_check_matrix_15_in, row_updated_15, column_updated_15, select_input_to_parity_check_matrix);
	BUS_MUX_21 generate_input_22(parity_check_matrix_22_in, row_updated_22, column_updated_22, select_input_to_parity_check_matrix);
	BUS_MUX_21 generate_input_23(parity_check_matrix_23_in, row_updated_23, column_updated_23, select_input_to_parity_check_matrix);
	BUS_MUX_21 generate_input_24(parity_check_matrix_24_in, row_updated_24, column_updated_24, select_input_to_parity_check_matrix);

	BELIEF_PROPAGATION_DATA_PATH_UP_COUNTER count_iterations(clk, increment_count, reset_count, count);

	always @(posedge clk) begin
		if (initialize_parity_check_matrix) begin
			parity_check_matrix[0][0] <= received_vector[32 * 6 - 1: 32 * 5]; parity_check_matrix[1][0] <= 32'b0; parity_check_matrix[2][0] <= 32'b0;
			parity_check_matrix[0][1] <= 32'b0; parity_check_matrix[1][1] <= received_vector[32 * 5 - 1: 32 * 4]; parity_check_matrix[2][1] <= 32'b0;
			parity_check_matrix[0][2] <= 32'b0; parity_check_matrix[1][2] <= 32'b0; parity_check_matrix[2][2] <= received_vector[32 * 4 - 1: 32 * 3];
			parity_check_matrix[0][3] <= 32'b0; parity_check_matrix[1][3] <= received_vector[32 * 3 - 1: 32 * 2]; parity_check_matrix[2][3] <= received_vector[32 * 3 - 1:32 * 2];
			parity_check_matrix[0][4] <= received_vector[32 * 2 - 1: 32]; parity_check_matrix[1][4] <= 32'b0; parity_check_matrix[2][4] <= received_vector[32 * 2 - 1: 32]; 
			parity_check_matrix[0][5] <= received_vector[31:0]; parity_check_matrix[1][5] <= received_vector[31:0]; parity_check_matrix[2][5] <= 32'b0;
		end
		else if (load_parity_check_matrix) begin
			parity_check_matrix[0][0] <= parity_check_matrix_00_in; parity_check_matrix[0][4] <= parity_check_matrix_04_in; parity_check_matrix[0][5] <= parity_check_matrix_05_in;
			parity_check_matrix[1][1] <= parity_check_matrix_11_in; parity_check_matrix[1][3] <= parity_check_matrix_13_in; parity_check_matrix[1][5] <= parity_check_matrix_15_in;
			parity_check_matrix[2][2] <= parity_check_matrix_22_in; parity_check_matrix[2][3] <= parity_check_matrix_23_in; parity_check_matrix[2][4] <= parity_check_matrix_24_in;
		end
		if (load_sum_vector) begin
			sum_vector[32 * 6 - 1: 32 * 5] <= sum_column_1;
			sum_vector[32 * 5 - 1: 32 * 4] <= sum_column_2;
			sum_vector[32 * 4 - 1: 32 * 3] <= sum_column_3;
			sum_vector[32 * 3 - 1: 32 * 2] <= sum_column_4;
			sum_vector[32 * 2 - 1: 32] <= sum_column_5;
			sum_vector[31: 0] <= sum_column_6;
		end
	end

	always @(*) begin
		if (pos_row_1 == 2'b00) begin
			row_updated_00 = second_min_row_1;
			row_updated_04 = min_row_1;
			row_updated_05 = min_row_1;
			row_updated_00[31] = row1_sign ^ parity_check_matrix[0][0][31];
			row_updated_04[31] = row1_sign ^ parity_check_matrix[0][4][31];
			row_updated_05[31] = row1_sign ^ parity_check_matrix[0][5][31];
		end
		else if (pos_row_1 == 2'b01) begin
                        row_updated_00 =  min_row_1;
                        row_updated_04 = second_min_row_1;
                        row_updated_05 = min_row_1;
                        row_updated_00[31] = row1_sign ^ parity_check_matrix[0][0][31];
                        row_updated_04[31] = row1_sign ^ parity_check_matrix[0][4][31];
                        row_updated_05[31] = row1_sign ^ parity_check_matrix[0][5][31];
		end
		else begin
                        row_updated_00 = min_row_1;
                        row_updated_04 = min_row_1;
                        row_updated_05 = second_min_row_1;
                        row_updated_00[31] = row1_sign ^ parity_check_matrix[0][0][31];
                        row_updated_04[31] = row1_sign ^ parity_check_matrix[0][4][31];
                        row_updated_05[31] = row1_sign ^ parity_check_matrix[0][5][31];
		end
                if (pos_row_2 == 2'b00) begin
                        row_updated_11 = second_min_row_2;
                        row_updated_13 = min_row_2;
                        row_updated_15 = min_row_2;
                        row_updated_11[31] = row2_sign ^ parity_check_matrix[1][1][31];
                        row_updated_13[31] = row2_sign ^ parity_check_matrix[1][3][31];
                        row_updated_15[31] = row2_sign ^ parity_check_matrix[1][5][31];
                end
                else if (pos_row_2 == 2'b01) begin
                        row_updated_11 = min_row_2;
                        row_updated_13 = second_min_row_2;
                        row_updated_15 = min_row_2;
                        row_updated_11[31] = row2_sign ^ parity_check_matrix[1][1][31];
                        row_updated_13[31] = row2_sign ^ parity_check_matrix[1][3][31];
                        row_updated_15[31] = row2_sign ^ parity_check_matrix[1][5][31];
                end
                else begin
                        row_updated_11 = min_row_2;
                        row_updated_13 = min_row_2;
                        row_updated_15 = second_min_row_2;
                        row_updated_11[31] = row2_sign ^ parity_check_matrix[1][1][31];
                        row_updated_13[31] = row2_sign ^ parity_check_matrix[1][3][31];
                        row_updated_15[31] = row2_sign ^ parity_check_matrix[1][5][31];
                end
                if (pos_row_3 == 2'b00) begin
                        row_updated_22 = second_min_row_3;
                        row_updated_23 = min_row_3;
                        row_updated_24 = min_row_3;
                        row_updated_22[31] = row3_sign ^ parity_check_matrix[2][2][31];
                        row_updated_23[31] = row3_sign ^ parity_check_matrix[2][3][31];
                        row_updated_24[31] = row3_sign ^ parity_check_matrix[2][4][31];
                end
                else if (pos_row_3 == 2'b01) begin
                        row_updated_22 = min_row_3;
                        row_updated_23 = second_min_row_3;
                        row_updated_24 = min_row_3;
                        row_updated_22[31] = row3_sign ^ parity_check_matrix[2][2][31];
                        row_updated_23[31] = row3_sign ^ parity_check_matrix[2][3][31];
                        row_updated_24[31] = row3_sign ^ parity_check_matrix[2][4][31];
                end
                else begin
                        row_updated_22 = min_row_3;
                        row_updated_23 = min_row_3;
                        row_updated_24 = second_min_row_3;
                        row_updated_22[31] = row3_sign ^ parity_check_matrix[2][2][31];
                        row_updated_23[31] = row3_sign ^ parity_check_matrix[2][3][31];
                        row_updated_24[31] = row3_sign ^ parity_check_matrix[2][4][31];
                end
	end
endmodule
