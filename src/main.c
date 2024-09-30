#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "Steepest_Ascent_Hill-climbing/sahc.h"
#include "Hill-climbing_with_Sideways_Move/hcsm.h"

int main()
{
	Cube *cube = (Cube *)malloc(sizeof(Cube));
	if (cube == NULL)
		return 1;

	init_cube(cube);

	// test(cube);

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

	sahc(cube);

	printf("After hcsm\n");
	display_cube(cube);

	free(cube);
	return 0;
}

void choice(Cube *cube){
	puts("make ur choice");

	char input[80];
	fgets(input, 80, stdin);

	if(!strcmp(input, "sahc")){
		sahc(cube);
	}
	else if(!strcmp(input, "hcsm")){
		hcsm(cube);
	}
}