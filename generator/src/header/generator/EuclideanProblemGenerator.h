#ifndef EUCLIDEAN_PROBLEM_GENERATOR_H
#define EUCLIDEAN_PROBLEM_GENERATOR_H

#include <math.h>
#include "src/header/object/Hole.h"
#include "src/header/generator/ProblemGenerator.h"

class EuclideanProblemGenerator : public ProblemGenerator
{
	protected:
		virtual double generateCost(Hole *start, Hole *end) const;
};

#endif //EUCLIDEAN_PROBLEM_GENERATOR_H