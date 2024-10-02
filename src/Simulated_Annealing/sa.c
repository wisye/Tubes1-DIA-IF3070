#include "sa.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

double schedule1(int iterations, double temperature_0, double cooling_rate) {

	double new_t = temperature_0 * pow(cooling_rate, iterations);

	return new_t;
}

void sa(Cube *cube) {
	int h_current, h_new;
	uint8_t u1, u2;
	int iterations = 1;
	int MAX_ITERATIONS = 100000000;

	double initial_temperature = 1000.0;
	double temperature;
	double cooling_rate = 0.999999;

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

	for (iterations = 1; iterations < MAX_ITERATIONS; iterations++) {

		temperature = schedule1(iterations, initial_temperature, cooling_rate);

		if (temperature < 1e-6) {
			printf("Near 0 (harusnya 0 sih cman sigh)\n");
			break;
		}
		// if (temperature == 0) {
		// 	printf("Harusya make ini supaya ngikutin kalo 0 stop. masalahny ini bakal lama banget wkkw\n");
		// 	break;
		// }

		u1 = rand() % TOTAL_VALUES;
		u2 = rand() % TOTAL_VALUES;

		while (u1 == u2) {
			u2 = rand() % TOTAL_VALUES;
		}

		swap(linear_cube[u1], linear_cube[u2]);

		h_new = calculate_heuristics(cube);

		int delta_h = h_new - h_current;

		if (delta_h > 0) {

			h_current = h_new;
		}
		else {

			double probability = exp(delta_h / temperature);

			//? bawah kalo misal si prob dingin gajelasny dipilih
			if (rand() / (double)RAND_MAX < probability) {

				h_current = h_new;
			}

			else {

				swap(linear_cube[u1], linear_cube[u2]); //? ini kalo ga jdi ya ke default
			}
		}

		iterations++;
		printf("Iteration %d: Heuristic value: %d, Temperature: %f\n", iterations, h_current, temperature);

		if (h_current == TOTAL_EDGES) {
			printf("Found a magic cube!\n");
			break;
		}
	}
}
