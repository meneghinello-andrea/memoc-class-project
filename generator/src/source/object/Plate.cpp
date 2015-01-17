#include "src/header/object/Plate.h"

Plate::Plate(int width, int height)
{
	this->setWidth(width);
	this->setHeight(height);
	this->holes = new vector<Hole*>();
}

Plate::~Plate()
{
	for(Plate::Iterator iter = this->begin(); iter != this->end(); iter++)
	{
		delete (*this)[iter];
	}
	delete this->holes;
}

int Plate::getWidth() const
{
	return this->width;
}

void Plate::setWidth(int width)
{
	if(width > 0)
	{
		this->width = width;
	}
}

int Plate::getHeight() const
{
	return this->height;
}

void Plate::setHeight(int height)
{
	if(height > 0)
	{
		this->height = height;
	}
}

int Plate::getHoleCount() const
{
	int count = static_cast<int>(this->holes->size());
	return count;
}

void Plate::addHole(Hole *hole)
{
	if(hole != 0)
	{
		this->holes->push_back(hole);
	}
}

bool Plate::Iterator::operator==(Iterator iterator) const
{
	bool result = this->cursor == iterator.cursor;
	return result;
}

bool Plate::Iterator::operator!=(Iterator iterator) const
{
	bool result = !(*this == iterator);
	return result;
}

Plate::Iterator& Plate::Iterator::operator++()
{
	if(this->cursor >= 0 && this->cursor < this->plate->getHoleCount())
	{
		this->cursor += 1;
	}
	return *this;
}

Plate::Iterator& Plate::Iterator::operator++(int increment)
{
	return ++(*this);
}

Plate::Iterator Plate::begin() const
{
	return this->begin(0);
}

Plate::Iterator Plate::begin(int start_index) const
{
	Plate::Iterator iterator;
	iterator.plate = this;
	iterator.cursor = start_index;
	return iterator;
}

Plate::Iterator Plate::end() const
{
	Plate::Iterator iterator;
	iterator.plate = this;
	iterator.cursor = this->getHoleCount();
	return iterator;
}

Hole* Plate::operator[](Plate::Iterator iterator) const
{
	Hole *hole = 0;
	int index = iterator.cursor;
	if(index >= 0 && index < this->getHoleCount())
	{
		hole = this->holes->at(index);
	}
	return hole;
}