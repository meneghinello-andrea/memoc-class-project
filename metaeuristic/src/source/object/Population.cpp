#include "src/header/object/Population.h"

Population::Population()
{
	//Initialize the container
	this->population = new vector<Chromosome*>();
}

Population::~Population()
{
	Chromosome *current = 0;

//	for(int i = 0; i < this->size(); i += 1)
//	{
//		//Delete the chromosome
//		delete this->population->at(i);
//	}

	for(vector<Chromosome*>::iterator iter = this->population->begin(); iter != this->population->end(); ++iter)
	{
		current = *iter;
		delete current;
	}

	delete this->population;
}

int Population::size() const
{
	int size = static_cast<int>(this->population->size());
	return size;
}

void Population::sortPopulation()
{
	//Sort the chromosome population by the fitness value of each chromosome
	sort(this->population->begin(), this->population->end(), Population::compare);
}

void Population::addChromosome(Chromosome *chromosome)
{
	if(chromosome != 0)
	{
		this->population->push_back(chromosome);
	}
}

Chromosome Population::getRandomChromosome(int setSize) const
{
	Chromosome* selected = 0;
	int index = -1;

	//Initialize the random seed
	srand(time(NULL));

	//Initialize the set
	vector<Chromosome> randomSet;

	if(setSize > 0)
	{
		//Build the random set
		for(int i = 0; i < setSize; i += 1)
		{
			//Select a random number between 0 and population size
			index = rand() % this->size();

			//Extract the selected chromosome
			selected = this->population->at(index);

			//Add the selected chromosome to the set
			randomSet.push_back(*selected);
		}

		//Sort the random set
		sort(randomSet.begin(), randomSet.end());
	}

	return randomSet.at(0);
}

bool Population::Iterator::operator==(const Population::Iterator &iterator) const
{
	bool equals = false;

	if(this->population == iterator.population && this->cursor == iterator.cursor)
	{
		equals = true;
	}

	return equals;
}

bool Population::Iterator::operator!=(const Population::Iterator &iterator) const
{
	bool different = !((*this) == iterator);
	return different;
}

Population::Iterator& Population::Iterator::operator++()
{
	if(0 <= this->cursor && this->cursor < this->population->size())
	{
		this->cursor += 1;
	}

	return *this;
}

Population::Iterator& Population::Iterator::operator++(int increment)
{
	return ++(*this);
}

Population::Iterator Population::begin() const
{
	//Build the start iterator
	return this->begin(0);
}

Population::Iterator Population::begin(int start) const
{
	//Build an iterator
	Population::Iterator iterator;
	iterator.population = this;
	iterator.cursor = start;
	return iterator;
}

Population::Iterator Population::end() const
{
	//Build the end iterator
	int start = this->size();
	Population::Iterator iterator = this->begin(start);
	return iterator;
}

Chromosome& Population::operator[](const Population::Iterator &iterator) const
{
	Chromosome* current = 0;
	int index = iterator.cursor;

	if(0 <= index && index < this->size())
	{
		//Extract the current chromosome
		current = this->population->at(index);
	}

	return *current;
}

bool Population::compare(const Chromosome *chromosomeA, const Chromosome *chromosomeB)
{
	bool compare = (*chromosomeA) < (*chromosomeB);
	return compare;
}