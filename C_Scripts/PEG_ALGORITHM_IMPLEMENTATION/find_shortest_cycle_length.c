#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Implementing the Queue Data Structure
typedef struct Queue {
	int val;
	struct Queue* next;
} node;
node* front;
node* rear;

//Function to Create New Queue
void createNewQueue() {
	front = NULL;
	rear = NULL;
}

//Function to Push Elements into the Queue
void push(int val) {
	node* new_node = (node*)(malloc(sizeof(node)));
	new_node->val = val;
	new_node->next = NULL;
	if (front == NULL) {
		front = rear = new_node;
	}
	else {
		rear->next = new_node;
		rear = new_node;
	}
	node* temp = front;
}

//Function to Pop Elements from the Queue
int pop() {
	int ret;
	if (front == rear) {
		ret = front->val;
		front = rear = NULL;
	}
	else {
		node* temp = front;
		front = front->next;
		ret = temp->val;
		temp->next = NULL;
		free(temp);
	}
	return ret;
}

//Function to Check if Queue is Empty
int isEmpty() {
	if (front == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

//Function to Display Elements in the Queue
void display() {
	node* temp = front;
	while (temp != NULL) {
		printf("%d -> ", temp->val);
		temp = temp->next;
	}
	printf("END\n");
}

//Implementation of Graph
typedef struct Graph {
	int value;
	struct Graph* next;
} listNode;

void AddEdge(listNode* AdjacencyList[], int vertex1, int vertex2) {
	if (AdjacencyList[vertex1] == NULL) {
		AdjacencyList[vertex1] = (listNode*)(malloc(sizeof(listNode)));
		AdjacencyList[vertex1]->value = vertex2;
		AdjacencyList[vertex1]->next = NULL;
	}
	else {
		listNode* temp = AdjacencyList[vertex1];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = (listNode*)(malloc(sizeof(listNode)));
		temp = temp->next;
		temp->value = vertex2;
		temp->next = NULL;
	}
	if (AdjacencyList[vertex2] == NULL) {
		AdjacencyList[vertex2] = (listNode*)(malloc(sizeof(listNode)));
		AdjacencyList[vertex2]->value = vertex1;
		AdjacencyList[vertex2]->next = NULL;
	}
	else {
		listNode* temp = AdjacencyList[vertex2];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = (listNode*)(malloc(sizeof(listNode)));
		temp = temp->next;
		temp->value = vertex1;
		temp->next = NULL;
	}
}

//Function to Calculate Minimum of Two Numbers
int min(int x1, int x2) {
	return x1 < x2 ? x1 : x2;
}

//Function to Find the Length of Smallest Cycle
int find_shortest_cycle_length(listNode* AdjacencyList[], int n) {
	int ans = INT_MAX;
	for (int i = 0; i < n; i++) {
		int distances[n];
		int parent[n];
		for (int j = 0; j < n; j++) {
			distances[j] = INT_MAX;
		}
		distances[i] = 0;
		createNewQueue();
		push(i);
		while (!isEmpty()) {
			int x = pop();
			listNode* temp = AdjacencyList[x];
			while (temp != NULL) {
				int current_vertex = temp->value;
				if (distances[current_vertex] == INT_MAX) {
					distances[current_vertex] = 1 + distances[x];
					parent[current_vertex] = x;
					push(current_vertex);
				}
				else {
					if (parent[current_vertex] != x && parent[x] != current_vertex) {
						ans = min(ans, distances[x] + distances[current_vertex] + 1);
					}
				}
				temp = temp->next;
			}
		}
	}
	if (ans == INT_MAX) {
		return -1;
	}
	else {
		return ans;
	}
}

//Function to Create Graph
void create_graph_and_calculate_shortest_cycle_length(int J, int K, int EXPANSION_FACTOR) {
	int num_rows = J * EXPANSION_FACTOR;
	int num_columns = K * EXPANSION_FACTOR;
	int n = num_rows + num_columns;
	listNode* AdjacencyList[n];
	for (int i = 0; i < n; i++) {
		AdjacencyList[i] = NULL;
	}
	FILE* fptr;
	fptr = fopen("generated_H_matrix.txt", "r");
	int H[num_rows][num_columns];
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			char ch = fgetc(fptr);
			H[i][j] = ch - 48;
			ch = fgetc(fptr);
		}
		char ch = fgetc(fptr);
	}
	for (int i = 0; i < num_rows; i++) {
		int curr_check_node = i;
		for (int j = 0; j < num_columns; j++) {
			if (H[i][j] == 1) {
				int curr_bit_node = j;
				AddEdge(AdjacencyList, curr_check_node, curr_bit_node + num_rows);
			}
		}
	}
	int shortest_cycle_length = find_shortest_cycle_length(AdjacencyList, n);
	printf("Length of Shortest Cycle = %d\n", shortest_cycle_length);
}

//Main Function
int main(void) {
	int J = 8;
	int K = 64;
	int EXPANSION_FACTOR = 56;
	create_graph_and_calculate_shortest_cycle_length(J, K, EXPANSION_FACTOR);
	return 0;
}
