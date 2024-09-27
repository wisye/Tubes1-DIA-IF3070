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

	uint8_t flat_array[TOTAL_VALUES];
	size_t index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				flat_array[index++] = cube->blocks[i][j][k].value;
			}
		}
	}

	shuffle(flat_array, TOTAL_VALUES);

	index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				cube->blocks[i][j][k].value = flat_array[index++];
			}
		}
	}
}

bool check_cube(Cube *cube) {
	int magic_sum = 0;
	for(int i = 0; i < SIZE; i++){
		magic_sum += cube->blocks[0][0][i].value;
	}

	// Check rows
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			int row_sum = 0;
			for(int k = 0; k < SIZE; k++){
				row_sum += cube->blocks[i][j][k].value;
			}
			if(row_sum != magic_sum) return false;
		}
	}

	// Check columns
	for(int i = 0; i < SIZE; i++){
		for(int k = 0; k < SIZE; k++){
			int col_sum = 0;
			for(int j = 0; j < SIZE; j++){
				col_sum += cube->blocks[i][j][k].value;
			}
			if(col_sum != magic_sum) return false;
		}
	}

	// Check depths
	for(int j = 0; j < SIZE; j++){
		for(int k = 0; k < SIZE; k++){
			int depth_sum = 0;
			for(int i = 0; i < SIZE; i++){
				depth_sum += cube->blocks[i][j][k].value;
			}
			if(depth_sum != magic_sum) return false;
		}
	}

	// Check main diagonals in each plane
	for(int i = 0; i < SIZE; i++){
		int diag1_sum = 0, diag2_sum = 0;
		for(int j = 0; j < SIZE; j++){
			diag1_sum += cube->blocks[i][j][j].value;
			diag2_sum += cube->blocks[i][j][SIZE - j - 1].value;
		}
		if(diag1_sum != magic_sum || diag2_sum != magic_sum) return false;
	}

	for(int j = 0; j < SIZE; j++){
		int diag1_sum = 0, diag2_sum = 0;
		for(int i = 0; i < SIZE; i++){
			diag1_sum += cube->blocks[i][j][i].value;
			diag2_sum += cube->blocks[i][j][SIZE - i - 1].value;
		}
		if(diag1_sum != magic_sum || diag2_sum != magic_sum) return false;
	}

	for(int k = 0; k < SIZE; k++){
		int diag1_sum = 0, diag2_sum = 0;
		for(int i = 0; i < SIZE; i++){
			diag1_sum += cube->blocks[i][i][k].value;
			diag2_sum += cube->blocks[i][SIZE - i - 1][k].value;
		}
		if(diag1_sum != magic_sum || diag2_sum != magic_sum) return false;
	}

	// Check space diagonals
	// int space_diag1_sum = 0, space_diag2_sum = 0, space_diag3_sum = 0, space_diag4_sum = 0;
	// for(int i = 0; i < SIZE; i++){
	// 	space_diag1_sum += cube->blocks[i][i][i].value;
	// 	space_diag2_sum += cube->blocks[i][i][SIZE - i - 1].value;
	// 	space_diag3_sum += cube->blocks[i][SIZE - i - 1][i].value;
	// 	space_diag4_sum += cube->blocks[SIZE - i - 1][i][i].value;
	// }
	// if(space_diag1_sum != magic_sum || space_diag2_sum != magic_sum || space_diag3_sum != magic_sum || space_diag4_sum != magic_sum) return false;

	return true;
}