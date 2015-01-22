#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <algorithm>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using std::max;
using std::min;
using std::ostringstream;
using std::reverse;
using std::string;
using std::vector;

class Chromosome
{
	private:
		vector<int> *genes;

	public:
		Chromosome();
		Chromosome(int geneSequence[], int sequenceLength);
		Chromosome(const Chromosome &chromosome);
		~Chromosome();

		Chromosome& operator=(const Chromosome &chromosome);

		int size() const;

		void mutate(int sequenceLength);

		string toString() const;

		class Iterator
		{
			friend class Chromosome;

			private:
				const Chromosome *chromosome;
				int cursor;

			public:
				bool operator==(const Chromosome::Iterator &iterator) const;
				bool operator!=(const Chromosome::Iterator &iterator) const;

				Chromosome::Iterator operator++();
				Chromosome::Iterator operator++(int increment);
		};

		Chromosome::Iterator begin() const;
		Chromosome::Iterator begin(int start) const;
		Chromosome::Iterator end() const;

		int operator[](const Chromosome::Iterator &iterator) const;
};

#endif //CHROMOSOME_H