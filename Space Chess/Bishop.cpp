#include "Bishop.h"

Bishop::Bishop(){

}

Bishop::~Bishop() {

}

Bishop::Bishop(double xCoordinate, double yCoordinate) {
	
	pieceType = bishop;
	coll = circle;
	radius = 1;
	xCoordinate = 0;
	yCoordinate = 0;
	//int score = getScore;
}

void Bishop::move(double x, double y) {

	xCoordinate = x;
	yCoordinate = y;

	//Moves diagonally in any direction
	if (x == 0 && y == 0 || x == 0 && y != 0 || x != 0 && y == 0) {

	}
	else if (abs(x) == abs(y)) {
		xCoordinate += x;
		yCoordinate += y;
	}
}
