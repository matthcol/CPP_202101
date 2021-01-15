/*
 * Point2D.h
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#ifndef POINT2D_H_
#define POINT2D_H_

#include "Form.h"

class Point2D: public Form {
private:
	int x;
	int y;
public:
	Point2D(const std::string &name, int x, int y);
	virtual ~Point2D();

	virtual void translate(int deltaX, int deltaY) override;
	virtual std::string toString() const override;

	double distance(const Point2D &other) const;
};

#endif /* POINT2D_H_ */
