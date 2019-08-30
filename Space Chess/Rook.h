#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook();
	~Rook();
	Rook(double xCoordinate, double yCoordinate);
	void move(double x, double y);

protected:
	double x;
	double y;
};

