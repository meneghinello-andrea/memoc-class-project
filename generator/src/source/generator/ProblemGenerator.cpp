#include "src/header/generator/ProblemGenerator.h"

void ProblemGenerator::saveProblem(Plate *plate, vector<double> *costs) const
{
	//Write the coordinate of the holes
	ostringstream stream;
	stream << "data/coordinate_" << plate->getHoleCount() << ".crd";
	this->saveCoordinateData(stream.str(), plate);

	//Clean the stream
	stream.str("");
	stream.clear();

	//Write the cost
	stream << "data/cost_" << plate->getHoleCount() << ".dat";
	this->saveCostData(stream.str(), plate->getHoleCount(), costs);
}

void ProblemGenerator::saveCostData(string fileName, int holesCount, vector<double> *costs) const
{
	double cost = -1;

	//Open the stream
	ofstream costFile(fileName.c_str(), ofstream::out);

	//Write the number of holes
	costFile << holesCount << endl;

	//Write the costs
	for(vector<double>::iterator iter = costs->begin(); iter != costs->end(); ++iter)
	{
		cost = *iter;
		costFile << cost << endl;
	}

	//Close the stream
	costFile.close();
}

void ProblemGenerator::saveCoordinateData(string fileName, Plate *plate) const
{
	Hole *hole = 0;

	//Open the stream
	ofstream coordinateFile(fileName.c_str(), ofstream::out);

	//Write datas
	for(Plate::Iterator iter = plate->begin(); iter != plate->end(); ++iter)
	{
		hole = (*plate)[iter];
		coordinateFile << hole->getAbscissa() << "," << hole->getOrdered() << endl;
	}

	//Close the stream
	coordinateFile.close();
}

void ProblemGenerator::generate(Plate *plate) const
{
	double cost = -1;
	int index = 1;
	Hole *start = 0;
	Hole *end = 0;
	vector<double> *costs = 0;

	if(plate != 0)
	{
		//Data structure where the cost are saved during the problem construction
		costs = new vector<double>();

		//Build the cost only for the upper triangular matrix associated to graph
		for(Plate::Iterator current = plate->begin(); current != plate->end(); ++current)
		{
			start = (*plate)[current];

			for(Plate::Iterator next = plate->begin(index); next != plate->end(); ++next)
			{
				end = (*plate)[next];

				//Generate the cost for two specic holes
				cost = this->generateCost(start, end);

				//Save the cost
				costs->push_back(cost);
			}

			index += 1;
		}
		
		//Save the problem datas on the hard drive
		this->saveProblem(plate, costs);

		//Free memory space
		delete costs;
	}
}