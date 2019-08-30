#include <iostream>
#include "quadratic.h"
#include "polynomial.h"

using namespace std;

int main() {

	//Define Variables

	Quadratic quad1 = Quadratic(3, 2, 4);
	Quadratic quad2 = Quadratic(2, 5, 1);

	double* testPA = new double[4]{ 4, 7, 2, 5 };
	Polynomial poly1 = Polynomial(testPA, 4);	// 4x^2 + 7X^1 + 2X^3 + 5
	double* testPA2 = new double[4]{ 2, 3, 1, 4 };
	Polynomial poly2 = Polynomial(testPA2, 4);	// 2x^2 + 3X^1 + 1X^3 + 4

	int xInput;

	//Testing
	//Quadratic Testing
	cout << "Quadratic=========================================================== " << endl;
	cout << "Quad 1: " << quad1 << endl;
	cout << "Please enter a power of X to return it's co-efficient" << endl;					

	cin >> xInput;																//User inputs a power						
	double testTerm = quad1.getTerm(xInput);									//Puts co-efficent into printable format
													
	cout << testTerm  << endl;													//Prints co-efficent

	//Print quads
	cout << "Quad 1: " << quad1 << endl;
	cout << "Quad 2 " << quad2 << endl;

	cout << "Add: " << (quad1 + quad2) << endl;									//Returns quads added together
	cout << "Subtract: " << (quad1 - quad2) << endl;							//Returns quads subtracted from eachother

	cout << "Please enter a value for X" << endl;
	cin >> xInput;
	cout << quad1 << endl;
	cout << "Value of Quadratic: " << (quad1.computeValue(xInput)) << endl;
	cout << "==================================================================== " << endl;

	//Polynomial Testing
	cout << "Polynomial========================================================== " << endl;
	cout << "Poly 1: " << poly1 << endl;
	cout << "Please enter a power of X to return it's co-efficient" << endl;
	
	cin >> xInput;
	double testTerm2 = poly1.getTerm(xInput);
	
	cout << testTerm2 << endl;

	//Print polys
	cout << "Poly 1: " << poly1 << endl;										
	cout << "Poly 2 " << poly2 << endl;											

	cout << "Add: " << (poly1 + poly2) << endl;									//Returns polys added together
	cout << "Subtract: " << (poly1 - poly2) << endl;							//Returns polys subtracted from eachother

	return 0;
}