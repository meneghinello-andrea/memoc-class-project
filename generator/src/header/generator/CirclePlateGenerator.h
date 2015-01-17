#ifndef CIRCLE_PLATE_GENERATOR_H
#define CIRCLE_PLATE_GENERATOR_H

#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include "src/header/generator/PlateGenerator.h"
#include "src/header/object/Hole.h"
#include "src/header/object/Plate.h"

using std::min;

class CirclePlateGenerator : public PlateGenerator
{
	public:
		virtual Plate* generate(int width, int height, int holes) const;	
};

#endif //CIRCLE_PLATE_GENERATOR_H