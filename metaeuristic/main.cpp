#include <iostream>
#include <string>
#include "src/header/object/Chromosome.h"
#include "src/header/solver/GeneticAlgorithm.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
	GeneticAlgorithm *solver = new GeneticAlgorithm();

	Chromosome c = solver->resolve(100, 30, "data/cost_10_1.dat");

	cout << c.toString() << endl;

	delete solver;
}