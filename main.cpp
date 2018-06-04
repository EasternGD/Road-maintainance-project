#include "inc/function.h"

int main(int argc, char **argv)
{
    PopulationType population(argv[1]);
    population.budget[0] = atoi(argv[2]);
    population.budget[1] = atoi(argv[3]);
    population.budget[2] = atoi(argv[4]);
    population.budget[3] = atoi(argv[5]);

    for (size_t i = 0; i < 80; i++)
    {
        population.reproduction();
        population.crossover();
        population.mutation();
        population.computeFitnessForStage1(i, 0);
    }
    
    population.printBestOne();
}