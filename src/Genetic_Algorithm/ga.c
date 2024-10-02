#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ga.h"

void ga() {
	srand(time(NULL));

	generate_chromosome();
	Chromosomes_list *cl = (Chromosomes_list *)malloc(sizeof(Chromosomes_list));
	Chromosomes_list *new_cl = (Chromosomes_list *)malloc(sizeof(Chromosomes_list));
	read_chromosome(cl, fopen("src/Parents/gen-1.txt", "r"));
	int total_heuristic = calculate_total_h(cl);
	init_chance(cl, total_heuristic);

	for (int i = 0; i < TOTAL_GENERATION; i++) {
		printf("Current generation: %d\n", i);
		for (int j = 0; j < TOTAL_CHROMOSOME; j += 2) {
			Chromosome *parent1 = select_parent(cl);
			Chromosome *parent2 = select_parent(cl);

			Chromosome child1 = *parent1;
			Chromosome child2 = *parent2;

			crossover(&child1, &child2);

			mutate(&child1, MUTATION_RATE);
			mutate(&child2, MUTATION_RATE);

			new_cl->chromosomes[j] = child1;
			new_cl->chromosomes[j + 1] = child2;
		}

		Chromosomes_list *temp = cl;
		cl = new_cl;
		new_cl = temp;

		total_heuristic = calculate_total_h(cl);
		init_chance(cl, total_heuristic);
	}

	sort_chromosome(cl);
	write_chromosome(cl, fopen("src/Parents/gen-2.txt", "w"));
	read_chromosome(cl, fopen("src/Parents/gen-1.txt", "r"));
	sort_chromosome(cl);
	write_chromosome(cl, fopen("src/Parents/gen-1.txt", "w"));
	free(cl);
	free(new_cl);
}

void generate_chromosome() {
	FILE *file = fopen("src/Parents/gen-1.txt", "w");
	Cube *cube = (Cube *)malloc(sizeof(Cube));
	init_cube(cube);

	Block *flat_array = flatten_cube(cube);
	int h;

	for (int i = 0; i < TOTAL_CHROMOSOME; i++) {
		Cube *c = unflatten_cube(flat_array);
		h = calculate_heuristics(c);
		fprintf(file, "%d;", h);
		for (int j = 0; j < TOTAL_VALUES; j++) {
			fprintf(file, "%d:%d ", flat_array[j].value, flat_array[j].pos);
		}
		fprintf(file, "\n");
		shuffle(flat_array);
	}

	free(cube);
	free(flat_array);
	fclose(file);
}

Chromosomes_list *read_chromosome(Chromosomes_list *cl, FILE *file) {
	char buf;
	int temp_val, temp_pos, temp_heuristic;
	for (int i = 0; i < TOTAL_CHROMOSOME; i++) {
		fscanf(file, "%d%c", &temp_heuristic, &buf);
		cl->chromosomes[i].h = temp_heuristic;
		for (int j = 0; j < TOTAL_VALUES; j++) {
			fscanf(file, "%d:%d%c", &temp_val, &temp_pos, &buf);
			cl->chromosomes[i].flat_array[j].value = (uint8_t)temp_val;
			cl->chromosomes[i].flat_array[j].pos = (uint8_t)temp_pos;
		}
		if (buf != '\n') {
			fscanf(file, "%c", &buf);
		}
	}

	fclose(file);
	return cl;
}

void write_chromosome(Chromosomes_list *cl, FILE *file) {
	for (int i = 0; i < TOTAL_CHROMOSOME; i++) {
		fprintf(file, "%d;", cl->chromosomes[i].h);
		for (int j = 0; j < TOTAL_VALUES; j++) {
			fprintf(file, "%d:%d ", cl->chromosomes[i].flat_array[j].value,
			        cl->chromosomes[i].flat_array[j].pos);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

void mutate(Chromosome *chromosome, double mutation_rate) {
	for (int i = 0; i < TOTAL_VALUES; i++) {
		if ((double)rand() / RAND_MAX < mutation_rate) {
			int pos2 = rand() % TOTAL_VALUES;
			Block temp = chromosome->flat_array[i];
			chromosome->flat_array[i] = chromosome->flat_array[pos2];
			chromosome->flat_array[pos2] = temp;
		}
	}
}

int calculate_total_h(Chromosomes_list *cl) {
	int h = 0;
	for (int i = 0; i < TOTAL_CHROMOSOME; i++) {
		h += cl->chromosomes[i].h;
	}
	return h;
}

void init_chance(Chromosomes_list *cl, int h) {
	for (int i = 0; i < TOTAL_CHROMOSOME; i++) {
		cl->chromosomes[i].chance = ((double)cl->chromosomes[i].h + EPSILON) / (double)h;
	}
}

int compare_chromosomes(const void *a, const void *b) {
	Chromosome *chromosome_a = (Chromosome *)a;
	Chromosome *chromosome_b = (Chromosome *)b;
	return chromosome_b->h - chromosome_a->h;
}

void sort_chromosome(Chromosomes_list *cl) {
	qsort(cl->chromosomes, TOTAL_CHROMOSOME, sizeof(Chromosome), compare_chromosomes);
}

void crossover(Chromosome *state1, Chromosome *state2) {
	int crossover_point = rand() % TOTAL_VALUES;

	for (int i = crossover_point; i < TOTAL_VALUES; i++) {
		Block temp = state1->flat_array[i];
		state1->flat_array[i] = state2->flat_array[i];
		state2->flat_array[i] = temp;
	}

	int value_count[TOTAL_VALUES] = {0};
	for (int i = 0; i < TOTAL_VALUES; i++) {
		value_count[state1->flat_array[i].value]++;
	}
	for (int i = 0; i < TOTAL_VALUES; i++) {
		if (value_count[state1->flat_array[i].value] > 1) {
			for (int j = 0; j < TOTAL_VALUES; j++) {
				if (value_count[j] == 0) {
					value_count[state1->flat_array[i].value]--;
					state1->flat_array[i].value = j;
					value_count[j]++;
					break;
				}
			}
		}
	}

	for (int i = 0; i < TOTAL_VALUES; i++) {
		value_count[i] = 0;
	}
	for (int i = 0; i < TOTAL_VALUES; i++) {
		value_count[state2->flat_array[i].value]++;
	}
	for (int i = 0; i < TOTAL_VALUES; i++) {
		if (value_count[state2->flat_array[i].value] > 1) {
			for (int j = 0; j < TOTAL_VALUES; j++) {
				if (value_count[j] == 0) {
					value_count[state2->flat_array[i].value]--;
					state2->flat_array[i].value = j;
					value_count[j]++;
					break;
				}
			}
		}
	}
}

Chromosome *select_parent(Chromosomes_list *cl) {
	double r = (double)rand() / RAND_MAX;
	double cumulative_probability = 0.0;

	for (int i = 0; i < TOTAL_CHROMOSOME; i++) {
		cumulative_probability += cl->chromosomes[i].chance;
		if (r <= cumulative_probability) {
			return &cl->chromosomes[i];
		}
	}
	return &cl->chromosomes[TOTAL_CHROMOSOME - 1];
}