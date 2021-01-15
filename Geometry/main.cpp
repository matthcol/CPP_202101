/*
 * main.cpp
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#include <iostream>
#include <vector>
#include "Form.h"
#include "Circle.h"
#include "Point2D.h"
#include "Polygon.h"
#include "Segment.h"

void testInheritance(){
	Point2D pA("A", 3, 4);
	Point2D pB("B", 6, 8);
	Point2D pC("C", 3, 8);
	std::vector<Point2D*> points{&pA, &pB, &pC};
	Circle c1("C1", &pA, 2);
	Circle c2("C2", &pA, 3);
	Polygon p1{&pA, &pB, &pC}; // with initializer_list
	Polygon p2("ABC_2", points.begin(), points.end()); // with iterators
	//const Form &f = Polygon{&pC, &pB, &pA};
	Form *f_ptr = new Polygon{&pC, &pB, &pA};
	std::vector<Form*> forms{&pA, &pB, &pC, &c1, &c2, &p1, &p2, f_ptr};

	// substitution uniquement en mode reference et pointer
	// Form *f_ptr = &pA;
	// Form &f = pA;

	// display all forms
	for (auto form_ptr: forms) {
		std::cout << " - " << form_ptr->toString() << std::endl;
	}

//	// translate all forms
//	for (auto form_ptr: forms) {
//		form_ptr->translate(2,  -5);
//	}
//
//	// display all forms
//	for (auto form_ptr: forms) {
//			std::cout << " - " << form_ptr->toString() << std::endl;
//	}

	// downcasting vers Circle*
	for (auto form_ptr: forms) {
		auto circle_ptr = dynamic_cast<Circle*>(form_ptr);
		if (circle_ptr != nullptr) {
			std::cout << "Circle of radius: " << circle_ptr->getRadius() << std::endl;
		}
	}

	// downcasting vers Mesurable2D*
	for (auto form_ptr: forms) {
		auto mesurable2d_ptr = dynamic_cast<Mesurable2D*>(form_ptr);
		if (mesurable2d_ptr != nullptr) {
			std::cout << "Form mesurable2D: " << std::endl;
			std::cout << "\t- perimeter: " << mesurable2d_ptr->perimeter()  << std::endl;
			std::cout << "\t- surface: " << mesurable2d_ptr->surface()  << std::endl;
		}
	}

	// désallocation mémoire
	delete f_ptr; // polygon + tableau de sommets via son destructeur
}

void testSegment() {
	Segment s1; // appelle le constructeur par défaut implicite
	s1.z = 2;
	Segment s2(s1); // constructeur par copie
	Segment s3;
	s3 = s1; // opérateur de copie
	std::cout << s1.z << " " << s2.z << " "<< s3.z << std::endl;
} // destructeur implicite appelé

void testCopieForms() {
	Point2D pA("A", 3, 4);
	Point2D pB("B", 6, 8);
	Point2D pC("C", 3, 8);
	Point2D pD("D", 15, 7);
	Polygon pABC{&pA, &pB, &pC};
	pABC.setName("ABC");
	Polygon pCBA{&pC, &pB, &pA};
	pCBA.setName("CBA");
	// copies
	Point2D pAbis(pA);
	std::cout << pAbis.toString() << std::endl;
	pAbis = pB;
	std::cout << pAbis.toString() << std::endl;
	Polygon pABCbis = pABC; // constructeur par copie
	std::cout << pABCbis.toString() << std::endl;
	pABCbis = pCBA; // operateur par copie
	std::cout << pABCbis.toString() << std::endl;
	pABCbis.setSummit(0, &pD);
	std::cout << pABCbis.toString() << std::endl;
	std::cout << pCBA.toString() << std::endl;
}

int main() {
	// std::cout << "PI = " << Circle::PI << std::endl;
	// testInheritance();
	// testSegment();
	testCopieForms();
}


