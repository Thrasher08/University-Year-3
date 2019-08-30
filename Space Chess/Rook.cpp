#include "Rook.h"

Rook::Rook(){

}

Rook::~Rook(){

}

Rook::Rook(double xCoordinate, double yCoordinate) {
	pieceType = rook;
	coll = square;
	sideLength = 2;
	xCoordinate = 0;
	yCoordinate = 0;
	//int score = getScore;
}

void Rook::move(double x, double y){
	
	xCoordinate = x;
	yCoordinate = y;

	//Moves horizontally or vertically
	if (x == 0 && y == 0 || x != 0 && y != 0) {
		
	}
	else {

		xCoordinate += x;
		yCoordinate += y;

	}
}