#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "src/header/object/Chromosome.h"

using std::endl;
using std::ostringstream;
using std::string;
using std::vector;

class Population
{
	private:
		vector<Chromosome*> *population;

	public:
		Population();
		Population(const Population &population);
		~Population();

		Population& operator=(const Population &population);

		int size() const;
		Population getRandomSet(int setSize) const;
		void addChromosome(Chromosome &chromosome);

		string toString() const;

		class Iterator
		{
			friend class Population;

			private:
				const Population* population;
				int cursor;

			public:
				bool operator==(const Population::Iterator &iterator) const;
				bool operator!=(const Population::Iterator &iterator) const;

				Population::Iterator operator++();
				Population::Iterator operator++(int increment);
		};

		Population::Iterator begin() const;
		Population::Iterator begin(int start) const;
		Population::Iterator end() const;

		Chromosome operator[](const Population::Iterator &iterator) const;
};

#endif //POPULATION_H