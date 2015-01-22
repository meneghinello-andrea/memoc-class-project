#include "src/header/object/Population.h"

Population::Population()
{
	this->population = new vector<Chromosome*>();
}

Population::Population(const Population &population)
{
	//The chromosome from the old population
	Chromosome chromosome;

	//A copy of the chromosome
	Chromosome *copy = 0;

	//Initialize the new population structure
	this->population = new vector<Chromosome*>();

	//Copy the chromosomes
	for(Population::Iterator iter = population.begin(); iter != population.end(); iter++)
	{
		//Extract a chromosome from the population
		chromosome = population[iter];

		//Copy the chromosome
		copy = new Chromosome(chromosome);

		//Insert the chromosome in the population
		this->population->push_back(copy);
	}
}

Population::~Population()
{
	if(this->population != 0)
	{
		delete []this->population;
	}
}

Population& Population::operator=(const Population &population)
{
	//The chromosome from the existing population
	Chromosome chromosome;

	//A copy of the chromosome
	Chromosome *copy = 0;

	//Copy only if they are different
	if(this != &population)
	{
		//Check if the current population is populated by element
		if(this->population != 0)
		{
			//Free memory
			this->~Population();
		}

		//Initialize the new population structure
		this->population = new vector<Chromosome*>();

		//Copy the chromosomes
		for(Population::Iterator iter = population.begin(); iter != population.end(); iter++)
		{
			//Extract a chromosome from the population
			chromosome = population[iter];

			//Copy the chromosome
			copy = new Chromosome(chromosome);

			//Insert the copy in the structure
			this->population->push_back(copy);
		}
	}

	return *this;
}

int Population::size() const
{
	//Compute the population size
	int size = static_cast<int>(this->population->size());

	return size;
}

Population Population::getRandomSet(int setSize) const
{
	//Used to make a copy of the selected chromosome
	Chromosome copy;

	//The chromosome selected randomly
	Chromosome *selected;

	//Index used to extract elements from the population
	int index = -1;

	//Population size
	int size = this->size();

	//Population set
	Population set;

	if(setSize > 1)
	{
		for(int i = 0; i < setSize; i += 1)
		{
			//Select a random index between 0 and population size (excluded)
			index = rand() % size;

			//Extract the chromosome pointed by index
			selected = this->population->at(index);

			//Make the copy of the selected chromosome
			copy = *selected;

			//Insert the copied chromosome in the set
			set.addChromosome(copy);
		}
	}

	return set;
}

void Population::addChromosome(Chromosome &chromosome)
{
	//Copy the chromosome
	Chromosome *copy = new Chromosome(chromosome);

	//Add the chromosome to the population
	this->population->push_back(copy);
}

string Population::toString() const
{
	Chromosome chromosome;
	ostringstream stream;
	string population;

	for(Population::Iterator iter = this->begin(); iter != this->end(); iter++)
	{
		//Extract the current chromosome
		chromosome = (*this)[iter];

		//Insert the chromosome in the stream
		stream << chromosome.toString() << endl;
	}

	//Convert the stream in string
	population = stream.str();

	return population;
}

bool Population::Iterator::operator==(const Population::Iterator &iterator) const
{
	bool equals = false;

	if(this->population == iterator.population && this->cursor == iterator.cursor)
	{
		//The two iterator are at the same point in the same population
		equals = !equals;
	}

	return equals;
}

bool Population::Iterator::operator!=(const Population::Iterator &iterator) const
{
	bool different = !(*this == iterator);

	return different;
}

Population::Iterator Population::Iterator::operator++()
{
	//The size of the population
	int size = this->population->size();

	//Check if the cursor is in the matrix limits
	if(0 <= this->cursor && this->cursor < size)
	{
		//Move the cursor to the next position
		this->cursor += 1;
	}

	return *this;
}

Population::Iterator Population::Iterator::operator++(int increment)
{
	return ++(*this);
}

Population::Iterator Population::begin() const
{
	//Create an iterator that point to the first chromosome in the population
	Population::Iterator iterator = this->begin(0);

	return iterator;
}

Population::Iterator Population::begin(int start) const
{
	//Create an empty iterator
	Population::Iterator iterator;

	//Size of the population
	int size = this->size();

	//Link the iterator to the population
	iterator.population = this;

	//Set the cursor in the iterator
	if(0 <= start && start < size)
	{
		iterator.cursor = start;
	}
	else
	{
		iterator.cursor = size;
	}

	return iterator;
}

Population::Iterator Population::end() const
{
	//Compute the first index outside the population
	int end = this->size();

	//Create an iterator that point outside the population range
	Population::Iterator iterator = this->begin(end);

	return iterator;
}

Chromosome Population::operator[](const Population::Iterator &iterator) const
{
	//The chromosome
	Chromosome chromosome;

	//Extract the cursor from the iterator
	int index = iterator.cursor;

	//Population size
	int size = this->size();

	if(0 <= index && index < size)
	{
		//Extract the selected chromosome
		chromosome = *(this->population->at(index));
	}

	return chromosome;
}