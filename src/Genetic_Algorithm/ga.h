#include "../cube.h"

#ifndef _GA_
#define _GA_

#define TOTAL_CHROMOSOME 1000
#define TOTAL_GENERATION 5
#define ELITE_SIZE 15
#define TOURNAMENT_SIZE 5
#define MUTATION_RATE 0.1

typedef struct {
	Block flat_array[TOTAL_VALUES];
	int h;
	double chance;
} Chromosome;

typedef struct {
	Chromosome chromosomes[TOTAL_CHROMOSOME];
} Chromosomes_list;

void ga();
void generate_chromosome();
void write_chromosome(Chromosomes_list *cl, FILE *file);
Chromosomes_list *read_chromosome(Chromosomes_list *cl, FILE *file);
void two_point_crossover(Chromosome *state1, Chromosome *state2);
int calculate_total_h(Chromosomes_list *cl);
void init_chance(Chromosomes_list *cl, int h);
int compare_chromosomes(const void *a, const void *b);
void sort_chromosome(Chromosomes_list *cl);
Chromosome *select_parent(Chromosomes_list *cl);
void mutate(Chromosome *chromosome, double mutation_rate);
void elitism(Chromosomes_list *cl, Chromosomes_list *new_cl, int elite_size);
void shuffle_population(Chromosomes_list *cl);
Chromosome *tournament_selection(Chromosomes_list *cl, int tournament_size);

#endif