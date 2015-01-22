#include "src/header/object/Chromosome.h"

Chromosome::Chromosome()
{
	this->genes = new vector<int>();
}

Chromosome::Chromosome(int geneSequence[], int sequenceLength)
{
	int gene = -1;

	//Initialize the new chromosome structure
	this->genes = new vector<int>();

	for(int i = 0; i < sequenceLength; i += 1)
	{
		//Extract the gene
		gene = geneSequence[i];

		//Save the gene in the structure
		this->genes->push_back(gene);
	}
}

Chromosome::Chromosome(const Chromosome &chromosome)
{
	int gene = -1;

	//Initialize the new chromosome structure
	this->genes = new vector<int>();

	//Copy al the genes in the new structure
	for(Chromosome::Iterator iter = chromosome.begin(); iter != chromosome.end(); iter++)
	{
		//Extract a single gene
		gene = chromosome[iter];

		//Save the gene in the new structure
		this->genes->push_back(gene);
	}
}

Chromosome::~Chromosome()
{
	//Check if memory is occupied
	if(this->genes != 0)
	{	
		//Free memory
		delete this->genes;
	}
}

int Chromosome::size() const
{
	//Compute the size of the chromosome
	int size = static_cast<int>(this->genes->size());

	return size;
}

void Chromosome::mutate(int sequenceLength)
{
	//Initialize the random seed
	srand(time(NULL));

	//Select two point the chromosome
	int cut_point_a = rand() % (sequenceLength - 1) + 1;
	int cut_point_b = rand() % (sequenceLength - 1) + 1;

	//Set the start and end index
	int start = min(cut_point_a, cut_point_b);
	int end = this->size() - max(cut_point_a, cut_point_b);

	//Mutate the part between start and end
	reverse(this->genes->begin() + start, this->genes->end() - end);
}

string Chromosome::toString() const
{
	int gene = -1;
	ostringstream stream;
	string chromosome = "";

	for(Chromosome::Iterator iter = this->begin(); iter != this->end(); iter++)
	{
		//Extract a gene
		gene = (*this)[iter];

		//Insert the gene in the stream
		stream << gene << "|";
	}

	//Convert the stream in a string
	chromosome = stream.str();

	return chromosome;
}

bool Chromosome::Iterator::operator==(const Chromosome::Iterator &iterator) const
{
	bool equals = false;

	if(this->chromosome == iterator.chromosome && this->cursor == iterator.cursor)
	{
		//The two iterator are at the same point in the same chromosome
		equals = !equals;
	}

	return equals;
}

bool Chromosome::Iterator::operator!=(const Chromosome::Iterator &iterator) const
{
	bool different = !(*this == iterator);

	return different;
}

Chromosome::Iterator Chromosome::Iterator::operator++()
{
	int size = this->chromosome->size();

	//Check if the cursor is in the matrix limits
	if(0 <= this->cursor && this->cursor < size)
	{
		//Move the cursor to the next position
		this->cursor += 1;
	}

	return *this;
}

Chromosome::Iterator Chromosome::Iterator::operator++(int increment)
{
	return ++(*this);
}

Chromosome::Iterator Chromosome::begin() const
{
	//Create an itertor that point to the first gene in the chromosome
	Chromosome::Iterator iterator = this->begin(0);

	return iterator;
}

Chromosome::Iterator Chromosome::begin(int start) const
{
	//Create an empty iterator
	Chromosome::Iterator iterator;

	//Size of the chromosome
	int size = this->size();

	//Link the iterator and the chromosome
	iterator.chromosome = this;

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

Chromosome::Iterator Chromosome::end() const
{
	//Compute the first index outside the chromosome
	int end = this->size();

	//Create an iterator tha point outside the chromosome
	Chromosome::Iterator iterator = this->begin(end);

	return iterator;
}

int Chromosome::operator[](const Chromosome::Iterator &iterator) const
{
	//The gene
	int gene = -1;

	//Extract the cursor from the iterator
	int index = iterator.cursor;

	//The chromosome size
	int size = this->size();

	//Check if the index is in the matrix limits
	if(0 <= index && index < size)
	{
		//Extract the gene
		gene = this->genes->at(index);
	}

	return gene;
}