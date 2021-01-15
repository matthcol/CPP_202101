/*
 * Circle.cpp
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#include "Circle.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

Circle::Circle(const std::string &name, Point2D *center, unsigned int radius):
		Form(name),
		center(center),
		radius(radius)
{
	if (radius == 0){
		throw std::invalid_argument("radius of a circle must be positive");
	}
}

Circle::~Circle() {
	//std::clog << "Circle destroyed: " << getName() << std::endl;
}

Point2D* Circle::getCenter() const {
	return center;
}

unsigned int Circle::getRadius() const {
	return radius;
}

void Circle::translate(int deltaX, int deltaY) {
	center->translate(deltaX, deltaY);
}

std::string Circle::toString() const {
	std::stringstream res;
	res << getName() << "<" << center->getName() << "," << radius << ">";
	return res.str();
}

double Circle::perimeter() const {
	return 2*PI*radius;
}

double Circle::surface() const {
	return PI*radius*radius;
}
