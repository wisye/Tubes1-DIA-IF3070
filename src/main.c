#include <stdlib.h>

#include "cube.h"
#include "Steepest Ascent Hill-Climbing/sahc.h"
#include "Hill-climbing with Sideways Move/hcsm.h"
int main()
{
	Cube *cube = (Cube *)malloc(sizeof(Cube));
	if (cube == NULL)
		return 1;

	init_cube(cube);

	// while(!check_cube(cube)){
	// 	shuffle_cube(cube);
	// }
	// test(cube);
	// if (check_cube(cube))
	// {
	// 	display_cube(cube);
	// }

	// printf("\n\n%d\n", calculate_heuristics(cube));

	//? BAWAH TESTING ALGORITHM
	// printf("Before SAHC\n");
	// display_cube(cube);

	// sahc(cube);

	// printf("After SAHC\n");
	// display_cube(cube);

	//
	printf("Before HCSM\n");
	display_cube(cube);

	hcsm(cube);

	printf("After hcsm\n");
	display_cube(cube);

	free(cube);
	return 0;
}