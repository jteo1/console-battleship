#ifndef _COMPUTER_
#define _COMPUTER_

#include "board.h"

class Player; 

using namespace std;
class Computer
{
private:
	char intToDir(int num);
	Board b;
	Board memBoard; //keep track of view of player's board
	int lives;

	//ship statuses
	int ship5Status;
	int ship4Status;
	int ship32Status;
	int ship31Status;
	int ship2Status;

	//smartAI variables
	direction dir;
	bool followDir; //found a 1D plane to investigate
	bool switchedDir; //indicate whether we have already tried to switch direction once
	bool switchedAxis; //indicate when we're currently on new axis
	unsigned int currentDirLength; //streak of hits in a given direction from initial hit
	unsigned int initialHit[2]; //stores where the initial hit occured
	unsigned int loopCounter; //prevent infinite loops from happening
	bool shipsSunk[5]; //stores which ships have already sunk: {2-ship, 3-ship, 3-ship, 4-ship, 5-ship}

	//smartAI functions
	int tryDirection(unsigned int row, unsigned int col, direction dir, unsigned int distance, Player* p);
	void cycleNextDirection();
	void resetSmartVariables();
	void setOppositeDirection();
	int makeRandomShot(Player* p);

public:
	Computer();
	void initializeShips();
	void printBoard();
	void printHiddenBoard();
	int attemptHit(int row, int  col);
	int getLives();
	int fireAtPlayer(bool smartAI, Player* p);
};

#endif