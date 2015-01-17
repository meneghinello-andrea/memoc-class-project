#ifndef PROBLEM_GENERATOR_H
#define PROBLEM_GENERATOR_H

#include <fstream>
#include <sstream>
#include <string>
#include "src/header/object/Hole.h"
#include "src/header/object/Plate.h"

using std::endl;
using std::ofstream;
using std::ostringstream;
using std::string;

class ProblemGenerator
{
	private:
		void saveProblem(Plate *plate, vector<double> *costs) const;
		void saveCostData(string fileName, int holesCount, vector<double> *costs) const;
		void saveCoordinateData(string fileName, Plate *plate) const;

	protected:
		virtual double generateCost(Hole *start, Hole *end) const = 0;

	public:
		void generate(Plate *plate) const;
};

#endif //PROBLEM_GENERATOR_H