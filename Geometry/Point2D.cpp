/*
 * Point2D.cpp
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#include <sstream>
#include <cmath>
#include <iostream>

#include "Point2D.h"

Point2D::Point2D(const std::string &name, int x, int y):
	Form(name),
	x(x), y(y)
{
}

Point2D::Point2D(const std::string &name):
	Point2D(name,0,0)
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

Point2D::Point2D(const Point2D &other):
	// Point2D(other.getName(), other.x, other.y)
	Form(other), x(other.x), y(other.y)
{
	std::clog << toString() << " constructed by copy" << std::endl;
}

Point2D::Point2D(Point2D &&other):
	Form(other), x(other.x), y(other.y)
{
	// cleanup
	other.setName("_");
	other.x = 0;
	other.y = 0;
	std::clog << toString() << " constructed by move" << std::endl;
}

Point2D& Point2D::operator =(const Point2D &other) {
	this->setName(other.getName());
	this->x = other.x;
	this->y = other.y;
	std::clog << toString() << " assigned by copy" << std::endl;
	return *this;
}

Point2D& Point2D::operator =(Point2D &&other) {
	this->setName(other.getName());
	this->x = other.x;
	this->y = other.y;
	// cleanup
	other.setName("_");
	other.x = 0;
	other.y = 0;
	std::clog << toString() << " assigned by move" << std::endl;
	return *this;
}


double Point2D::distance(const Point2D &other) const {
	return hypot(x - other.x, y - other.y);
}

