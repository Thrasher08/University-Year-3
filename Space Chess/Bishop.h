#pragma once
#include "Piece.h"
#include <math.h>

class Bishop : public Piece
{
public:
	Bishop();
	~Bishop();
	Bishop(double xCoordinate, double yCoordinate);
	void move(double x, double y);

protected:
	double x;
	double y;
};

