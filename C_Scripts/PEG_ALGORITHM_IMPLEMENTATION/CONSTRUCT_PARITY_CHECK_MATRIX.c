#include <stdio.h>
#include <stdlib.h>

//Function to Sort Check Nodes in Ascending Order of Degree
void sort_check_nodes_by_degree(int* arr1, int* arr2, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr2[j] > arr2[j + 1]) {
				int temp = arr2[j];
				arr2[j] = arr2[j + 1];
				arr2[j + 1] = temp;
				temp = arr1[j];
				arr1[j] = arr1[j + 1];
				arr1[j + 1] = temp;
			}
		}
	}
}

//Function to Implement PEG Algorithm
void construct_parity_check_matrix(int J, int K, int EXPANSION_FACTOR) {
	int num_rows = J * EXPANSION_FACTOR;	//Number of rows in parity check matrix
	int num_columns = K * EXPANSION_FACTOR;	//Number of columns in parity check matrix
	
	//Initialize Parity Check Matrix with all zeros
	int H[num_rows][num_columns];
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			H[i][j] = 0;
		}
	}

	//Outer loop to add edges to each bit node
	for (int i = 0; i < K; i++) {
		int current_bit_node = i * EXPANSION_FACTOR;
		
		int check_node_degrees[num_rows];
		int check_nodes[num_rows];
		for (int j = 0; j < num_rows; j++) {
			check_node_degrees[j] = 0;
		}
		for (int j = 0; j < num_rows; j++) {
			check_nodes[j] = j;
		}
		for (int j = 0; j < num_rows; j++) {
			for (int k = 0; k < num_columns; k++) {
				check_node_degrees[j] += H[j][k];
			}
		}
		sort_check_nodes_by_degree(check_nodes, check_node_degrees, num_rows);

		//Loop to Assign Edges within a single bit node
		int check_node_position_for_first_iteration = 0;
		for (int j = 0; j < J; j++) {
			if (j == 0) {
				int connected_check_node = check_nodes[check_node_position_for_first_iteration % EXPANSION_FACTOR];
				for (int k = 0; k < EXPANSION_FACTOR; k++) {
					H[(connected_check_node + k) % EXPANSION_FACTOR + EXPANSION_FACTOR * (connected_check_node/EXPANSION_FACTOR)][current_bit_node + k] = 1;
				}
			}
			else {
				int computation_tree_check_node_present_status[num_rows];
				int computation_tree_check_node_next_status[num_rows];
				int computation_tree_bit_node_present_status[num_columns];
				int computation_tree_bit_node_next_status[num_columns];
				for (int k = 0; k < num_rows; k++) {
					computation_tree_check_node_present_status[k] = 0;
					computation_tree_check_node_next_status[k] = 0;
				}
				for (int k = 0; k < num_columns; k++) {
					computation_tree_bit_node_present_status[k] = 0;
					computation_tree_bit_node_next_status[k] = 0;
				}
				int stop_expanding_computation_tree = 0;
				computation_tree_bit_node_present_status[current_bit_node] = 1;
				computation_tree_bit_node_next_status[current_bit_node] = 1;
				while (!stop_expanding_computation_tree) {
					for (int k = 0; k < num_columns; k++) {
						if (computation_tree_bit_node_present_status[k] == 1) {
							for (int l = 0; l < num_rows; l++) {
								if (H[l][k] == 1) {
									computation_tree_check_node_present_status[l] = 1;
									computation_tree_check_node_next_status[l] = 1;
								}
							}
						}
					}
					for (int k = 0; k < num_rows; k++) {
						if (computation_tree_check_node_present_status[k] == 1) {
							for (int l = 0; l < num_columns; l++) {
								if (H[k][l] == 1) {
									computation_tree_bit_node_present_status[l] = 1;
									computation_tree_bit_node_next_status[l] = 1;
								}
							}
						}
					}
					for (int k = 0; k < num_columns; k++) {
						if (computation_tree_bit_node_next_status[k] == 1) {
							for (int l = 0; l < num_rows; l++) {
								if (H[l][k] == 1) {
									computation_tree_check_node_next_status[l] = 1;
								}
							}
						}
					}
					int present_status_number_of_check_nodes = 0;
					int next_status_number_of_check_nodes = 0;
					for (int k = 0; k < num_rows; k++) {
						if (computation_tree_check_node_present_status[k] == 1) {
							present_status_number_of_check_nodes++;
						}
						if (computation_tree_check_node_next_status[k] == 1) {
							next_status_number_of_check_nodes++;
						}
					}
					if (present_status_number_of_check_nodes == next_status_number_of_check_nodes || next_status_number_of_check_nodes == num_rows) {
						stop_expanding_computation_tree = 1;
					}
				}
				int num_unused_check_nodes = 0;
				for (int k = 0; k < num_rows; k++) {
					if (computation_tree_check_node_present_status[k] == 0 && (k >= j * EXPANSION_FACTOR && k < (j + 1) * EXPANSION_FACTOR)) {
						num_unused_check_nodes++;
					}
				}
				if (num_unused_check_nodes == 0 && check_node_position_for_first_iteration < EXPANSION_FACTOR) {
					j = -1;
					for (int k = 0; k < num_rows; k++) {
						for (int l = current_bit_node; l < current_bit_node + EXPANSION_FACTOR; l++) {
							H[k][l] = 0;
						}
					}
					check_node_position_for_first_iteration++;
				}
				else {
					int candidate_check_nodes[num_unused_check_nodes];
					int candidate_check_node_degrees[num_unused_check_nodes];
					int count = 0;
					for (int k = 0; k < num_rows; k++) {
						if (computation_tree_check_node_present_status[k] == 0 && (k >= j * EXPANSION_FACTOR && k < (j + 1) * EXPANSION_FACTOR)) {
							candidate_check_nodes[count] = k;
							candidate_check_node_degrees[count] = 0;
							for (int l = 0; l < num_columns; l++) {
								if (H[candidate_check_nodes[count]][l] == 1) {
									candidate_check_node_degrees[count]++;
								}
							}	
							count++;
						}
					}
					sort_check_nodes_by_degree(candidate_check_nodes, candidate_check_node_degrees, num_unused_check_nodes);
					printf("Candidate Check Nodes: ");
					for (int k = 0; k < num_unused_check_nodes; k++) {
						printf("%d ", candidate_check_nodes[k]);
					}
					printf("\n");
					if (candidate_check_node_degrees[0] >= K && check_node_position_for_first_iteration < EXPANSION_FACTOR) {
						j = -1;
						for (int k = 0; k < num_rows; k++) {
							for (int l = current_bit_node; l < current_bit_node + EXPANSION_FACTOR; l++) {
								H[k][l] = 0;
							}
						}
						check_node_position_for_first_iteration++;	
					}
					else {
						int selected_check_node;
						if (num_unused_check_nodes == 0) {
							selected_check_node = j * EXPANSION_FACTOR;
						}
						else {
							selected_check_node = candidate_check_nodes[0];
						}
						for (int k = 0; k < EXPANSION_FACTOR; k++) {
							H[(selected_check_node + k) % EXPANSION_FACTOR + EXPANSION_FACTOR * (selected_check_node/EXPANSION_FACTOR)][current_bit_node + k] = 1;
						}
					}
				}
			}
			printf("Parity Check Matrix:\n");
			for (int k = 0; k < num_rows; k++) {
				for (int l = 0; l < num_columns; l++) {
					printf("%d ", H[k][l]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}
}

//Main Function that defines the code parameters
int main(void) {
	int J = 2; //Number of Block Rows
	int K = 3; //Number of Block Columns
	int EXPANSION_FACTOR = 2;     //Expansion Factor
	construct_parity_check_matrix(J, K, EXPANSION_FACTOR);
	return 0;
}
