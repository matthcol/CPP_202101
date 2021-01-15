/*
 * Polygon.h
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include "Form.h"
#include "Mesurable2D.h"
#include "Point2D.h"

#include <iterator>
#include <stdexcept>
#include <algorithm>

class Polygon: public Form, public Mesurable2D {
private:
	// dynamic array
	Point2D** summits;
	unsigned int size;
public:
	typedef Point2D** iterator;
	// Polygon() =default;

	Polygon(std::initializer_list<Point2D*> summits);

	template<class InputIterator>
	Polygon(const std::string &name, InputIterator first, InputIterator last):
		Form(name),
		summits(nullptr),
		size(0)
	{
		replaceSummits(first, last);
	}

	// Polygon(const Polygon &other) =delete;
	Polygon(const Polygon &other);
	// Polygon(Polygon &&other) =delete;
	Polygon(Polygon &&other);
	// Polygon& operator=(const Polygon &other) =delete;
	Polygon& operator=(const Polygon &other);
	Polygon& operator=(Polygon &&other);

	virtual ~Polygon();

	void setSummit(unsigned int index, Point2D* summit);
	Point2D* getSummit(unsigned int index) const;

	iterator begin() {
		return summits;
	}

	iterator end() {
		return summits+size;
	}

	template<class InputIterator>
	void replaceSummits(InputIterator first, InputIterator last) {
		unsigned int size = std::distance(first,last);
		if (size < 3) {
			throw std::invalid_argument("not enough summits");
		}
		if (summits != nullptr) {
			delete[] summits;
		}
		summits = new Point2D*[size];
		std::copy(first, last, summits);
		this->size = size;
	}

	virtual void translate(int deltaX, int deltaY) override;
	virtual std::string toString() const override;

	virtual double surface() const override;
	virtual double perimeter() const override;

};

#endif /* POLYGON_H_ */
