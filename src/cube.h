#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
#define TOTAL_VALUES (SIZE * SIZE * SIZE)

typedef struct {
	uint8_t value;
} Block;

typedef struct {
	Block blocks[SIZE][SIZE][SIZE];
} Cube;

void init_cube(Cube *cube);
void display_cube(Cube *cube);
void shuffle_cube(Cube *cube);
void shuffle(uint8_t *array, size_t n);