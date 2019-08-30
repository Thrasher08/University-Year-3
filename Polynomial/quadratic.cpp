#include "Quadratic.h"

using namespace std;

//Defines a Quadratic object
Quadratic::Quadratic(double term1, double term2, double term3) {
	terms[0] = term1;
	terms[1] = term2;
	terms[2] = term3;
}

double Quadratic::getTerm(int power){

	//Error checking: power is greater or less than length of quadratic return NULL
	if (power > 2 || power < 0) {
		return NULL;
	}

	//Reutns the correct co-effecient (i.e. power = 2 returns term 0)
	return terms[2 -power];
}

Quadratic Quadratic::operator+(Quadratic rhs){
	Quadratic addQuad = Quadratic(1,1,1);

	//Cycle through terms
	for (int i = 0; i <= 2; i++) {
		addQuad.terms[i] = this->terms[i] + rhs.terms[i];	//adds the same term of both quads together
	}

	return addQuad;
}

Quadratic Quadratic::operator-(Quadratic rhs) {
	Quadratic subQuad = Quadratic(1, 1, 1);

	//Cycle through terms
	for (int i = 0; i <= 2; i++) {
		subQuad.terms[i] = this->terms[i] - rhs.terms[i];	//subtracts the same term of both quads together
	}

	return subQuad;
}

double Quadratic::computeValue(double x) {
	double valueQuad = 0;

	//Cycle through terms
	for (int i = 0; i <= 2; i++) {
		valueQuad += terms[i] * pow(x, i);		// Multiply the term with defined X and power and then add all together
	}

	return valueQuad;
}

//Allows quadratics to be written out by the cout operator
ostream& operator<<(ostream& outStream, Quadratic& quad) {
	
	//Writes out each term
	outStream << quad.getTerm(0) << "X^2 + "
		<< quad.getTerm(1) << "X^1 + "
		<< quad.getTerm(2) << "X^0 ";

	return outStream;
}