/*
 * Point2D.cpp
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#include <sstream>
#include <cmath>
#include "Point2D.h"

Point2D::Point2D(const std::string &name, int x, int y):
	Form(name),
	x(x), y(y)
{
}

Point2D::~Point2D() {
}

void Point2D::translate(int deltaX, int deltaY) {
	x += deltaX;
	y += deltaY;
}

std::string Point2D::toString() const {
	std::stringstream res;
	res << getName() << "(" << x << "," << y << ")";
	return res.str();
}

double Point2D::distance(const Point2D &other) const {
	return hypot(x - other.x, y - other.y);
}
