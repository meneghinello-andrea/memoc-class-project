#ifndef PLATE_H
#define PLATE_H

#include <vector>
#include "src/header/object/Hole.h"

using std::vector;

class Plate
{
	private:
		int width;
		int height;
		vector<Hole*> *holes;

	public:
		Plate(int width = 100, int height = 100);
		~Plate();

		int getWidth() const;
		void setWidth(int width);

		int getHeight() const;
		void setHeight(int height);

		int getHoleCount() const;

		void addHole(Hole *hole);

		class Iterator
		{
			friend class Plate;

			private:
				const Plate *plate;
				int cursor;

			public:
				bool operator==(Iterator iterator) const;
				bool operator!=(Iterator iterator) const;

				Iterator& operator++();							//Prefix ++ operator
				Iterator& operator++(int increment);			//Postfix ++ operator
		};

		Plate::Iterator begin() const;
		Plate::Iterator begin(int start_index) const;
		Plate::Iterator end() const;
		Hole* operator[](Plate::Iterator iterator) const;
};

#endif //PLATE_H