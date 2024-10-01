#include "cube.h"

void init_cube(Cube *cube) {
	uint8_t value = 1;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				cube->blocks[i][j][k].pos = value - 1;
				cube->blocks[i][j][k].value = value++;
			}
		}
	}
	shuffle_cube(cube);
}

void display_cube(Cube *cube) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				printf("%d ", cube->blocks[i][j][k].value);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void shuffle(Block *array) {
	size_t n = TOTAL_VALUES;
	for (size_t i = 0; i < n - 1; i++) {
		size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
		uint8_t t = array[i].value;
		uint8_t p = array[i].pos;

		array[i].value = array[j].value;
		array[i].pos = array[j].pos;

		array[j].value = t;
		array[j].pos = p;
	}
}

void shuffle_cube(Cube *cube) {
	srand(time(NULL));

	Block *flat_array = flatten_cube(cube);

	shuffle(flat_array);

	uint8_t index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				cube->blocks[i][j][k].value = flat_array[index++].value;
			}
		}
	}
	free(flat_array);
}

bool check_cube(Cube *cube) {
	// Check rows
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int row_sum = 0;
			for (int k = 0; k < SIZE; k++) {
				row_sum += cube->blocks[i][j][k].value;
			}
			if (row_sum != MAGIC_NUMBER) return false;
		}
	}

	// Check columns
	for (int i = 0; i < SIZE; i++) {
		for (int k = 0; k < SIZE; k++) {
			int col_sum = 0;
			for (int j = 0; j < SIZE; j++) {
				col_sum += cube->blocks[i][j][k].value;
			}
			if (col_sum != MAGIC_NUMBER) return false;
		}
	}

	// Check depths
	for (int j = 0; j < SIZE; j++) {
		for (int k = 0; k < SIZE; k++) {
			int depth_sum = 0;
			for (int i = 0; i < SIZE; i++) {
				depth_sum += cube->blocks[i][j][k].value;
			}
			if (depth_sum != MAGIC_NUMBER) return false;
		}
	}

	// Check main diagonals in each plane
	for (int i = 0; i < SIZE; i++) {
		int diag1_sum = 0, diag2_sum = 0;
		for (int j = 0; j < SIZE; j++) {
			diag1_sum += cube->blocks[i][j][j].value;
			diag2_sum += cube->blocks[i][j][SIZE - j - 1].value;
		}
		if (diag1_sum != MAGIC_NUMBER || diag2_sum != MAGIC_NUMBER) return false;
	}

	for (int j = 0; j < SIZE; j++) {
		int diag1_sum = 0, diag2_sum = 0;
		for (int i = 0; i < SIZE; i++) {
			diag1_sum += cube->blocks[i][j][i].value;
			diag2_sum += cube->blocks[i][j][SIZE - i - 1].value;
		}
		if (diag1_sum != MAGIC_NUMBER || diag2_sum != MAGIC_NUMBER) return false;
	}

	for (int k = 0; k < SIZE; k++) {
		int diag1_sum = 0, diag2_sum = 0;
		for (int i = 0; i < SIZE; i++) {
			diag1_sum += cube->blocks[i][i][k].value;
			diag2_sum += cube->blocks[i][SIZE - i - 1][k].value;
		}
		if (diag1_sum != MAGIC_NUMBER || diag2_sum != MAGIC_NUMBER) return false;
	}

	// Check space diagonals
	int space_diag1_sum = 0, space_diag2_sum = 0, space_diag3_sum = 0, space_diag4_sum = 0;
	for (int i = 0; i < SIZE; i++) {
		space_diag1_sum += cube->blocks[i][i][i].value;
		space_diag2_sum += cube->blocks[i][i][SIZE - i - 1].value;
		space_diag3_sum += cube->blocks[i][SIZE - i - 1][i].value;
		space_diag4_sum += cube->blocks[SIZE - i - 1][i][i].value;
	}
	if (space_diag1_sum != MAGIC_NUMBER || space_diag2_sum != MAGIC_NUMBER || space_diag3_sum != MAGIC_NUMBER ||
	    space_diag4_sum != MAGIC_NUMBER)
		return false;

	return true;
}

