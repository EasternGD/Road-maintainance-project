#include "inc/function.h"

int main(int argc, char *argv[])
{
	//cout << "stage 1 ---------------------" << endl;
	srand(time(NULL));
	//srand(atoi(argv[9]));

		PopulationType population(argv[1], 1); //1 mean for stage 1 ,2 mean for stage 2
		PopulationType population2(argv[1], 2);

		population.CROSSOVER_RATE = atof(argv[3]);
		population2.CROSSOVER_RATE = atof(argv[3]);
		population.MUTATION_RATE = atof(argv[4]);
		population2.MUTATION_RATE = atof(argv[4]);
		population.ALPHA = atof(argv[5]);
		population2.ALPHA = atof(argv[5]);
		population.BETA = atof(argv[6]);
		population2.BETA = atof(argv[6]);
		population.GAMMA = atof(argv[7]);
		population2.GAMMA = atof(argv[7]);
		population.budget = atoi(argv[8]);


		//cout << "budget: " << population.budget / 1000000.0 << " M" << endl;

		for (size_t i = 0; i < ITERA_CNT; i++)
		{
			//cout << "(" << i + 1 << "/" << ITERA_CNT << ")" << endl;
			population.reproduction();
			population.crossover();
			population.mutation();
			population.computeFitness(i);
		}

		population.printBestOne();
		saveJSON(population, population2, argv[2]);

	return(0);
	// cout << "\nstage 2 ---------------------" << endl;
	// population2.budget = population.budget - population.BestOne.cost;

	// cout << "budget: " << population2.budget / 1000000.0 << " M" << endl;

	// for (size_t i = 0; i < ITERA_CNT; i++)
	// {
	//     cout << "(" << i + 1 << "/" << ITERA_CNT << ")" << endl;
	//     population2.reproduction();
	//     population2.crossover();
	//     population2.mutation();
	//     population2.computeFitness(i);
	// }
	// population2.printBestOne();

}
