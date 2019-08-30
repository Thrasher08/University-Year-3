#include "Piece.h"
#include "Bishop.h"
#include "Queen.h"
#include "Rook.h"
#include <stdlib.h> 
#include <string>
#include <random>
#include <iostream>

using namespace std;

//Allows a piece type to be printed
string printType(vector <Piece*> pArr, int i) {

	string typePiece;

	if (pArr[i]->getPieceName() == rook) {
		typePiece = "Rook";
	}

	else if (pArr[i]->getPieceName() == bishop) {
		typePiece = "Bishop";
	}
	else
		typePiece = "Queen";

	return typePiece;
}

//Allows a collision type to be printed
string printColl(vector <Piece*> pArr, int i) {
	
	string collType;

	if (pArr[i]->getColl() == circle) {
		collType = "Circle";
	}
	else
		collType = "Square";

	return collType;
}

int main() {
	
	//Score for each type of piece
	int scoreR = 0;
	int scoreB = 0;
	int scoreQ = 0;
	//****************************

	const int boardSize = 256;		//Defines board size
	double numMoves = 100;			//Defines number of moves pieces can make
	int numPieces = 8;				//Defines the number of pieces to generate

	Rook rook;
	Bishop bishop;
	Queen queen;

	vector <Piece*> pArr;

	//Allows doubles to be randomised (later used to randomly move pieces)
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(1, boardSize);
	//********************************************************************

	cout << "Space Chess" << endl;

	//Adds each piece to a vector array
	for (int i = 0; i < numPieces; i++) {
		
		//Add Rooks
		Rook *r = new Rook(dist(e2), dist(e2));
		pArr.push_back(r);

		//Add Bishops
		Bishop *b = new Bishop(dist(e2), dist(e2));
		pArr.push_back(b);

		//Add Queens
		Queen *q = new Queen(dist(e2), dist(e2));
		pArr.push_back(q);

	}

	
	int counter = 0;
	int counter2 = 0;

	//Continue running until number of moves is exceeded
	for (int j = 0; j <= numMoves; j++) {

		std::vector<Piece*>::iterator pIt = pArr.begin();		//Iterates through every piece within the vector from the beginning

		while (pIt != pArr.end()) {

			cout << endl;

			(*pIt)->move(dist(e2), dist(e2));					//Moves piece randomly

			counter = std::distance(pArr.begin(), pIt);			//Enables iterator to be plugged into a print statement e.g. printType(pArr, counter)

			cout << printType(pArr, counter) << " [" << counter << "] Collision Type: " << printColl(pArr, counter) << " Postion: (" << (*pIt)->getXCord() << ", " << (*pIt)->getYCord() << ")" << " Times Moved: " << j << endl;	//Prints piece information

			std::vector<Piece*>::iterator it = pArr.begin();	//Iterates through all previous pieces from the beginning
			counter2 = std::distance(pArr.begin(), it);			//Enables iterator to be plugged into a print statement e.g. printType(pArr, counter2)

			//Continues to run while there are still pieces within the vector
			while (it != pArr.end()) {

				Piece* pieceHolder = *pIt;	//Used to reajust piece iterator

				//If collision occurs between two pieces, erase the stationary piece from vector
				if ((*pIt)->hasCollided(*pIt, *it) && pIt != it) {
					cout << printType(pArr, counter) << " takes " << printType(pArr, counter2) << endl;
					it = pArr.erase(it);

					//Increase Rook Score
					if (printType(pArr, counter) == "rook") {
						scoreR += scoreR;
					}

					//Increase Bishop Score
					if (printType(pArr, counter) == "bishop") {
						scoreB += scoreB;
					}

					//Increase Queen Score
					if (printType(pArr, counter) == "queen") {
						scoreQ += scoreQ;
					}
				}
				else {
					it++;
				}

				//Recycle through pieces and correct itterator
				for (std::vector<Piece*>::iterator revalidator = pArr.begin(); revalidator != pArr.end(); revalidator++){
					if (*revalidator = pieceHolder) {
						pIt = revalidator;
					}
				}
			}
			pIt++;

		}

		//Prints final scores
		cout << "Rook Score: " << scoreR << endl;
		cout << "Bishop Score: " << scoreB << endl;
		cout << "Queen Score: " << scoreQ << endl;

	}
	
	return 0;
}