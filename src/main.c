#include "cube.h"
#include <stdlib.h>

int main(){
	Cube *cube = (Cube *)malloc(sizeof(Cube));
	if (cube == NULL) return 1;

	init_cube(cube);
	
	while(!check_cube(cube)){
		shuffle_cube(cube);
	}

	display_cube(cube);

	free(cube);
	return 0;
}