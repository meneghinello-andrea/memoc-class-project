#ifndef HOLE_H
#define HOLE_H

#include <sstream>
#include <string>

using std::ostringstream;
using std::string;

class Hole
{
	private:
		int abscissa;
		int ordered;

	public:
		Hole();
		Hole(int abscissa, int ordered);

		int getAbscissa() const;
		void setAbscissa(int abscissa);

		int getOrdered() const;
		void setOrdered(int ordered);

		bool equals(const Hole* hole) const;

		string toString() const;
};

#endif //HOLE_H