int calculate_heuristics(Cube *cube) {
	int heuristics = 0;

	// Check rows
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int row_sum = 0;
			for (int k = 0; k < SIZE; k++) {
				row_sum += cube->blocks[i][j][k].value;
			}
			if (row_sum == MAGIC_NUMBER) heuristics++;
		}
	}

	// Check columns
	for (int i = 0; i < SIZE; i++) {
		for (int k = 0; k < SIZE; k++) {
			int col_sum = 0;
			for (int j = 0; j < SIZE; j++) {
				col_sum += cube->blocks[i][j][k].value;
			}
			if (col_sum == MAGIC_NUMBER) heuristics++;
		}
	}

	// Check depths
	for (int j = 0; j < SIZE; j++) {
		for (int k = 0; k < SIZE; k++) {
			int depth_sum = 0;
			for (int i = 0; i < SIZE; i++) {
				depth_sum += cube->blocks[i][j][k].value;
			}
			if (depth_sum == MAGIC_NUMBER) heuristics++;
		}
	}

	// Check main diagonals in each plane
	for (int i = 0; i < SIZE; i++) {
		int diag1_sum = 0, diag2_sum = 0;
		for (int j = 0; j < SIZE; j++) {
			diag1_sum += cube->blocks[i][j][j].value;
			diag2_sum += cube->blocks[i][j][SIZE - j - 1].value;
		}
		if (diag1_sum == MAGIC_NUMBER) heuristics++;
		if (diag2_sum == MAGIC_NUMBER) heuristics++;
	}

	for (int j = 0; j < SIZE; j++) {
		int diag1_sum = 0, diag2_sum = 0;
		for (int i = 0; i < SIZE; i++) {
			diag1_sum += cube->blocks[i][j][i].value;
			diag2_sum += cube->blocks[i][j][SIZE - i - 1].value;
		}
		if (diag1_sum == MAGIC_NUMBER) heuristics++;
		if (diag2_sum == MAGIC_NUMBER) heuristics++;
	}

	for (int k = 0; k < SIZE; k++) {
		int diag1_sum = 0, diag2_sum = 0;
		for (int i = 0; i < SIZE; i++) {
			diag1_sum += cube->blocks[i][i][k].value;
			diag2_sum += cube->blocks[i][SIZE - i - 1][k].value;
		}
		if (diag1_sum == MAGIC_NUMBER) heuristics++;
		if (diag2_sum == MAGIC_NUMBER) heuristics++;
	}

	// Check space diagonals
	int space_diag1_sum = 0, space_diag2_sum = 0, space_diag3_sum = 0, space_diag4_sum = 0;
	for (int i = 0; i < SIZE; i++) {
		space_diag1_sum += cube->blocks[i][i][i].value;
		space_diag2_sum += cube->blocks[i][i][SIZE - i - 1].value;
		space_diag3_sum += cube->blocks[i][SIZE - i - 1][i].value;
		space_diag4_sum += cube->blocks[SIZE - i - 1][i][i].value;
	}
	if (space_diag1_sum == MAGIC_NUMBER) heuristics++;
	if (space_diag2_sum == MAGIC_NUMBER) heuristics++;
	if (space_diag3_sum == MAGIC_NUMBER) heuristics++;
	if (space_diag4_sum == MAGIC_NUMBER) heuristics++;

	return heuristics;
}

void swap(uint8_t *u1, uint8_t *u2) {
	uint8_t temp = *u1;
	*u1 = *u2;
	*u2 = temp;
}

Block *flatten_cube(Cube *cube) {
	Block *flat_array = (Block *)malloc(sizeof(Block) * (TOTAL_VALUES));

	size_t index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				flat_array[index].pos = cube->blocks[i][j][k].pos;
				flat_array[index].value = cube->blocks[i][j][k].value;
				index++;
			}
		}
	}
	return flat_array;
}

Cube *unflatten_cube(Block *flat_array) {
	Cube *cube = (Cube *)malloc(sizeof(Cube));

	size_t index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				cube->blocks[i][j][k].pos = flat_array[index].pos;
				cube->blocks[i][j][k].value = flat_array[index].value;
				index++;
			}
		}
	}
	return cube;
}

