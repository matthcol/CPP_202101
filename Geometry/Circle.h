/*
 * Circle.h
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Form.h"
#include "Point2D.h"
#include "Mesurable2D.h"

class Circle: public Form, public Mesurable2D {
private:
	Point2D *center;
	unsigned int radius;
public:
	static constexpr double PI = 3.141592653589793;

	Circle(const std::string &name, Point2D *center, unsigned int radius);
	virtual ~Circle();

	Point2D* getCenter() const;
	unsigned int getRadius() const;

	virtual void translate(int deltaX, int deltaY) override;
	virtual std::string toString() const override;

	virtual double perimeter() const override;
	virtual double surface() const override;
};

#endif /* CIRCLE_H_ */
