#ifndef PLATE_GENERATOR_H
#define PLATE_GENERATOR_H

#include "src/header/object/Plate.h"

class PlateGenerator
{
	public:
		virtual Plate* generate(int width, int height, int holes) const = 0;
};

#endif //PLATE_GENERATOR_H