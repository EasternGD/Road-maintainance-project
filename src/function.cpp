#include "../inc/function.h"

DataType::DataType(string fileName)
{
    /* let's count # lines first.*/
    row = 1;
    column = 0;
    string buffer;
    ifstream fileInput(fileName, ios::in);
    if (!fileInput)
    {
        cerr << "\nError opening file: " << fileName << endl;
    }

    while (fileInput.good())
    {
        getline(fileInput, buffer, ',');
        column++;
        // cout << buffer << endl;
        if (buffer.find("\n") < UINT32_MAX)
        {
            column++;
            row++;
            // cout << column << endl;
        }
    }

    column /= row;
    /* file's content size */
    cout << "row : " << row << endl;
    cout << "column : " << column << endl;

    //allocate memory for storing data
    content = new string[(row - 1) * 3];

    //re-read the file and this time read the useful data into allocated memory
    fileInput.seekg(0, fileInput.beg);
    getline(fileInput, buffer);
    for (size_t i = 1; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {

            if (!j)
            {
                getline(fileInput, content[(i - 1) * 3], ',');
            }
            else if (j == (pArea - 1))
            {
                getline(fileInput, content[(i - 1) * 3 + 1], ',');
            }
            else if (j == (pPCI - 1))
            {
                getline(fileInput, content[(i - 1) * 3 + 2]);
            }
            else
            {
                getline(fileInput, buffer, ',');
            }
        }
    }

    // for (size_t i = 0; i < (row - 1); i++)
    // {
    //     for (size_t j = 0; j < 3; j++)
    //     {
    //         cout << content[i * 3 + j] << " ";
    //     }
    //     cout << endl;
    // }
    fileInput.close();
    /* figure data size */
    row -= 1;
    column = 3;
}

PopulationType::PopulationType(string argv1) : DataType(argv1)
{
    // binary value initilization
    srand(1);
    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        for (size_t j = 0; j < row; j++)
        {

            parent[i].binaryValue += to_string(BinaryRand());
            //(PCI'-PCI)* Area * binary
            parent[i].benefit +=
                ((100.0 - atof(content[j * column + 2].c_str()) * PCI_decline) *
                 atof(content[j * column + 1].c_str())) *
                (parent[i].binaryValue[j] - '0');
            parent[i].cost += atof(content[j * column + 1].c_str()) * 586.0 * (parent[i].binaryValue[j] - '0');
            parent[i].fitnessValue = parent[i].benefit;
        }
        // cout << parent[i].binaryValue << " ";
        // cout << parent[i].fitnessValue << endl;
    }
}

void PopulationType::reproduction()
{
    cout << "do reproduction" << endl;
    double sum = 0;
    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        sum += parent[i].fitnessValue;
    }

    parent[0].probability = parent[0].fitnessValue / sum;
    // cout << parent[0].probability << endl;
    for (size_t i = 1; i < POPULATION_CNT; i++)
    {
        parent[i].probability = parent[i - 1].probability + parent[i].fitnessValue / sum;
        cout << parent[i].probability << endl;
    }
    double r;

    for (size_t i = 0; i < POPULATION_CNT; i++)
    {
        for (size_t j = 0; j < POPULATION_CNT - 1; j++)
        {
            r = SRand();
            pool[i] = parent[0];
            if (r > parent[j].probability && r < parent[j + 1].probability)
            {

                pool[i] = parent[j + 1];
                cout << r << " ~ " << pool[i].probability << endl;
            }
        }
    }
}

void PopulationType::crossover()
{

}
void PopulationType::computeFitness()
{
}
