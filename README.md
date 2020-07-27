# Road-maintainance-project
>Genetic-Algorithm Implementation of Road Maintenance

`data/01.csv` and `data/testfile.csv` are road information provided by the government

## Installation

```sh
git clone https://github.com/EasternGD/Road-maintainance-project.git
```

## Usage example

```sh
./main.exe data/01.csv 01.json 0.8 0.1 0.8 0.5 0.8 15000000
```

Argument:

1. Input Data
2. Ouptput Data (JSON file)
3. Crossover rate
4. Mutation rate
5. Alpha
6. Beta
7. Gamma
8. Budget

## Tests 
Use `make test1` for test small size data
```sh
make
make test1
```

## Example Output
```sh
	{
		"NUMBER":["BL000432,BL000220,BL000493,BL001220,BL000237,BL000238"],
		"COST":1.46431e+007,
		"BENEFIT":2.07468e+006
	}

```
