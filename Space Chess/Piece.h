#pragma once
#include <cmath>
#include <math.h>

enum collType {square, circle};
enum pType {rook, bishop, queen};

class Piece
{
public:
	Piece();
	pType getPieceName();
	collType getColl();
	int getSide();
	double getXCord();
	double getYCord();
	int getRadius();
	virtual void move(double xCoordinate, double yCoordinate) = 0;
	double distance(Piece * p1, Piece * p2);
	bool hasCollided(Piece * p1, Piece * p2);

protected:

	int sideLength;
	int radius;
	double xCoordinate;
	double yCoordinate;
	pType pieceType;
	collType coll;

};

