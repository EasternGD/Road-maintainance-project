#include "inc/function.h"

int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));
    dataForm data;
    data.fileName = argv[1];
    data.pPCI = atoi(argv[2]) - 1;
    data.pArea = atoi(argv[3]) - 1;
    data.PCI_decline = atof(argv[4]);
    data.COST_PER_AREA = atoi(argv[5]);
    data.budget = atoi(argv[6]);

    readCSV(data);

    chromosomeForm parent[POPULATION_CNT];
    chromosomeForm pool[POPULATION_CNT];
    chromosomeForm offspring[POPULATION_CNT];

    initialization(parent, pool, offspring, data);
    for (size_t i = 0; i < ITERA_CNT; i++)
    {
        reproduction(parent, pool);
        crossover(pool, offspring);
        mutation(offspring);
        setFitness(offspring, data);
        penalty(i, offspring, data);
        setProbability(offspring);
        chromosomeCopy(parent, offspring);
    }
    printBestOne();
}