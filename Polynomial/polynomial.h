#pragma once
#include <iostream>

using std::istream;
using std::ostream;
class Polynomial {
private:
	double *terms;
	int length;

public:
	Polynomial();
	~Polynomial();
	Polynomial(double* arrT, int length);
	Polynomial operator+(Polynomial rhs);
	Polynomial operator-(Polynomial rhs);
	Polynomial operator*(Polynomial rhs);
	double computePolyValue(double x);
	double getTerm(int power);

	friend ostream& operator<<(ostream& outStream, Polynomial& poly);
};

