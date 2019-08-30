#include "Polynomial.h"

using namespace std;

//Defined a Polynomial object
Polynomial::Polynomial() {
	length = 4;
	double *arr = new double[length] {4, 7, 2, 5};
	terms = arr;
}

//Deconstructs a Polynomial object
Polynomial::~Polynomial() {
	delete[] terms;
}

Polynomial::Polynomial(double* arrT, int length) {
	terms = new double[length];
	this->length = length;
	for (int i = 0; i < length; i++) {
		terms[i] = arrT[i];
	}
}

double Polynomial::getTerm(int power) {

	//Error checking if the power is less than 0, power is not a polynomial, return NULL
	if (power < 0) {
		return NULL;
	}

	//Reutns the correct co-effecient (i.e. power = 2 returns term 0)
	return this->terms[this->length - power - 1];
}

Polynomial Polynomial::operator+(Polynomial rhs) {
	double *addArr = new double[4] { 1, 1, 1, 1 };
	Polynomial addPoly = Polynomial(addArr, 4);
	for (int i = 0; i <= 3; i++) {
		addPoly.terms[i] = this->terms[i] + rhs.terms[i];
	}

	return addPoly;
}

Polynomial Polynomial::operator-(Polynomial rhs) {
	double *subArr = new double[4]{ 1, 1, 1, 1 };
	Polynomial subPoly = Polynomial(subArr, 4);
	for (int i = 0; i <= 3; i++) {
		subPoly.terms[i] = this->terms[i] - rhs.terms[i];
	}

	return subPoly;
}

Polynomial Polynomial::operator*(Polynomial rhs) {
	double *mulArr = new double[4]{ 1, 1, 1, 1 };
	Polynomial mulPoly = Polynomial(mulArr, 4);
	for (int i = 0; i <= 3; i++) {
		mulPoly.terms[i] = this->terms[i] * rhs.terms[i];
	}

	return mulPoly;
}

/*double computePolyValue(double x) {
	double *valArr = new double[4]{ 1, 1, 1, 1 };
	Polynomial valPoly = Polynomial(valArr, 4);
	for (int i = 0; i <= 2; i++) {
		valPoly += terms[i] * pow(x, i);
	}

	return valPoly;
}*/

//Allows polynomials to be written out by the cout operator
ostream& operator<<(ostream& outStream, Polynomial& poly) {
	for (int i = 0; i < poly.length; i++) {
		outStream << poly.getTerm(poly.length-i-1) << "X";
	}


	return outStream;
}

ostream& operator>>(ostream& inStream, Polynomial& poly) {
	//inStream >>	//FIX

	return inStream;
}