#include <iostream>
#include <string>
#include "src/header/generator/CirclePlateGenerator.h"
#include "src/header/generator/ClusterPlateGenerator.h"
#include "src/header/generator/EuclideanProblemGenerator.h"
#include "src/header/generator/PlateGenerator.h"
#include "src/header/generator/ProblemGenerator.h"
#include "src/header/generator/RandomPlateGenerator.h"
#include "src/header/object/Plate.h"

using std::cout;
using std::endl;
using std::string;

int selectGenerator(string choice)
{
	int result = -1;

	if(choice.compare("RANDOM") == 0)
	{
		result = 1;
	}

	if(choice.compare("CLUSTER") == 0)
	{
		result = 2;
	}

	if(choice.compare("CIRCLE") == 0)
	{
		result = 3;
	}

	return result;
}

int main(int argc, char* argv[])
{
	//Object that generate a plate
	PlateGenerator *plate_gen = 0;

	//Object that generate the problem datas
	ProblemGenerator *problem_gen = 0;

	//The plate
	Plate *plate = 0;

	//Used to select the generator type
	int type = -1;

	if((argc - 1 ) >= 3)
	{
		//The type of the generator selected by the user
		type = selectGenerator(argv[1]);

		switch(type)
		{
			case 1:
				{
					//RANDOM POINT

					int width = atoi(argv[2]);
					int height = atoi(argv[3]);
					int holes = atoi(argv[4]);

					plate_gen = new RandomPlateGenerator();
					problem_gen = new EuclideanProblemGenerator();

					//Generate a new plate
					plate = plate_gen->generate(width, height, holes);

					//Generate the problem datas
					problem_gen->generate(plate); 
				}
			break;

			case 2:
				{
					//CLUSTER POINT

					int width = atoi(argv[2]);
					int height = atoi(argv[3]);
					int clusters = atoi(argv[4]);
					int holes = atoi(argv[5]);

					plate_gen = new ClusterPlateGenerator(clusters);
					problem_gen = new EuclideanProblemGenerator();

					//Generate a new plate
					plate = plate_gen->generate(width, height, holes); 

					//Generate the problem datas
					problem_gen->generate(plate);
				}
			break;
			case 3:
				{
					//CIRCLE POINT

					int width = atoi(argv[2]);
					int height = atoi(argv[3]);
					int holes = atoi(argv[4]);

					plate_gen = new CirclePlateGenerator();
					problem_gen = new EuclideanProblemGenerator();

					//Generate a new plate
					plate = plate_gen->generate(width, height, holes);

					//Generate the problem datas
					problem_gen->generate(plate); //PROBLEMA NELLA GENERAZIONE SCOPRIRE
				}
			break;
		}

		//Free memory
		delete plate;
		delete problem_gen;
		delete plate_gen;
	}
	else
	{
		cout << "Numero di parametri in ingresso insufficienti" << endl;
		cout << "Richiesti:" << endl;
		cout << "1) Random: RANDOM larghezza altezza num_punti" << endl;
		cout << "2) Cluster: CLUSTER larghezza altezza num_cluster num_punti" << endl;
		cout << "3) Circle: CIRCLE larghezza altezza num_punti" << endl;
	}

	return 0;
}