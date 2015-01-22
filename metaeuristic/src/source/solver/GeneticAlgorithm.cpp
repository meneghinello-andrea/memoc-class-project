#include "src/header/solver/GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
	this->costs = new vector<double>();
	this->genes = 0;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	//Check if memory is occupied
	if(this->costs != 0)
	{
		//Free memory
		delete this->costs;
	}
}

void GeneticAlgorithm::readProblemDatas(string fileName)
{
	//Cost read from file
	double cost = 0;

	//Stream associated to file
	ifstream file;

	//Line read from file
	string line = "";

	if(fileName != "")
	{
		//Open the file in read mode
		file.open(fileName.c_str());

		//Read the number of genes
		getline(file, line);
		istringstream iss(line);
		iss >> this->genes;

		//Read the costs
		while(getline(file, line))
		{
			//Parse the line
			istringstream iss(line);

			//Save the cost in a temporany variable
			iss >> cost;

			//Save the cost for the algorithm
			this->costs->push_back(cost);
		}

		//Close the file
		file.close();
	}
}

double GeneticAlgorithm::getCost(int geneA, int geneB) const
{
	//Cost to reach geneB from geneA
	double cost = -1;

	//Number of empty space in the row selected
	int empty_space = 0;

	//Index of the cost in the linearized array
	int index = -1;

	//Row start in the matrix associated with the linearized array
	int row_start = -1;

	if(geneA < geneB)
	{
		//Compute the index in the lower triangular matrix
		row_start = (this->genes * geneA) - ((geneA * (geneA + 1)) / 2);
		empty_space = geneA + 1;
		index = row_start - empty_space + geneB;
	}
	else
	{
		//Compute the index in the upper triangular matrix
		row_start = (this->genes * geneB) - ((geneB * (geneB + 1)) / 2);
		empty_space = geneB + 1;
		index = row_start - empty_space + geneA;
	}

	//Extract the selected cost
	cost = this->costs->at(index);

	return cost;
}

Chromosome GeneticAlgorithm::getBetterChromosome(const Population &set) const
{
	//Better chromosome in the set
	Chromosome chromosome;

	//Current chromosome under analysis
	Chromosome current;

	//Max fitness value associated to the chromosome
	double maxValue = 0;

	//Fitness value associate to a chromosome
	double value = 0;

	for(Population::Iterator iter = set.begin(); iter != set.end(); iter++)
	{
		//Extract the current chromosome
		current = set[iter];

		//Compute the fitness value associated to the chromosome
		value = this->fitnessFunction(current);

		if(value > maxValue)
		{
			//Save the new max value
			maxValue = value;

			//Save the associated chromosome
			chromosome = current;
		}
	}

	return chromosome;
}

bool GeneticAlgorithm::contains(int geneSequence[], int sequenceLength, int gene) const
{
	//At the beginning the gene is not present by definitions
	bool contains = false;

	//Search a specific gene in the gene sequence
	for(int i = 0; i < sequenceLength && contains == false; i += 1)
	{
		//Check each gene with a specific one
		if(geneSequence[i] == gene)
		{
			//the gene was found
			contains = !contains;
		}
	}

	return contains;
}

double GeneticAlgorithm::fitnessFunction(const Chromosome &chromosome) const
{
	//The iterator for the starter gene in the sub path
	Chromosome::Iterator iterA = chromosome.begin();

	//The total cost from the first to the last gene
	double cost = 0;

	//Fitness value
	double fitness = 0;

	//Partial cost
	double partial = 0;

	//The starter gene in the sub path
	int gene_start = chromosome[iterA];

	//The end gene in the sub path
	int gene_end = -1;

	for(Chromosome::Iterator iterB = iterA++; iterB != chromosome.end(); iterB++)
	{
		//Set the end gene in the sub path
		gene_end = chromosome[iterB];

		//Compute the cost to reach gene_end from gene_start
		partial = this->getCost(gene_start, gene_end);

		//Upgrade the total cost of the path
		cost += partial;

		//Move the gene start
		gene_start = gene_end;
	}

	//Compute the fitness value
	fitness = 1 / cost;

	return fitness;
}

