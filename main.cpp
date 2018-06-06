#include "inc/function.h"

int main(int argc, char **argv)
{
    cout << "stage 1 ---------------------" << endl;

    PopulationType population(argv[1], 1); //1 mean for stage 1 ,2 mean for stage 2
    population.budget = atoi(argv[2]);

    cout << "budget: " << population.budget / 1000000.0 << " M" << endl;

    for (size_t i = 0; i < ITERA_CNT; i++)
    {
        cout << "(" << i + 1 << "/" << ITERA_CNT << ")" << endl;
        population.reproduction();
        population.crossover();
        population.mutation();
        population.computeFitness(i);
    }
    population.printBestOne();

    cout << "\nstage 2 ---------------------" << endl;

    PopulationType population2(argv[1], 2);
    population2.budget = population.budget - population.BestOne.cost;

    cout << "budget: " << population2.budget / 1000000.0 << " M" << endl;

    for (size_t i = 0; i < ITERA_CNT; i++)
    {
        cout << "(" << i << "/" << ITERA_CNT << ")" << endl;
        population2.reproduction();
        population2.crossover();
        population2.mutation();
        population2.computeFitness(i);
    }
    population2.printBestOne();
}
