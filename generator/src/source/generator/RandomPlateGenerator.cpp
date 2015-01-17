#include "src/header/generator/RandomPlateGenerator.h"

Plate* RandomPlateGenerator::generate(int width, int height, int holes) const
{
	int abscissa = -1;
	int ordered = -1;
	Hole *hole = 0;
	Plate *plate = 0;

	//Initialize the random seed
	srand(time(NULL));

	if (holes > 3)
	{
		plate = new Plate(width, height);

		for(int i = 0; i < holes; i++)
		{
			//Generate an integer random number between 1 and the width of the plate
			abscissa = rand() % (plate->getWidth() + 1);

			//Generate an integer random number between 1 and the height of the plate
			ordered = rand() % (plate->getHeight() + 1);

			//Create the hole
			hole = new Hole(abscissa, ordered);

			//Add the new hole to the plate
			plate->addHole(hole);
		}
	}
	
	return plate;
}