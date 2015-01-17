#ifndef CLUSTER_PLATE_GENERATOR_H
#define CLUSTER_PLATE_GENERATOR_H

#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "src/header/generator/PlateGenerator.h"
#include "src/header/object/Hole.h"
#include "src/header/object/Plate.h"

using std::min;

class ClusterPlateGenerator : public PlateGenerator
{
	private:
		int clusters;

		bool check(Hole *center, int radius, Hole *hole) const;

	public:
		ClusterPlateGenerator(int clusters);

		int getClusters() const;
		void setClusters(int clusters);

		virtual Plate* generate(int width, int height, int holes) const;
};

#endif //CLUSTER_PLATE_GENERATOR_H