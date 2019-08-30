#include "Piece.h"
#include <String>

Piece::Piece(){

}

pType Piece::getPieceName() {
	return pieceType;
}

collType Piece::getColl() {
	return coll;
}

int Piece::getSide() {
	return sideLength;
}
double Piece::getXCord() {
	return xCoordinate;
}
double Piece::getYCord() {
	return yCoordinate;
}

int Piece::getRadius() {
	return radius;
}

//Measures the difference between pieces
double Piece::distance(Piece * p1, Piece * p2) {
	
	double spaceBetween;
	double x1 = p1->getXCord();
	double x2 = p2->getXCord();
	double y1 = p1->getYCord();
	double y2 = p2->getYCord();

		return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2 ));
}


//Check for collision
bool Piece::hasCollided(Piece * p1, Piece * p2) {

	double pDist = distance(p1, p2);

	if (pDist > 3) {
		return false;
	}

	//Piece has collided
	else if (pDist < 2) {
		return true;
	}

	if (p1->getColl() == circle && p2->getColl() == circle) {
		return false;
	}

	//Check for two square collisions
	else if (p1->getColl() == square && p2->getColl() == square) {
		
		double xDist = p1->getXCord() - p2->getXCord();
		double yDist = p1->getYCord() - p2->getYCord();

		//If between these ranges they have collided
		if ((xDist < 2 && xDist > -2) && (yDist < 2 && yDist > -2)) {
			return true;
		}
		else
			return false;
	}

}

/*int Piece::getScore() {
	return score
}*/