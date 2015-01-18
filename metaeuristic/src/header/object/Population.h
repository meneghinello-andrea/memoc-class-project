#ifndef POPULATION_H
#define POPULATION_H

#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "src/header/object/Chromosome.h"

using std::sort;
using std::vector;

class Population
{
	private:
		vector<Chromosome*> *population;

//		struct Less
//		{
//			Less(const Population &population) : population(population) {}
//			bool operator()(const Chromosome *chromosomeA, const Chromosome *chromosomeB)
//			{
//				return (*chromosomeA) < (*chromosomeB);
//			}
//			population& population;
//		};

	public:
		Population();
		~Population();

		int size() const;

		void sortPopulation();
		void addChromosome(Chromosome *chromosome);
		vector<Chromosome> getRandomSet(int size) const;

		class Iterator
		{
			friend class Population;

			private:
				const Population* population;
				int cursor;

			public:
				bool operator==(const Iterator &iterator) const;
				bool operator!=(const Iterator &iterator) const;

				Iterator& operator++();
				Iterator& operator++(int increment);
		};

		Population::Iterator begin() const;
		Population::Iterator begin(int start) const;
		Population::Iterator end() const;

		Chromosome& operator[](const Population::Iterator &iterator) const;

		static bool compare(const Chromosome *chromosomeA, const Chromosome *chromosomeB);
};

#endif //POPULATION_H