Population GeneticAlgorithm::initialize(int populationSize) const
{
	//The chromosome
	Chromosome chromosome;

	//Size of the chromosomes
	int chromosomeSize = this->genes + 1;

	//Array for the chromosome zero
	int *geneSequence = new int[chromosomeSize];

	Population population;

	//Initialize the chromosome zero
	for(int i = 0; i < (chromosomeSize - 1); i += 1)
	{
		geneSequence[i] = i;
	}

	//Add zero at the end because the I want to return to gene zero after visiting all the genes
	geneSequence[chromosomeSize - 1] = 0;

	//Initialize the population with random chromosomes
	for(int i = 0; i < populationSize; i += 1)
	{
		//Shuffle the chromosome
		random_shuffle(&geneSequence[1], &geneSequence[chromosomeSize - 1]);

		//Create the chromosome
		chromosome = Chromosome(geneSequence, chromosomeSize);

		//Add the chromosome to the population
		population.addChromosome(chromosome);
	}

	return population;
}

Chromosome GeneticAlgorithm::crossover(const Chromosome &father, const Chromosome &mother) const
{
	//Flag to check if a gene is present in the child
	bool inserted = false;

	//The son chromosome
	Chromosome son;

	//Select two cut point in the chromosome range
	int cut_point_a = rand() % (this->genes - 1) + 1;
	int cut_point_b = rand() % (this->genes - 1) + 1;

	//Compute the start and and index for cut the chromosome
	int start = min(cut_point_a, cut_point_b);
	int end = max(cut_point_a, cut_point_b);

	//Current gene under analysis
	int gene = -1;

	//Index to slide the father
	int index = start;

	//Gene sequence for the son
	int *sonSequence = new int[this->genes + 1];

	//Initialize an empty gene sequence
	for(int i = 1; i < this->genes; i += 1)
	{
		sonSequence[i] = -1;
	}

	//Add the start and end gene
	sonSequence[0] = 0;
	sonSequence[this->genes] = 0;

	//Copy the father's part between start and end in the son gene sequence
	for(Chromosome::Iterator iter = father.begin(start); iter != father.end() && index <= end; iter++, index += 1)
	{
		//Extract the gene from the father
		gene = father[iter];

		//Save the gene in the son gene sequence in the same position as in the father
		sonSequence[index] = gene;
	}

	//Clean the gene
	gene = -1;

	//Copy mother's part in the free space of son gene sequence
	for(Chromosome::Iterator iter = mother.begin(); iter != mother.end(); iter++)
	{
		//Extract a gene from the mother
		gene = mother[iter];

		//Check if the gene is presente in the son
		if(this->contains(sonSequence, this->genes - 1, gene) == false)
		{
			//Setup the inserted flag
			inserted = false;

			//Find the first free position in the son
			for(int i = 0; i < (this->genes + 1) && inserted == false; i += 1)
			{
				//Check if the position is free
				if(sonSequence[i] == -1)
				{
					//Insert the gene in this position beceaus it is free
					sonSequence[i] = gene;

					//Set the inserted flag
					inserted = !inserted;
				}
			}
		}
	}

	//Create the son chromosome
	son = Chromosome(sonSequence, this->genes + 1);

	return son;
}

Chromosome GeneticAlgorithm::resolve(int populationSize, int evolutions, string fileName)
{
	//Initialize the random seed
	srand(time(NULL));

	//Chromosomes used to genereate a new population at each evolutions
	Chromosome better;
	Chromosome father;
	Chromosome mother;
	Chromosome son;

	//Mutation probability
	int mutationProb = 0;

	//Old and new population
	Population currentPopulation;
	Population nextPopulation;

	//Used for the torneo-n
	Population set;

	//Read the cost from file
	this->readProblemDatas(fileName);

	//Initialize the population zero
	currentPopulation = this->initialize(populationSize);

	//Simulate the evolution
	for(int i = 0; i < evolutions; i += 1)
	{
		//Get the better chromosome from the current 
		better = this->getBetterChromosome(currentPopulation);

		//Insert the better chromosome of the current population in the next generation
		nextPopulation.addChromosome(better);

		//Create the next generation
		for(int j = 0; i < (populationSize - 1); j += 1)
		{
			//Get a random set to search the father
			set = currentPopulation.getRandomSet(50);

			//Compute the father
			father = this->getBetterChromosome(set);

			//Get a random set to search the mother
			set = currentPopulation.getRandomSet(50);

			//Compute the mother
			mother = this->getBetterChromosome(set);

			//Compute the son
			son = this->crossover(father, mother);

			//Compute the mutation probability
			mutationProb = rand() % 11;

			if(mutationProb < 4)
			{
				//Mutate the son
				son.mutate(this->genes);
			}

			//Add the son the next generation
			nextPopulation.addChromosome(son);
		}
	}

	//Find the better chromosome in the last evolution
	better = this->getBetterChromosome(nextPopulation);

	return better;
}