/*
 * Form.h
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#ifndef FORM_H_
#define FORM_H_

#include <string>

// abstract class (at least one abstract method)
class Form {
private:
	std::string name;
public:
	Form(const std::string &name);
	virtual	~Form();

	const std::string& getName() const;
	void setName(const std::string &name);

	// abstract method (uml) i.e. pure virtual method (c++)
	virtual void translate(int deltaX, int deltaY)=0;
	virtual std::string toString() const=0;
};

#endif /* FORM_H_ */
