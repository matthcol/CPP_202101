/*
 * Mesurable2D.h
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#ifndef MESURABLE2D_H_
#define MESURABLE2D_H_

// interface (UML) i.e pure virtual class (C++)
class Mesurable2D {
public:
	virtual ~Mesurable2D();

	virtual double perimeter() const=0;
	virtual double surface() const=0;
};

#endif /* MESURABLE2D_H_ */
