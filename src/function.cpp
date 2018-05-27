#include "../inc/function.h"

chromosomeForm bestOne;
void readCSV(dataForm &data)
{
    data.row = 1;
    data.column = 0;
    string temp;
    ifstream fileInput(data.fileName, ios::in);
    if (!fileInput)
    {
        cerr << "\nError opening file: " << data.fileName;
    }

    // let's count # lines first.
    while (fileInput.good())
    {
        getline(fileInput, temp, ',');
        data.column++;
        // //cout << temp<< endl;
        if (temp.find("\n") < UINT32_MAX)
        {
            data.row++;
            data.column++;
            //  //cout << data.column << endl;
        }
    }

    data.column /= data.row;
    //cout << "row : " << data.row << endl;
    //cout << "column : " << data.column << endl;
    data.row -= 1; //real data
    //allocate memory for storing data
    data.content = new string[data.row * data.column];
    //re-read the file and this time read the actual data into allocated memory
    fileInput.seekg(0, fileInput.beg);
    getline(fileInput, temp);
    for (size_t i = 0; i < data.row; i++)
    {
        for (size_t j = 0; j < data.column; j++)
        {
            if (j == data.column - 1)
            {
                getline(fileInput, data.content[i * data.column + j]);
            }
            else
            {
                getline(fileInput, data.content[i * data.column + j], ',');
            }
        }
    }

    for (size_t i = 0; i < data.row; i++)
    {
        //cout << data.content[i * data.column + data.pArea] << "\t" << data.content[i * data.column + data.pPCI] << endl;
    }
    fileInput.close();
}

void initialization(chromosomeForm *parent, chromosomeForm *pool, chromosomeForm *offspring, dataForm &data)
{
    //cout << "random generate binary value for each chromosome" << endl;

    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        parent[i].length = data.row;
        for (size_t j = 0; j < data.row; j++)
        {
            parent[i].binaryValue += to_string(BinaryRand());
        }
    }

    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        //cout << parent[i].binaryValue << endl;
    }
    setFitness(parent, data);
    penalty(0, parent, data);
    setProbability(parent);
}

void setFitness(chromosomeForm *population, dataForm &data)
{
    //cout << "calculate fitness value " << endl;
    double cost = 0;

    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        population[i].benefit = 0;
        population[i].cost = 0;
        for (size_t j = 0; j < data.row; j++)
        {
            // //cout << population[i].binaryValue[j];
            if (population[i].binaryValue[j] == '1')
            {
                //(PCI'-PCI)/Area
                population[i].benefit +=
                    ((100.0 - atof(data.content[j * data.column + data.pPCI].c_str()) * data.PCI_decline) *
                     atof(data.content[j * data.column + data.pArea].c_str()));
                population[i].cost += atof(data.content[j * data.column + data.pArea].c_str()) * 586;
            }
        }
        //cout << " i = " << i << ",\t" << population[i].benefit;
        //cout << "\ttotal cost: " << population[i].cost << endl;
        //cout << endl;
    }
}
void setProbability(chromosomeForm *population)
{
    //cout << "calculate accumulated probabilty " << endl;
    double fitness_sum = 0;
    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        fitness_sum += population[i].fitnessValue;
    }
    population[0].probability = population[0].fitnessValue / fitness_sum;
    //cout << population[0].probability << endl;
    for (size_t i = 1; i < POPULATION_CNT; i++)
    {
        population[i].probability = population[i - 1].probability + population[i].fitnessValue / fitness_sum;
        //cout << population[i].probability << endl;
    }
}

void reproduction(chromosomeForm *parent, chromosomeForm *temp)
{
    // cout << "do reproduction" << endl;
    double r;
    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        r = SRand();
        if (r < parent[0].probability)
        {
            //cout << r << " ~ " << parent[0].probability << endl;
            temp[i] = parent[0];
        }
        for (size_t j = 1; j < POPULATION_CNT; j++)
        {
            if (r < parent[j].probability && r > parent[j - 1].probability)
            {
                //cout << r << " ~ " << parent[j].probability << endl;
                temp[i] = parent[j];
            }
        }

        // //cout << parent[i].length;
        //cout << endl;
    }
}

void crossover(chromosomeForm *temp, chromosomeForm *offspring)
{
    //cout << "do crossover" << endl;
    size_t t1, t2, p, i = 0;
    while (i < POPULATION_CNT)
    {
        t1 = rand() % POPULATION_CNT;
        do
        {
            t2 = rand() % POPULATION_CNT;
        } while (t1 == t2);
        // //cout << t1 << "\t" << t2 << endl;

        double r = SRand();
        if (r < CROSSOVER_RATE)
        {
            p = rand() % temp[i].length;
            offspring[i].length = temp[i].length;
            offspring[i].binaryValue = temp[t1].binaryValue.substr(0, p) + temp[t2].binaryValue.substr(p, temp[i].length);

            i++;

            //cout << endl;
        }
    }
}

void mutation(chromosomeForm *offspring)
{
    //cout << " do mutation" << endl;
    double mr;
    size_t p;
    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        mr = SRand();
        // //cout <<p << endl;
        if (mr < MUTATION_RATE)
        {
            p = rand() % offspring[i].length;
            if (offspring[i].binaryValue[p] == '0')
            {
                offspring[i].binaryValue[p] = '1';
            }
            else
            {
                offspring[i].binaryValue[p] = '0';
            }
        }

        //cout << "i = " << i << " :" << offspring[i].binaryValue << endl;
    }
}

void penalty(size_t itera, chromosomeForm *offspring, dataForm &data)
{
    //cout << "do penalty" << endl;
    double min = 0;
    size_t max_index = 0;
    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        offspring[i].fitnessValue = offspring[i].benefit;
        if (offspring[i].cost > data.budget)
        {
            // cout << offspring[i].cost << " > " << data.budget << endl;
            offspring[i].fitnessValue -= pow(abs(offspring[i].cost - data.budget), 0.8) * pow(0.5 * itera, 2);
        }
        // cout << offspring[i].fitnessValue << endl;
        //最小值
        if (offspring[i].fitnessValue < min)
        {
            min = offspring[i].fitnessValue;
        }
    }
    //cout << "minimun value = " << min << endl;
    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        offspring[i].fitnessValue -= min - 1;
        if (offspring[i].fitnessValue > offspring[max_index].fitnessValue)
        {
            max_index = i;
        }
        //cout << "i = " << i << "\t" << offspring[i].fitnessValue << endl;
    }
    if (offspring[max_index].benefit > bestOne.benefit && offspring[max_index].cost < data.budget)
    {
        bestOne = offspring[max_index];
    }

    //cout << endl;
}

void chromosomeCopy(chromosomeForm *chromosome_1, chromosomeForm *chromosome_2)
{
    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        chromosome_1[i].binaryValue = chromosome_2[i].binaryValue;
        chromosome_1[i].cost = chromosome_2[i].cost;
        chromosome_1[i].fitnessValue = chromosome_2[i].fitnessValue;
        chromosome_1[i].length = chromosome_2[i].length;
        chromosome_1[i].probability = chromosome_2[i].probability;
        // //cout << chromosome_1[i].length << endl;
    }
}

void printBestOne()
{
    cout << "Best one: " << bestOne.binaryValue << endl;
    cout << "cost :" << bestOne.cost << endl;
}