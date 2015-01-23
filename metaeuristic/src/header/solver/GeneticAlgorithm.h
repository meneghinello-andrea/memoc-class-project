#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include "src/header/object/Chromosome.h"
#include "src/header/object/Population.h"

using std::ifstream;
using std::istringstream;
using std::max;
using std::min;
using std::random_shuffle;
using std::string;
using std::vector;

class GeneticAlgorithm
{
	private:
		int genes;
		vector<double> *costs;

		void readProblemDatas(string fileName);
		double getCost(int geneA, int geneB) const;
		Chromosome getBetterChromosome(const Population &set) const;
		bool contains(int geneSequence[], int sequenceLength, int gene) const;

		double fitnessFunction(const Chromosome &chromosome) const;
		Population initialize(int populationSize) const;
		Chromosome crossover(const Chromosome &father, const Chromosome &mother) const;
	
	public:
		GeneticAlgorithm();
		~GeneticAlgorithm();

		Chromosome resolve(int populationSize, int evolutions, string fileName);

		double getObjectiveValue(const Chromosome & chromosome) const;
};

#endif //GENETIC_ALGORITHM_H