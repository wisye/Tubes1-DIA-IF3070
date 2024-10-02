#include "rrhc.h"
#include <stdbool.h>

void rrhc(Cube *cube) {
	int h_current, h_best, h_new;
	uint8_t u1, u2;           //? buat nandaian swap
	uint8_t best_u1, best_u2; //? untuk nyimpan nilai swap terbaik

	int improved = true;
	int iterations = 0;
	int restarted = 0;

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
	bool reached_local_maximum = false;
	int total_sideways = 0;

	while ((improved || reached_local_maximum) && h_current < TOTAL_EDGES && restarted < 10) {

		if (reached_local_maximum == true) {
			shuffle_cube(cube);
			restarted++;
			h_current = calculate_heuristics(cube);
			reached_local_maximum = false;
			printf("Restarted %d\n", restarted);
		}

		improved = false;
		h_best = h_current;

		for (u1 = 0; u1 < TOTAL_VALUES - 1; u1++) {

			for (u2 = u1 + 1; u2 < TOTAL_VALUES; u2++) {

				swap(linear_cube[u1], linear_cube[u2]);

				h_new = calculate_heuristics(cube);

				//? kalo heuristicsny lebih bagus, update h_best
				if (h_new > h_best) {
					h_best = h_new;
					best_u1 = u1;
					best_u2 = u2;
					improved = true;
				}
				else if (h_new == h_best && total_sideways < 2000) {
					total_sideways++;
					h_best = h_new;
					best_u1 = u1;
					best_u2 = u2;
					improved = true;
				}

				//? swap balik
				swap(linear_cube[u1], linear_cube[u2]);
			}
		}

		if (improved) {
			//? swap ke best swap
			swap(linear_cube[best_u1], linear_cube[best_u2]);
			h_current = h_best;
			iterations++;
			unflatten_cube2(linear_cube);
			drawCube(cube);
			printf("Iteration %d: Improved heuristic to %d\n", iterations, h_current);

			if (h_current == TOTAL_EDGES) {
				printf("Found a magic cube!\n");
				break;
			}
		}
		else {
			printf("Stopped at iteration %d\n", iterations);
			printf("Local maximum found with h = %d\n", h_current);
			reached_local_maximum = true;
			printf("Restarting...\n");
			// break;
		}
	}
}