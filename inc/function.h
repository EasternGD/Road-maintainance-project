#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>

using namespace std;

#define SRand() ((double)rand() / (double)RAND_MAX)
#define BinaryRand() (rand() % 2)
#define POPULATION_CNT 10
#define ITERA_CNT 10
#define CROSSOVER_RATE 0.8
#define MUTATION_RATE 0.1
#define PCI_decline 0.8
#define COST_PER_AREA 586

class DataType
{
private:
  size_t pPCI = 27;
  size_t pArea = 7;
  string* mustBeDone;
  /*four season*/
public:
  string *content;
  size_t row;
  size_t column;
  size_t budget[4];
  DataType(string);
};

class PopulationType : public DataType
{
public:
  struct ChromosomeType
  {
    string binaryValue;
    size_t cost = 0;
    double fitnessValue = 0;
    double benefit = 0;
    double probability = 0;
  };

private:
  ChromosomeType parent[POPULATION_CNT];
  ChromosomeType pool[POPULATION_CNT];
  ChromosomeType offspring[POPULATION_CNT];
  size_t iterantion;

public:
  PopulationType(string);
  void reproduction();
  void crossover();
  void computeFitness();
};

// void setFitness(chromosomeForm *population, dataForm &data);
// void setProbability(chromosomeForm *population);
// void reproduction(chromosomeForm *parent, chromosomeForm *temp);
// void crossover(chromosomeForm *temp, chromosomeForm *offspring);
// void penalty(size_t itera, chromosomeForm *offspring, dataForm &data);
// void chromosomeCopy(chromosomeForm *chromosome_1, chromosomeForm *chromosome_2);
// void mutation(chromosomeForm *offspring);
// void printBestOne();