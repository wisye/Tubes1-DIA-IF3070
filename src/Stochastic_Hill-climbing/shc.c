#include "shc.h"
#include <stdbool.h>

void shc(Cube *cube) {
	int h_current, h_new;
	uint8_t u1, u2;
	int iterations = 0;
	int MAX_ITERATIONS = 10000;

	uint8_t *linear_cube[TOTAL_VALUES];
	int index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				linear_cube[index++] = &cube->blocks[i][j][k].value;
			}
		}
	}

	h_current = calculate_heuristics(cube);

	for (int i = 0; i < MAX_ITERATIONS; i++) {

		u1 = rand() % TOTAL_VALUES;
		u2 = rand() % TOTAL_VALUES;

		while (u1 == u2) {
			u2 = rand() % TOTAL_VALUES;
		}
		swap(linear_cube[u1], linear_cube[u2]);

		h_new = calculate_heuristics(cube);

		if (h_new > h_current) {
			h_current = h_new;
		}
		else {
			swap(linear_cube[u1], linear_cube[u2]);
		}

		iterations++;
		unflatten_cube2(linear_cube);
		drawCube(cube);
		printf("Iteration %d: Improved heuristic to %d\n", iterations, h_current);

		if (h_current == TOTAL_EDGES) {
			printf("Found a magic cube!\n");
			break;
		}
	}
}