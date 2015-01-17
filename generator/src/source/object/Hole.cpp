#include "src/header/object/Hole.h"

Hole::Hole()
{
	this->abscissa = -1;
	this->ordered = -1;
}

Hole::Hole(int abscissa, int ordered)
{
	this->abscissa = abscissa;
	this->ordered = ordered;
}

int Hole::getAbscissa() const
{
	return this->abscissa;
}

void Hole::setAbscissa(int abscissa)
{
	this->abscissa = abscissa;
}

int Hole::getOrdered() const
{
	return this->ordered;
}

void Hole::setOrdered(int ordered)
{
	this->ordered = ordered;
}

bool Hole::equals(const Hole *hole) const
{
	bool result = false;

	if(hole != 0)
	{
		//Check if two holes are equals or not
		result = (this->getAbscissa() == hole->getAbscissa()) && (this->getOrdered() == hole->getOrdered());
	}

	return result;
}

string Hole::toString() const
{
	ostringstream stream;
	string result = "";
	stream << this->getAbscissa();
	stream << " - ";
	stream << this->getOrdered();
	result = stream.str();
	return result;
}