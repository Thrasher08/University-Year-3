#include "Queen.h"

Queen::Queen(){

}

Queen::~Queen() {

}

Queen::Queen(double xCoordinate, double yCoordinate) {
	
	pieceType = queen;
	coll = circle;
	radius = 1;
	xCoordinate = 0;
	yCoordinate = 0;
	//int score = getScore;
}

void Queen::move(double x, double y) {

	xCoordinate = x;
	yCoordinate = y;

	if (x == 0 && y == 0) {

	}

	//Move in bishop directions
	else if (abs(x) == abs(y) && (x == 0 && y != 0 || x != 0 && y == 0)) {
		xCoordinate += x;
		yCoordinate += y;
	}

	//Move in rook directions
	else if(x == 0 && y != 0 || x != 0 && y == 0) {
		xCoordinate += x;
		yCoordinate += y;
	}
}