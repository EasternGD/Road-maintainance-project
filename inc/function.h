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
#define PCI_decline 0.8
#define COST_PER_AREA 586

class DataType
{
private:
  size_t pPCI = 27;
  size_t pArea = 7;
  string mustBeDone;
  /*four season*/
public:
  string *content;
  size_t row;
  size_t column;
  double power = 0;
  int budget;
  DataType(string, int);
  virtual ~DataType() { delete[] content; }
};

class PopulationType : public DataType
{
public:
  struct ChromosomeType
  {
    string binaryValue;
    int cost = 0;
    double fitnessValue = 0;
    double benefit = 0;
    double probability = 0;
  } BestOne;

private:
  ChromosomeType *parent = new ChromosomeType[POPULATION_CNT];
  ChromosomeType *pool = new ChromosomeType[POPULATION_CNT];
  ChromosomeType *offspring = new ChromosomeType[POPULATION_CNT];

public:
  PopulationType(string, int);
  ~PopulationType()
  {
    delete[] parent;
    delete[] pool;
    delete[] offspring;
  };
  void reproduction();
  void crossover();
  void mutation();
  void computeFitness(size_t);
  void printBestOne();
};