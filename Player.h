#ifndef _PLAYER_
#define _PLAYER_

#include "board.h"
#include <string>

using namespace std;
class Player
{
private:
	Board b;
	int lives;

	//ship statuses
	int ship5Status;
	int ship4Status;
	int ship32Status;
	int ship31Status;
	int ship2Status;


public:
	Player();
	int placeShip(string input, int size, marker shipNum);
	void printBoard();
	int attemptHit(int row, int  col);
	int getLives();
};

#endif

