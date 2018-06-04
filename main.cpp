#include "inc/function.h"

int main(int argc, char **argv)
{
    
    PopulationType population(argv[1], 1); //1 mean for stage 1 ,2 mean for stage 2
    population.budget = atoi(argv[2]);

    for (size_t j = 0; j < ITERA_CNT; j++)
    {
        population.reproduction();
        population.crossover();
        population.mutation();
        population.computeFitness(j);
    }

    PopulationType population2(argv[1], 2);
    population2.budget = population.budget - population.BestOne.cost;
    for (size_t j = 0; j < ITERA_CNT; j++)
    {
        population2.reproduction();
        population2.crossover();
        population2.mutation();
        population2.computeFitness(j);
    }
    population.printBestOne();
    population2.printBestOne();
}
