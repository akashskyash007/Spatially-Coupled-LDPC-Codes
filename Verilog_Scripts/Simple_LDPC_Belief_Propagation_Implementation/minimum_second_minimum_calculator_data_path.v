//Datapath of Check Node Processor that Calculates Absolute Minimum and Absolute Second Minimum

`timescale 1ns/1ps

module minimum_second_minimum_calculator_data_path(clk, done_iterations, initialize_min, initialize_second_min, reset_count, calculating_second_min, r1, r2, r3, min, second_min, pos, load_first_min, load_second_min);
	input[31:0] r1, r2, r3;
	output[31:0] min, second_min;
	output[1:0] pos;
	input clk, initialize_min, initialize_second_min, reset_count, calculating_second_min, load_first_min, load_second_min;
	output done_iterations;

	wire[31:0] r1_out, r2_out, r3_out;
	wire[31:0] comparator_input_1, comparator_input_2, comparator_out;
	wire[31:0] minimum_out, second_minimum_out;
	wire[1:0] count;
	wire calculating_first_minimum;
	wire load_pos;
	wire l;

	assign r1_out = r1;
	assign r2_out = r2;
	assign r3_out = r3;
	assign done_iterations = (count >= 2'b11);
	assign min = minimum_out;
	assign second_min = second_minimum_out;

	BUS_MUX_31 generate_first_comparator_input(comparator_input_1, r1_out, r2_out, r3_out, count);
	comparator_floating_point generate_comparator_less_than_output(l, comparator_input_1, comparator_input_2);
	BUS_MUX_21 generate_comparator_output(comparator_out, comparator_input_2, comparator_input_1, l);
	MIN_PIPO_REGISTER minimum_register(clk, load_first_min, initialize_min, minimum_out, comparator_out);
	MIN_PIPO_REGISTER second_minimum_register(clk, load_second_min, initialize_second_min, second_minimum_out, comparator_out);
	BUS_MUX_21 generate_second_comparator_input(comparator_input_2, minimum_out, second_minimum_out, calculating_second_min);
	and G2(load_pos, load_first_min, l);
	POS_PIPO_REGISTER pos_register(clk, load_pos, pos, count);
	UP_COUNTER calculate_count(clk, reset_count, calculating_second_min, pos, count);
endmodule
