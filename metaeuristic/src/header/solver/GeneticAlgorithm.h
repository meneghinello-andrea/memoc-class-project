#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "src/header/object/Chromosome.h"
#include "src/header/object/Population.h"

using std::ifstream;
using std::istringstream;
using std::random_shuffle;
using std::string;
using std::vector;

class GeneticAlgorithm
{
	private:
		int genes;
		Population *population;
		vector<double> *costs;

		void readProblemDatas(string fileName);
		double getCost(int geneA, int geneB) const;
		double fitnessFunction(const Chromosome &chromosome) const;
		double fitnessFunction(int *geneSequence, int sequenceSize) const;
		void initialize(int populationSize);

	public:
		GeneticAlgorithm();
		~GeneticAlgorithm();

		void TEST();
};

#endif //GENETIC_ALGORITHM_H