void test(Cube *cube) {
	cube->blocks[0][0][0].value = 25;
	cube->blocks[0][0][1].value = 16;
	cube->blocks[0][0][2].value = 80;
	cube->blocks[0][0][3].value = 104;
	cube->blocks[0][0][4].value = 90;

	cube->blocks[0][1][0].value = 115;
	cube->blocks[0][1][1].value = 98;
	cube->blocks[0][1][2].value = 4;
	cube->blocks[0][1][3].value = 1;
	cube->blocks[0][1][4].value = 97;

	cube->blocks[0][2][0].value = 42;
	cube->blocks[0][2][1].value = 111;
	cube->blocks[0][2][2].value = 85;
	cube->blocks[0][2][3].value = 2;
	cube->blocks[0][2][4].value = 75;

	cube->blocks[0][3][0].value = 66;
	cube->blocks[0][3][1].value = 72;
	cube->blocks[0][3][2].value = 27;
	cube->blocks[0][3][3].value = 102;
	cube->blocks[0][3][4].value = 48;

	cube->blocks[0][4][0].value = 67;
	cube->blocks[0][4][1].value = 18;
	cube->blocks[0][4][2].value = 119;
	cube->blocks[0][4][3].value = 106;
	cube->blocks[0][4][4].value = 5;

	cube->blocks[1][0][0].value = 91;
	cube->blocks[1][0][1].value = 77;
	cube->blocks[1][0][2].value = 71;
	cube->blocks[1][0][3].value = 6;
	cube->blocks[1][0][4].value = 70;

	cube->blocks[1][1][0].value = 52;
	cube->blocks[1][1][1].value = 64;
	cube->blocks[1][1][2].value = 117;
	cube->blocks[1][1][3].value = 69;
	cube->blocks[1][1][4].value = 13;

	cube->blocks[1][2][0].value = 30;
	cube->blocks[1][2][1].value = 118;
	cube->blocks[1][2][2].value = 21;
	cube->blocks[1][2][3].value = 123;
	cube->blocks[1][2][4].value = 23;

	cube->blocks[1][3][0].value = 26;
	cube->blocks[1][3][1].value = 39;
	cube->blocks[1][3][2].value = 92;
	cube->blocks[1][3][3].value = 44;
	cube->blocks[1][3][4].value = 114;

	cube->blocks[1][4][0].value = 116;
	cube->blocks[1][4][1].value = 17;
	cube->blocks[1][4][2].value = 14;
	cube->blocks[1][4][3].value = 73;
	cube->blocks[1][4][4].value = 95;

	cube->blocks[2][0][0].value = 47;
	cube->blocks[2][0][1].value = 61;
	cube->blocks[2][0][2].value = 45;
	cube->blocks[2][0][3].value = 76;
	cube->blocks[2][0][4].value = 86;

	cube->blocks[2][1][0].value = 107;
	cube->blocks[2][1][1].value = 43;
	cube->blocks[2][1][2].value = 38;
	cube->blocks[2][1][3].value = 33;
	cube->blocks[2][1][4].value = 94;

	cube->blocks[2][2][0].value = 89;
	cube->blocks[2][2][1].value = 68;
	cube->blocks[2][2][2].value = 63;
	cube->blocks[2][2][3].value = 58;
	cube->blocks[2][2][4].value = 37;

	cube->blocks[2][3][0].value = 32;
	cube->blocks[2][3][1].value = 93;
	cube->blocks[2][3][2].value = 88;
	cube->blocks[2][3][3].value = 83;
	cube->blocks[2][3][4].value = 19;

	cube->blocks[2][4][0].value = 40;
	cube->blocks[2][4][1].value = 50;
	cube->blocks[2][4][2].value = 81;
	cube->blocks[2][4][3].value = 65;
	cube->blocks[2][4][4].value = 79;

	cube->blocks[3][0][0].value = 31;
	cube->blocks[3][0][1].value = 53;
	cube->blocks[3][0][2].value = 112;
	cube->blocks[3][0][3].value = 109;
	cube->blocks[3][0][4].value = 10;

	cube->blocks[3][1][0].value = 12;
	cube->blocks[3][1][1].value = 82;
	cube->blocks[3][1][2].value = 34;
	cube->blocks[3][1][3].value = 87;
	cube->blocks[3][1][4].value = 100;

	cube->blocks[3][2][0].value = 103;
	cube->blocks[3][2][1].value = 3;
	cube->blocks[3][2][2].value = 105;
	cube->blocks[3][2][3].value = 8;
	cube->blocks[3][2][4].value = 96;

	cube->blocks[3][3][0].value = 113;
	cube->blocks[3][3][1].value = 57;
	cube->blocks[3][3][2].value = 9;
	cube->blocks[3][3][3].value = 62;
	cube->blocks[3][3][4].value = 74;

	cube->blocks[3][4][0].value = 56;
	cube->blocks[3][4][1].value = 120;
	cube->blocks[3][4][2].value = 55;
	cube->blocks[3][4][3].value = 49;
	cube->blocks[3][4][4].value = 35;

	cube->blocks[4][0][0].value = 121;
	cube->blocks[4][0][1].value = 108;
	cube->blocks[4][0][2].value = 7;
	cube->blocks[4][0][3].value = 20;
	cube->blocks[4][0][4].value = 59;

	cube->blocks[4][1][0].value = 29;
	cube->blocks[4][1][1].value = 28;
	cube->blocks[4][1][2].value = 122;
	cube->blocks[4][1][3].value = 125;
	cube->blocks[4][1][4].value = 11;

	cube->blocks[4][2][0].value = 51;
	cube->blocks[4][2][1].value = 15;
	cube->blocks[4][2][2].value = 41;
	cube->blocks[4][2][3].value = 124;
	cube->blocks[4][2][4].value = 84;

	cube->blocks[4][3][0].value = 78;
	cube->blocks[4][3][1].value = 54;
	cube->blocks[4][3][2].value = 99;
	cube->blocks[4][3][3].value = 24;
	cube->blocks[4][3][4].value = 60;

	cube->blocks[4][4][0].value = 36;
	cube->blocks[4][4][1].value = 110;
	cube->blocks[4][4][2].value = 46;
}