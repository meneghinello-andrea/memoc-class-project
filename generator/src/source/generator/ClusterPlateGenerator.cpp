#include "src/header/generator/ClusterPlateGenerator.h"

ClusterPlateGenerator::ClusterPlateGenerator(int clusters)
{
	this->setClusters(clusters);
}

int ClusterPlateGenerator::getClusters() const
{
	return this->clusters;
}

void ClusterPlateGenerator::setClusters(int clusters)
{
	if(clusters > 1)
	{
		this->clusters = clusters;
	}
	else
	{
		this->clusters = 3;
	}
}

Plate* ClusterPlateGenerator::generate(int width, int height, int holes) const
{
	int abscissa = -1;
	int ordered = -1;
	int radius = -1;
	Hole *center = 0;
	Hole *hole = 0;
	Plate *plate = 0;

	//Initialize the random seed
	srand(time(NULL));

	if(holes > 3)
	{
		//Create the plate where the holes are created
		plate = new Plate(width, height);

		//Generate each cluster with its holes
		for(int i = 0; i < this->getClusters(); i++)
		{
			//Generate an integer random number between 1 and the width of the plate (abscissa of the center of cluster)
			abscissa = rand() % (plate->getWidth() + 1);

			//Generate an integer random number between 1 and the height of the plate (ordered of the center of cluster)
			ordered = rand() % (plate->getHeight() + 1);

			//Generate an integer random number between 1 and the width of the plate (radius of the cluster)
			radius = rand() % (min(abs(plate->getWidth() - center->getAbscissa()), abs(plate->getHeight() - center->getOrdered())) + 1);

			//Setup the center of the cluster
			center = new Hole(abscissa, ordered);
			abscissa = -1;
			ordered = -1;

			//Generate the (n / cluster) point in the cluster
			for(int j = 0; j < (int)(holes / this->getClusters());)
			{
				//Generate an integer random number between 1 and the width of the plate
				abscissa = rand() % (plate->getWidth() + 1);

				//Generate an integer random number between 1 and the height of the plate
				ordered = rand() % (plate->getHeight() + 1);

				//Setup the hole
				hole = new Hole(ordered, abscissa);

				//Check if the point is inside the cluster
				if(this->check(center, radius, hole) == true)
				{
					//The point is inside then I save it in the plate
					plate->addHole(hole);

					//Increment the number of valid holes
					j += 1;
				}
				else
				{
					//The point isn't inside the cluster then I delete it
					delete hole;
				}
			}
		}

		//Probably there are some holes that are not generated because (holes / cluster) is not divisible
		for(int i = 0; i < (holes % this->getClusters());)
		{
			//Generate an integer random number between 1 and the width of the plate
			abscissa = rand() % (plate->getWidth() + 1);

			//Generate an integer random number between 1 and the height of the plate
			ordered = rand() % (plate->getHeight() + 1);

			//Setup the hole
			hole = new Hole(abscissa, ordered);

			//Check if the point is inside the last cluster
			if(this->check(center, radius, hole) == true)
			{
				//The point is inside then I save it in the plate
				plate->addHole(hole);

				//Increment the number of valid holes
				i += 1;
			}
			else
			{
				//The point isn't inside the last cluster then I delete it
				delete hole;
			}
		}
	}
	
	return plate;
}

bool ClusterPlateGenerator::check(Hole *center, int radius, Hole *hole) const
{
	bool result = false;
	int abscissa = -1;
	int ordered = -1;
	double distance = -1;

	if(center != 0 && radius > 1 && hole != 0)
	{
		//Calculate one of the cathet of the triangle
		abscissa = center->getAbscissa() - hole->getAbscissa();

		//Calculate one of the cathet of the triangle
		ordered = center->getOrdered() - hole->getOrdered();

		//Calculate the euclidean distance from the point and the center of the cluster
		distance = sqrt(pow(abscissa, 2) + pow(ordered, 2));

		//Verify if the point is inside the circle
		result = distance <= radius;
	}

	return result;
}