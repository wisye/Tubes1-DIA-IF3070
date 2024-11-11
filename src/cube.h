#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _CUBE_
#define _CUBE_

#define SIZE 5
#define TOTAL_VALUES (SIZE * SIZE * SIZE)
#define MAGIC_NUMBER 315
#define TOTAL_EDGES 109

typedef struct {
	uint8_t value;
	uint8_t pos;
} Block;

typedef struct {
	Block blocks[SIZE][SIZE][SIZE];
} Cube;

void init_cube(Cube *cube);
void copy_cube(Cube *og, Cube *fake);
void display_cube(Cube *cube);
void shuffle_cube(Cube *cube);
void shuffle(Block *array);
void swap(uint8_t *u1, uint8_t *u2);
Block *flatten_cube(Cube *cube);
Cube *unflatten_cube(Block *flat_array);
Cube *unflatten_cube2(uint8_t **flat_array);

bool check_cube(Cube *cube);
int calculate_heuristics(Cube *cube);
void test(Cube *cube);

#endif