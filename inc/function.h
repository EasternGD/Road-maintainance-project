#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>

using namespace std;

#define SRand() ((double)rand() / (double)RAND_MAX)
#define BinaryRand() (rand() % 2)
#define POPULATION_CNT 100
#define ITERA_CNT 100
#define CROSSOVER_RATE 0.8
#define MUTATION_RATE 0.1

class dataForm
{
  public:
    string fileName;
    size_t pPCI;
    size_t pArea;
    string *content;
    size_t row;
    size_t column;
    double PCI_decline;
    size_t COST_PER_AREA;
    size_t budget;
};

class chromosomeForm
{
  public:
    string binaryValue;
    size_t length;
    double fitnessValue = 0;
    double benefit = 0;
    double probability = 0;
    double cost = 0;
};

void readCSV(dataForm &data);
void initialization(chromosomeForm *parent, chromosomeForm *pool, chromosomeForm *offspring, dataForm &data);
void setFitness(chromosomeForm *population, dataForm &data);
void setProbability(chromosomeForm *population);
void reproduction(chromosomeForm *parent, chromosomeForm *temp);
void crossover(chromosomeForm *temp, chromosomeForm *offspring);
void penalty(size_t itera, chromosomeForm *offspring, dataForm &data);
void chromosomeCopy(chromosomeForm *chromosome_1, chromosomeForm *chromosome_2);
void mutation(chromosomeForm *offspring);
void printBestOne();