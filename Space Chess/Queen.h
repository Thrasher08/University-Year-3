#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen();
	~Queen();
	Queen(double xCoordinate, double yCoordinate);
	void move(double x, double y);

protected:
	double x;
	double y;
};

