#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifndef _CUBE_
#define _CUBE_

#define SIZE 5
#define TOTAL_VALUES (SIZE * SIZE * SIZE)
#define MAGIC_NUMBER 315
#define TOTAL_EDGES 109

typedef struct
{
	uint8_t value;
	uint8_t pos;
} Block;

typedef struct
{
	Block blocks[SIZE][SIZE][SIZE];
} Cube;

void init_cube(Cube *cube);
void display_cube(Cube *cube);
void shuffle_cube(Cube *cube);
void shuffle(uint8_t *array, size_t n);
void swap(uint8_t *u1, uint8_t *u2);

bool check_cube(Cube *cube);
int calculate_heuristics(Cube *cube);
void test(Cube *cube);

#endif