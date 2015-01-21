#include "src/header/solver/GeneticAlgorithm.h"

void GeneticAlgorithm::readProblemDatas(string fileName)
{
	double cost = -1;
	ifstream file;
	string line = "";

	if(fileName != "")
	{
		//Open the file in read mode
		file.open(fileName.c_str());

		//Read the number of genes
		getline(file, line);
		istringstream iss(line);
		iss >> this->genes;

		//Read the cost
		while(getline(file, line))
		{
			istringstream iss(line);
			iss >> cost;
			this->costs->push_back(cost);
		}

		//Close the file
		file.close();
	}
}

double GeneticAlgorithm::getCost(int geneA, int geneB) const
{
	//Number of empty space in the matrix associated to the linearized array
	int empty_space_read = 0;

	//Index of the cost in the linearized array
	int index = 0;

	//Row start in the matrix associated with the linearized array
	int row_start = 0;

	if(geneA < geneB)
	{
		//Index calculation for the lower triangular matrix
		row_start = (this->genes * geneA) - ((geneA * (geneA + 1)) / 2);
		empty_space_read = geneA + 1;
		index = row_start - empty_space_read + geneB;
	}
	else
	{
		//Index calculation for the upper triangular matrix
		row_start = (this->genes * geneB) - ((geneB * (geneB + 1)) / 2);
		empty_space_read = geneB + 1;
		index = row_start - empty_space_read + geneA;
	}

	return index;
}

double GeneticAlgorithm::fitnessFunction(const Chromosome &chromosome) const
{
	Chromosome::Iterator iterA = chromosome.begin();
	double cost = 0;
	double fitnessValue = 0;
	double partial = 0;
	int geneA = chromosome[iterA];
	int geneB = -1;

	for(Chromosome::Iterator iterB = iterA++; iterB != chromosome.end(); iterB++)
	{
		//Get the end gene
		geneB = chromosome[iterB];

		//calculate cost to reach geneB from geneA
		partial = this->getCost(geneA, geneB);

		//Upgrade the total cost
		cost += partial;

		//Move the gene's pointer
		geneA = geneB;
	}

	//Calculate the fitness value
	fitnessValue = 1 / cost;

	return fitnessValue;
}

double GeneticAlgorithm::fitnessFunction(int *geneSequence, int sequenceSize) const
{
	//Create a temporany chromosome
	Chromosome *chromosome = new Chromosome(geneSequence, sequenceSize, 0);

	//Calculate it's fitness value
	double fitnessValue = this->fitnessFunction(*chromosome);

	//Free memory
	delete chromosome;

	return fitnessValue;
}

void GeneticAlgorithm::initialize(int populationSize)
{
	Chromosome *chromosome = 0;
	double fitnessValue = 0;
	int *geneSequence = new int[populationSize + 1];

	//Create the chromosome zero as the first N integer number
	for(int i = 0; i < this->genes; i += 1)
	{
		geneSequence[i] = i;
	}

	//Add zero at the end because I want to return to first gene at the end
	geneSequence[populationSize] = 0;

	//Initialize the population with populationSize random elements
	for(int i = 0; i < populationSize; i += 1)
	{
		//Shuffle the gene sequence
		random_shuffle(&geneSequence[1], &geneSequence[this->genes]);

		//Calculate the fitness value
		fitnessValue = this->fitnessFunction(geneSequence, this->genes + 1);

		//Create the chromosome
		chromosome = new Chromosome(geneSequence, this->genes + 1, fitnessValue);

		//Add the chromosome to the population
		this->population->addChromosome(chromosome);
	}

	//Sort the population by the fintess value
	this->population->sortPopulation();
}

GeneticAlgorithm::GeneticAlgorithm()
{
	this->costs = new vector<double>();
	this->genes = 0;
	this->population = new Population();
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	delete this->costs;
	delete this->population;
}