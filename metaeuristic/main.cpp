#include <ctime>
#include <iostream>
#include <string>
#include "src/header/object/Chromosome.h"
#include "src/header/solver/GeneticAlgorithm.h"

using std::cout;
using std::endl;
using std::string;

void printTime(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end)
{
	//Milliseconds used by the computations
	int elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	//Datas to print the start and the end time
	std::time_t startTime = std::chrono::system_clock::to_time_t(start);
	std::time_t endTime = std::chrono::system_clock::to_time_t(end);

	cout << "Computation started at:   " << std::ctime(&startTime) << endl;
	cout << "Computation completed at: " << std::ctime(&endTime) << endl;
	cout << "Computation in (ms):      " << elapsedMilliseconds << endl;
}

int main(int argc, char* argv[])
{
	//The solution of the problem
	Chromosome solution;

	//Objective value
	double objValue = -1;

	//Genetic algorithm
	GeneticAlgorithm *solver = 0;

	//The size of the population
	int populationSize = -1;

	//The size of the evolutions
	int evolutions = -1;

	//File with the problem data
	string fileName = "";

	//Time when the computation start
	std::chrono::time_point<std::chrono::system_clock> start;

	//Time when the computation end;
	std::chrono::time_point<std::chrono::system_clock> end;

	if((argc - 1) == 3)
	{
		//Extract the path to the file with the data
		fileName = argc[1];

		//Extract the population size
		populationSize = argc[2];

		//Extract the numboer of evolutions
		evolutions = argc[3];

		//Create the solver
		solver = new GeneticAlgorithm();

		//Save the start time
		start = std::chrono::system_clock::now();

		//Resolve the problem
		solution = solver->resolve(populationSize, evolutions, fileName);

		//Save the end time
		end = std::chrono::system_clock::now();

		//Compute the objective value of the solution found
		objValue = solver->getObjectiveValue(chromosome);

		//Print the solution
		cout << solution.toString() << " -> " << objValue << endl;

		//Print the computation time
		printTime(start, end);
	}
}