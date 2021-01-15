/*
 * Polygon.cpp
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#include "Polygon.h"
#include <sstream>
#include <iostream>
#include <algorithm>

Polygon::Polygon(std::initializer_list<Point2D*> summits):
	Polygon("", summits.begin(), summits.end())
{
}

Polygon::~Polygon() {
	//std::clog << "Polygon destroyed" << std::endl;
	delete[] summits;
}

void Polygon::translate(int deltaX, int deltaY) {
	std::for_each(summits, summits+size,
			[deltaX, deltaY](auto summit_ptr){summit_ptr->translate(deltaX, deltaY);}
	);
}

double Polygon::surface() const {
	// somme des surfaces de triangles
	// => formule la Héron
	// https://fr.wikipedia.org/wiki/Formule_de_H%C3%A9ron
	// TODO
	return 0.0;
}

void Polygon::setSummit(unsigned int index, Point2D *summit) {
	summits[index] = summit;
}

Point2D* Polygon::getSummit(unsigned int index) const {
	return summits[index];
}


double Polygon::perimeter() const {
	double res=0.0;
//	for (unsigned int i=0; i<size; ++i) {
//		res += summits[i]->distance(*summits[(i+1)%size]);
//	}
	// le précédent du dernier est le premier
	Point2D *pre_summit_ptr = summits[size-1];
	for (unsigned int i=0; i<size; ++i) {
		Point2D *curr_summit_ptr = summits[i];
		res += curr_summit_ptr->distance(*pre_summit_ptr);
		pre_summit_ptr = curr_summit_ptr;
	}
	return res;
}

std::string Polygon::toString() const {
	std::stringstream res;
	res << getName() << "{";
	for (unsigned int i=0; i<size; ++i) {
		res << summits[i]->getName() << " ";
	}
	res << "}#" << size;
	return res.str();
}

Polygon::Polygon(const Polygon &other):
	Polygon(other.getName(),other.summits, other.summits+other.size)
{
}

Polygon::Polygon(Polygon &&other):
	Form(other), summits(other.summits), size(other.size)
{
	// cleanup source
	other.summits = nullptr;
	other.size = 0;
}

Polygon& Polygon::operator =(const Polygon &other) {
	setName(other.getName());
	replaceSummits(other.summits, other.summits+other.size);
	return *this;
}

Polygon& Polygon::operator =(Polygon &&other) {
	setName(other.getName());
	this->summits = other.summits;
	this->size = other.size;
	// cleanup source
	other.summits = nullptr;
	other.size = 0;
	return *this;
}
