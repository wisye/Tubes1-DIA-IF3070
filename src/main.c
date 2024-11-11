#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Genetic_Algorithm/ga.h"
#include "Hill-climbing_with_Sideways_Move/hcsm.h"
#include "Random_Restart_Hill-climbing/rrhc.h"
#include "Simulated_Annealing/sa.h"
#include "Steepest_Ascent_Hill-climbing/sahc.h"
#include "Stochastic_Hill-climbing/shc.h"
#include "cube.h"
// #include "visualize_cube.h"

int main() {
	Cube *cube = (Cube *)malloc(sizeof(Cube));
	Cube *initialCube = (Cube *)malloc(sizeof(Cube));
	if (cube == NULL) return 1;
	init_cube(cube);
	copy_cube(cube, initialCube);

	//* --------------------------------- instruksi run dengan visualisasi ⬇️ ------------------------------
	//* uncomment code (by default ini )

	//* jika sudah menginstall openGL. Akan terpopup window baru jika memasukkan input 1.
	//* karena bebera kendala, Genetic Algorithm belum bisa di visualisasi
	char choice;
	puts("1. Steepest ascent hill climbing, its variant, and simulated annealing\n2. Genetic algorithm");
	scanf("%c", &choice);
	if (choice == '1')
		visualize_cube(cube);
	else
		ga(cube);

	//* --------------------------------- instruksi run dengan visualisasi ⬆️ ------------------------------

	//? --------------------------------- instruksi run tanpaa visualisasi ⬇️ ------------------------------

	//? uncomment salah satu algoritma yang mau di run.

	//? ini tinggal run aja slah satu algonya satu per satu, nanti buka folder results itu ada. dari situ csv
	//? dah dinamain per algo nya
	//? lngsng "make all" aja stiap kali ganti algo. misal hcsm(cube) skrng. `make all` di terminal .
	//? trus pas ganti algo, rrhc(cube). make all di command. and so on

	// hcsm(cube);
	// rrhc(cube);
	// sa(cube);
	// sahc(cube);
	// shc(cube);

	//? uncomment seluruh perintah print dan display ini

	// printf("Inisial state si cube: \n");
	// display_cube(initialCube);

	// printf("Akhir state si cube: \n");
	// display_cube(cube);
	//? --------------------------------- instruksi run tanpaa visualisasi ⬆️ ------------------------------

	free(cube);
	free(initialCube);
	return 0;
}
