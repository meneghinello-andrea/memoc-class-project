#include "src/header/generator/CirclePlateGenerator.h"

Plate* CirclePlateGenerator::generate(int width, int height, int holes) const
{
	double angle = 0;
	double theta = -1;
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

		//generate the abscissa of the center of the circle
		abscissa = rand() % (plate->getWidth() + 1);

		//generate the ordered of the center of the circle
		ordered = rand() & (plate->getHeight() + 1);

		//Setup the center of the circle
		center = new Hole(abscissa, ordered);

		//generate the radius (I want a circle inside of the plate)
		radius = rand() % (min(abs(plate->getWidth() - center->getAbscissa()), abs(plate->getHeight() - center->getOrdered())) + 1);

		//Setup the increment angle
		theta = (2 * M_PI) / holes;

		//Generate the holes in the circumference
		for(int i = 0; i < holes; i += 1)
		{
			//Calculate the abscissa of the hole
			abscissa = (cos(angle) * radius) + center->getAbscissa();

			//Calculate the ordered of the hole
			ordered = (sin(angle) * radius) + center->getOrdered();

			//setup the hole
			hole = new Hole(abscissa, ordered);

			//Add the hole in the plate
			plate->addHole(hole);

			//Increment the angle for the next hole
			angle += theta;
		}

		//Free memory
		delete center;
	}
	
	return plate;
}