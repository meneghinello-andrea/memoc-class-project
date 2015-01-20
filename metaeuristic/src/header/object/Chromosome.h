#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using std::ostringstream;
using std::string;
using std::vector;

class Chromosome
{
	private:
		double fitnessValue;
		vector<int> *genes;

	protected:
		double cint(double value) const;
		double round(double value, unsigned places) const;

	public:
		Chromosome(int genes[], int chromosomeSize, double fitnessValue);
		Chromosome(const Chromosome &Chromosome);
		~Chromosome();

		int size() const;
		double getFitnessValue() const;

		bool equals(const Chromosome &chromosome) const;
		string toString() const;

		class Iterator
		{
			friend class Chromosome;

			private:
				const Chromosome *chromosome;
				int cursor;

			public:
				bool operator==(const Iterator &iterator) const;
				bool operator!=(const Iterator &iterator) const;

				Iterator& operator++();
				Iterator& operator++(int increment);
		};

		Chromosome::Iterator begin() const;
		Chromosome::Iterator begin(int index) const;
		Chromosome::Iterator end() const;

		int operator[](const Chromosome::Iterator &iterator) const;

		bool operator==(const Chromosome &chromosome) const;
		bool operator!=(const Chromosome &chromosome) const;

		bool operator<=(const Chromosome &chromosome) const;
		bool operator>=(const Chromosome &chromosome) const;

		bool operator<(const Chromosome &chromosome) const;
		bool operator>(const Chromosome &chromosome) const;
};

#endif //CHROMOSOME_H