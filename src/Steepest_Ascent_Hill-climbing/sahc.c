#include "sahc.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

void sahc(Cube *cube) {

	FILE *file = fopen("src/results/sahc_result.csv", "w");

	if (file == NULL) {
		perror("Unable to open file");
		return;
	}

	fprintf(file, "Iteration,Heuristic Value,Time\n");

	int h_current, h_best, h_new;
	uint8_t u1, u2;           //? buat nandaian swap
	uint8_t best_u1, best_u2; //? untuk nyimpan nilai swap terbaik

	int improved = true; //? buat ngecek ada improvmenet ato ga (dan buat loop)
	int iterations = 0;

	//? inisialisasi linear_cube. INI SUPAYA NANTI NGE SWAP GAMPANG, GA
	//? PERLU NESTED LOOP
	uint8_t *linear_cube[TOTAL_VALUES];
	int index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				linear_cube[index++] = &cube->blocks[i][j][k].value;
			}
		}
	}
	clock_t start_time = clock();
	clock_t end_time;
	double elapsed_time;
	h_current = calculate_heuristics(cube);
	while (improved && h_current < TOTAL_EDGES) {
		improved = false;
		h_best = h_current;

		for (u1 = 0; u1 < TOTAL_VALUES - 1; u1++) {
			for (u2 = u1 + 1; u2 < TOTAL_VALUES; u2++) {
				//? swap
				swap(linear_cube[u1], linear_cube[u2]);
				//? hitung heuristics
				h_new = calculate_heuristics(cube);

				//? kalo heuristicsny lebih bagus, update h_best
				if (h_new > h_best) {
					h_best = h_new;
					best_u1 = u1;
					best_u2 = u2;
					improved = true;
				}

				//? swap balik
				swap(linear_cube[u1], linear_cube[u2]);
			}
		}

		iterations++;
		if (improved) {
			//? swap ke best swap
			swap(linear_cube[best_u1], linear_cube[best_u2]);
			h_current = h_best;
			unflatten_cube2(linear_cube);
			printf("Iteration %d: Improved heuristic to %d\n", iterations, h_current);

			if (h_current == TOTAL_EDGES) {
				printf("Found a magic cube!\n");
				break;
			}
		}
		else {
			printf("Stopped at iteration %d\n", iterations);
			printf("Local maximum found with h = %d\n", h_current);
		}
		end_time = clock();
		elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
		fprintf(file, "%d,%d,%.4f\n", iterations, h_current, elapsed_time);
	}

	fclose(file);
}