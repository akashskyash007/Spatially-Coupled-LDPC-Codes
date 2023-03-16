#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void find_primitives(int q) {
	printf("Primitive Roots: ");
	for (int alpha = 1; alpha < q; alpha++) {
		int terminate = 0;
		int curr_value = 1;
		int count = 1;
		int visited[q];
		for (int i = 0; i < q; i++) {
			visited[i] = 0;
		}
		while (!terminate) {
			curr_value = (curr_value * alpha) % q; 
			count++;
			if (visited[curr_value] == 1) {
				terminate = 1;
			}
			else {
				visited[curr_value] = 1;
			}
		}
		int is_primitive = 1;
		for (int i = 1; i < q; i++) {
			if (visited[i] == 0) {
				is_primitive = 0;
			}
		}
		if (is_primitive) {
			printf("%d ", alpha);
		}
	}
	printf("\n");
} 

int main(void) {
	int q = 89;
	find_primitives(q);
	return 0;
}
