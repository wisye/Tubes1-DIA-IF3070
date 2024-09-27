#include "cube.h"

void init_cube(Cube *cube){
	uint8_t value = 1;
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			for(int k = 0; k < SIZE; k++){
				cube->blocks[i][j][k].value = value++;
			}
		}
	}
	shuffle_cube(cube);
}

void display_cube(Cube *cube){
	for(int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for(int k = 0; k < SIZE; k++){
				printf("%d ", cube->blocks[i][j][k].value);
			}
			printf("\n");
		}
		printf("\n\n");
	}
}

void shuffle(uint8_t *array, size_t n){
	if(n > 1){
		for(size_t i = 0; i < n - 1; i++){
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			uint8_t t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
	}
}

void shuffle_cube(Cube *cube){
	srand(time(NULL));

	uint8_t flat_array[SIZE * SIZE * SIZE];
	size_t index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				flat_array[index++] = cube->blocks[i][j][k].value;
			}
		}
	}

	shuffle(flat_array, SIZE * SIZE * SIZE);

	index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				cube->blocks[i][j][k].value = flat_array[index++];
			}
		}
	}
}