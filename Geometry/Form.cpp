/*
 * Form.cpp
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#include "Form.h"
#include <iostream>

Form::Form(const std::string &name):name(name) {
}

Form::~Form() {
	std::clog << "Form destroyed: " << getName() << std::endl;
}

const std::string& Form::getName() const {
	return name;
}

void Form::setName(const std::string &name) {
	this->name = name;
}

std::optional<std::string> nameFromForm(const Form &form) {
	if (form.getName().empty()) {
		return std::nullopt;  // boite vide
	} else {
		return form.getName(); // conversion implicite
	}
}

Form::Form() noexcept:
	name("")
{
}
