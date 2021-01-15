/*
 * main.cpp
 *
 *  Created on: 14 janv. 2021
 *      Author: Matthias
 */

#include <iostream>
#include <vector>
#include <memory>
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

Point2D* creerData() {
	// create data in the heap
	Point2D *res = new Point2D("A",3,4);
	return res;
}

void useData(Point2D *data) {
	data->translate(2,-1);
	std::cout << data->toString() << std::endl;
}

void testAllocationClassic() {
	auto data = creerData();
	useData(data);
	// nettoyer la donnée
	delete data;
}

std::shared_ptr<Point2D> creerDataAuto() {
	// create data in the heap
	std::shared_ptr<Point2D> res(new Point2D("A",3,4));
	std::cout << "[create] Ptr count:" << res.use_count() << std::endl;
	return res;
}

void useDataAuto(std::shared_ptr<Point2D> data) {
	data->translate(2,-1);
	std::cout << data->toString() << std::endl;
	std::cout << "[use] Ptr count:" << data.use_count() << std::endl;
}

void testAllocationAuto() {
	auto data = creerDataAuto();
	std::cout << "[test] Ptr count:" << data.use_count() << std::endl;
	useDataAuto(data);
	std::cout << "[test] Ptr count:" << data.use_count() << std::endl;
} 	// nettoyer la donnée allouée car le compteur de ref de data est à 1

std::shared_ptr<std::vector<std::shared_ptr<Form>>>
creerDataAutoComplex() {
	// create data in the heap
	auto pA = new Point2D("A", 3, 4);
	auto pB = new Point2D("B", 6, 8);
	auto pC = new Point2D("C", 3, 8);
	auto pD = new Point2D("D", 15, 7);
	std::shared_ptr<Form> poly(new Polygon{pA, pB, pC, pD});
	std::shared_ptr<Form> c(new Circle("C1", pA, 2));
	std::shared_ptr<std::vector<std::shared_ptr<Form>>> res(new std::vector<std::shared_ptr<Form>>());
	res->push_back(poly);  // ajout par copie
	res->push_back(c);
	res->push_back(std::shared_ptr<Form>(pA)); // ajout par move
	res->push_back(std::shared_ptr<Form>(pB));
	res->push_back(std::shared_ptr<Form>(pC));
	res->push_back(std::shared_ptr<Form>(pD));
//	std::shared_ptr<Point2D> res();
//	std::cout << "[create] Ptr count:" << res.use_count() << std::endl;
	return res;
}

void useDataAutoComplex(std::shared_ptr<std::vector<std::shared_ptr<Form>>> data) {
	for (auto f: *data) {
		f->translate(2,-1);
		std::cout << f->toString() << std::endl;
		std::cout << "[use] Ptr f count:" << f.use_count() << std::endl;
	}
	std::cout << "[use] Ptr vect count:" << data.use_count() << std::endl;
}

void useDataOptional(std::shared_ptr<std::vector<std::shared_ptr<Form>>> data) {
	for (auto f: *data) {
		auto optName = nameFromForm(*f);
		std::cout << "Form name: " << optName.value_or("?") << std::endl;
		// if (optName) {
		if (optName.has_value()) {
			std::cout << "Form " << f->toString() << " has a name: "
					<< optName.value() << "/"
					<< *optName << std::endl;
		} else {
			std::cout << "Form " << f->toString() << " has no name" << std::endl;
		}
	}
}

void testAllocationAutoComplex() {
	// TODO: passer les summits et center dans le modele object en shared_ptr
	auto data = creerDataAutoComplex();
	std::cout << "[test] Ptr vect count:" << data.use_count() << std::endl;
	useDataAutoComplex(data);
	useDataOptional(data);
	std::cout << "[test] Ptr vect count:" << data.use_count() << std::endl;
}

void testOptionalPoint() {
	Point2D pA("A", 3, 4);
	std::optional<std::reference_wrapper<Point2D>> optPointRef{pA}; // une reference du point est copiée dans la boite
	std::optional<Point2D> optPoint(pA); // un nouveau point "copié" dans la boite
	std::cout << optPoint->getName() << std::endl;
	std::cout << optPointRef->get().getName() << std::endl;
}

void testMovePoint2D() {
	Point2D pA("A", 3, 4);
	Point2D pB(pA); // constructeur par copie
	std::cout << pA.toString() << " / "
				<< pB.toString() << std::endl;
	pB = pA; // operateur d'assignation par copie
	std::cout << pA.toString() << " / "
				<< pB.toString() << std::endl;
	pB = Point2D("B", 5,6); // operation d'assignation par move
	std::cout << pA.toString() << " / "
			<< pB.toString() << std::endl;
	pB = std::move(pA); // pA est un terme gauche est transformé en terme droit
	std::cout << pA.toString() << " / "
				<< pB.toString() << std::endl;
}

void testMovePolygon() {
	Point2D pA("A", 3, 4);
	Point2D pB("B", 5, 6);
	Point2D pC("C", 7, 8);
	Point2D pD("D", 9, 10);
	Point2D pE("E", 11, 12);
	Polygon poly1{&pA, &pB, &pC};
	Polygon poly2{&pB, &pC, &pA};
	std::cout << poly1.toString() << " / "
				<< poly2.toString() << std::endl;

	poly2 = poly1;
	poly1.setSummit(0, &pD);
	std::cout << poly1.toString() << " / "
				<< poly2.toString() << std::endl;

	poly2 = std::move(poly1);
	poly2.setSummit(2, &pE);
	std::cout   << poly1.toString() << " / "
				<< poly2.toString() << std::endl;

	std::vector<Polygon> polygons;
	polygons.push_back(std::move(poly2));
	polygons.push_back(Polygon{&pA, &pB, &pC});
}

void testBadUsagePolygon() {
	Point2D pA("A", 3, 4);
	Point2D pB("B", 3, 4);
	Point2D pC("C", 3, 4);
	// Polygon p0{};
	// Polygon p1{&pA};
	//Polygon p2{&pA, &pB};
	//Polygon p3{&pA, &pB, &pC};
	std::vector<unsigned int> radiis{4,3,2,1,0,1,2,3,4};
	for (unsigned int r: radiis) {
		try {
			Circle c("C", &pB, r);
			std::cout << c.toString() << std::endl;
		} catch (std::invalid_argument &e) {
			std::cerr << "Circle not constructed: " << e.what() << std::endl;
		}
	}
	//auto r = radiis.at(10);
	//	auto r = radiis[10];
	//	std::cout << "Wrong radius: " << r << std::endl;
}

void playWithPoint2D(Point2D p) {
	std::cout << p.toString() << std::endl;
}

void testExplicitPoint2D() {
	// Point2D p("A");
	std::string n("A");
//	Point2D p = n; // implicit conversion string => Point2D or forbiden is explicit constructor
//	std::cout << p.toString() << std::endl;
	playWithPoint2D(n); // implicit conversion string => Point2D or forbiden is explicit constructor
}

int main() {
	std::cout << "Test POO on Geometry Model" <<std::endl;
	// std::cout << "PI = " << Circle::PI << std::endl;
	// testInheritance();
	// testSegment();
	// testCopieForms();
	//testAllocationClassic();
	// testAllocationAuto();
	// testAllocationAutoComplex();
	// testOptionalPoint();
	// testMovePoint2D();
	// testMovePolygon();
	//testBadUsagePolygon();
	testExplicitPoint2D();
}


