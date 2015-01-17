#include "src/header/generator/EuclideanProblemGenerator.h"

double EuclideanProblemGenerator::generateCost(Hole *start, Hole *end) const
{
	double distance = -1;
	int abscissa = -1;
	int ordered = -1;

	if(start != 0 && end != 0)
	{
		//Get one cathet of the rectangular triangle
		abscissa = end->getAbscissa() - start->getAbscissa();

		//Get one cathet of the rectangular triangle
		ordered = end->getOrdered() - start->getOrdered();

		//Calculate the euclidean distance from the two holes
		distance = sqrt(pow(abscissa, 2) + pow(ordered, 2));
	}

	return distance;
}