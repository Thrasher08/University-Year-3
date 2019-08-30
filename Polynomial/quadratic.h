#pragma once
#include <iostream>
using std::ostream;

class Quadratic {
private:
	double terms[3];

public:
	Quadratic(double term1, double term2, double term3);
	double getTerm(int power);
	Quadratic operator+(Quadratic rhs);
	Quadratic operator-(Quadratic rhs);
	double computeValue(double x);
};

ostream& operator<<(ostream& outStream, Quadratic& quad);