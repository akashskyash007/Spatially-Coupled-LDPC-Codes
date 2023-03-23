//Modelling the Control Path of QCLDPC Encoder

`timescale 1ns/1ps

module QC_LDPC_ENCODER_CONTROL_PATH(clk, clear_7bit_counter, clear_6bit_counter, increment_6bit_counter, load_SRAA_shift_reg, load_SRAA_reg, clear_SRAA, counter_7bit_out, counter_6bit_out, start, done);
	input clk, start;
	input[5:0] counter_6bit_out;
	input[6:0] counter_7bit_out;
	output reg clear_6bit_counter, clear_7bit_counter, load_SRAA_shift_reg, load_SRAA_reg;
	output reg clear_SRAA, increment_6bit_counter, done;

	reg[2:0] PS, NS;

	parameter S0 = 0, S1 = 1, S2 = 2, S3 = 3, S4 = 4, S5 = 5, S6 = 6;

	always @(posedge clk) begin
		PS <= NS;
	end

	always @(*) begin
		case (PS)
			S0: begin
				#2 if (start) begin
					NS = S1;
					clear_6bit_counter = 1; clear_7bit_counter = 1; clear_SRAA = 1; load_SRAA_shift_reg = 1;
				end
			end
			S1: begin
				#2 NS = S2;
				clear_6bit_counter = 0; clear_7bit_counter = 0; clear_SRAA = 0; load_SRAA_shift_reg = 0; load_SRAA_reg = 1;
			end
			S2: begin
				#2 if (counter_6bit_out == 23) begin
					if (counter_7bit_out == 86) begin
						NS = S5;
						increment_6bit_counter = 1;
					end
				end
				else begin
					if (counter_7bit_out == 86) begin
						NS = S3;
						increment_6bit_counter = 1;
					end
				end
			end
			S3: begin
				#2 NS = S4;
				increment_6bit_counter = 0; clear_7bit_counter = 1; load_SRAA_shift_reg = 1;
			end
			S4: begin
				#2 NS = S2;
				load_SRAA_shift_reg = 0; clear_7bit_counter = 0;
			end
			S5: begin
				#2 if (counter_6bit_out == 39) begin
					NS = S6;
					done = 1;
					clear_6bit_counter = 0; clear_7bit_counter = 0; load_SRAA_shift_reg = 0;
				end
				else begin
					load_SRAA_shift_reg = 1; clear_7bit_counter = 1;
				end
			end
			S6: begin
				#2 NS = S6;
				done = 1;
				clear_6bit_counter = 0; clear_7bit_counter = 0; load_SRAA_shift_reg = 0; load_SRAA_reg = 0;
				clear_SRAA = 0; increment_6bit_counter = 0;
			end
			default: begin
				#2 NS = S0;
				clear_6bit_counter = 0; clear_7bit_counter = 0; load_SRAA_shift_reg = 0; load_SRAA_reg = 0;
				clear_SRAA = 0; increment_6bit_counter = 0; done = 0;
			end
		endcase
	end
endmodule
