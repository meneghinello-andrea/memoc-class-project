#ifndef RANDOM_PLATE_GENERATOR
#define RANDOM_PLATE_GENERATOR

#include <stdlib.h>
#include <time.h>
#include "src/header/generator/PlateGenerator.h"
#include "src/header/object/Hole.h"
#include "src/header/object/Plate.h"

class RandomPlateGenerator : public PlateGenerator
{
	public:
		virtual Plate* generate(int width, int height, int holes) const;
};

#endif //RANDOM_PLATE_GENERATOR