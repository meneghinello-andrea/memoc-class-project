#include "src/header/object/Chromosome.h"

double Chromosome::cint(double value) const
{
	double fractional = modf(value, 0);
	double result = -1;

	if(fractional >= 0.5)
	{
		if(value >= 0)
		{
			result = ceil(value);
		}
		else
		{
			result = floor(value);
		}
	}
	else
	{
		if(value < 0)
		{
			result = ceil(value);
		}
		else
		{
			result = floor(value);
		}
	}

	return result;
}

double Chromosome::round(double value, unsigned places) const
{
	double off = pow(10, places);
	double result = this->cint(value * off) / off;
	return result;
}

Chromosome::Chromosome(int genes[], int chromosomeSize, double fitnessValue)
{
	int gene = -1;

	//Initialize the data structure for the gene sequence
	this->genes = new vector<int>(chromosomeSize);

	//Save the gene in the chromosome
	for(int i = 0; i < chromosomeSize; i += 1)
	{
		//Extract the gene
		gene = genes[i];

		//Save the gene in the chromosome structure
		this->genes->push_back(gene);
	}

	//Save the fitness value
	this->fitnessValue = this->round(fitnessValue, 4);
}

Chromosome::Chromosome(const Chromosome &chromosome)
{
	int gene = -1;

	//Initialize the data structure for the gene sequence
	this->genes = new vector<int>(chromosome.size());

	//Copy the chromosome
	for(Chromosome::Iterator iter = chromosome.begin(); iter != chromosome.end(); iter++)
	{
		//extract the gene
		gene = chromosome[iter];

		//Save teh gene in the chromosome structure
		this->genes->push_back(gene);
	}

	//Copy the fitness value
	this->fitnessValue = chromosome.getFitnessValue();
}

Chromosome::~Chromosome()
{
	if(this->genes != 0)
	{
		delete this->genes;
	}
}

int Chromosome::size() const
{
	int size = static_cast<int>(this->genes->size());
	return size;
}

double Chromosome::getFitnessValue() const
{
	return this->fitnessValue;
}

Chromosome::Iterator Chromosome::begin() const
{
	//Construct and iterator from the beginning of the chromosome
	Chromosome::Iterator iterator = this->begin(0);
	return iterator;
}

Chromosome::Iterator Chromosome::begin(int index) const
{
	//Construct an iterator from a specific starting point
	Chromosome::Iterator iterator;
	iterator.chromosome = this;
	iterator.cursor = index;
	return iterator;
}

Chromosome::Iterator Chromosome::end() const
{
	//Construct the end iterator
	int start = this->size();
	Chromosome::Iterator iterator = this->begin(start);
	return iterator;
}

bool Chromosome::equals(const Chromosome &chromosome) const
{
	bool equals = true;
	Chromosome::Iterator iterChromoA;
	Chromosome::Iterator iterChromoB;
	int geneA = -1;
	int geneB = -1;

	if(this->size() == chromosome.size())
	{
		//Initialize the iterators
		iterChromoA = this->begin();
		iterChromoB = chromosome.begin();

		while(iterChromoA != this->end() && iterChromoB != chromosome.end() && equals == true)
		{
			//Extract the gene
			geneA = (*this)[iterChromoA];
			geneB = chromosome[iterChromoB];

			//Check the gene
			if(geneA != geneB)
			{
				equals = false;
			}
			else
			{
				//Increment the iterators
				iterChromoA++;
				iterChromoB++;
			}
		}

		equals = equals && this->getFitnessValue() == chromosome.getFitnessValue();
	}
	else
	{
		equals = false;
	}

	return equals;
}

string Chromosome::toString() const
{
	int gene = -1;
	ostringstream stream;
	string chromosome = "";

	//Print the chromosome in the stream
	for(Chromosome::Iterator iter = this->begin(); iter != this->end(); iter++)
	{
		//Extract the gene
		gene = (*this)[iter];

		//Print the gene in the string stream
		stream << gene << "-";
	}

	//Print the fitness value associated
	stream << " (" << this->getFitnessValue() << ")";

	chromosome = stream.str();

	return chromosome;
}

int Chromosome::operator[](const Chromosome::Iterator &iterator) const
{
	int gene = -1;
	int index = iterator.cursor;

	if(0 <= index && index < this->size())
	{
		//Extract the gene pointed by the iterator object
		gene = this->genes->at(index);
	}

	return gene;
}

bool Chromosome::Iterator::operator==(const Chromosome::Iterator &iterator) const
{
	bool equals = false;

	if(this->chromosome == iterator.chromosome && this->cursor == iterator.cursor)
	{
		equals = true;
	}

	return equals;
}

bool Chromosome::Iterator::operator!=(const Chromosome::Iterator &iterator) const
{
	bool different = !(*this == iterator);
	return different;
}

Chromosome::Iterator& Chromosome::Iterator::operator++()
{
	if(0 <= this->cursor && this->cursor < this->chromosome->size())
	{
		this->cursor += 1;
	}

	return *this;
}

Chromosome::Iterator& Chromosome::Iterator::operator++(int increment)
{
	return ++(*this);
}

bool Chromosome::operator==(const Chromosome &chromosome) const
{
	bool equals = this->equals(chromosome);
	return equals;
}

bool Chromosome::operator!=(const Chromosome &chromosome) const
{
	bool different = !((*this) == chromosome);
	return different;
}

bool Chromosome::operator<=(const Chromosome &chromosome) const
{
	bool compare = (*this) == chromosome;

	if(compare == false)
	{
		compare = this->getFitnessValue() <= chromosome.getFitnessValue();
	}

	return compare;
}

bool Chromosome::operator>=(const Chromosome &chromosome) const
{
	bool compare = ((*this) == chromosome);

	if(compare == false)
	{
		compare = this->getFitnessValue() >= chromosome.getFitnessValue();
	}

	return compare;
}

bool Chromosome::operator<(const Chromosome &chromosome) const
{
	bool compare = !((*this) >= chromosome);
	return compare;
}

bool Chromosome::operator>(const Chromosome &chromosome) const
{
	bool compare = !((*this) <= chromosome);
	return compare;
}