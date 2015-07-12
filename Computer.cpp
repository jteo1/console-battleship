#include "Computer.h"
#include "Player.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
					   //initialize lives to num of ship markers
Computer::Computer() : lives(5+4+3+3+2), dir(UP), followDir(false), switchedDir(false), switchedAxis(false), loopCounter(0), currentDirLength(0), ship2Status(2), ship31Status(3), ship32Status(3), ship4Status(4), ship5Status(5)
{
	//clear initialized arrays
	for(int i = 0; i < 5; i++)
		shipsSunk[i] = false;

	initialHit[0] = -1;
	initialHit[1] = -1;

}

//converts the random number to a direction
//inputs: number
//outputs: character corresponding to the random direction chosen
//0 -> u, 1 -> d, 2 -> l, 3 -> r
char Computer::intToDir(int num)
{
	switch (num)
	{
	case 0:
		return UP;
	case 1:
		return DOWN;
	case 2:
		return LEFT;
	case 3:
		return RIGHT;
	default:
		return 0;
	}
}

//Uses random numbers to randomly place ships on the board for the cpu.
//inputs: n/a
//outputs: n/a
void Computer::initializeShips()
{
	//seed the random numbers
	srand(time(NULL));
	int row = 0, col = 0;
	char dir;

	//size 5 ship
	do
	{
	row = rand() % 10;
	col = rand() % 10;
	dir = intToDir(rand() % 4);
	} while(b.attemptToPlaceShip(row, col, dir, 5, SHIP5) == 0);

	//size 4 ship
	do
	{
	row = rand() % 10;
	col = rand() % 10;
	dir = intToDir(rand() % 4);
	} while(b.attemptToPlaceShip(row, col, dir, 4, SHIP4) == 0);


	//size 3 ship
	do
	{
	row = rand() % 10;
	col = rand() % 10;
	dir = intToDir(rand() % 4);
	} while(b.attemptToPlaceShip(row, col, dir, 3, SHIP32) == 0);

	//size 3 ship
	do
	{
	row = rand() % 10;
	col = rand() % 10;
	dir = intToDir(rand() % 4);
	} while(b.attemptToPlaceShip(row, col, dir, 3, SHIP31) == 0);

	//size 2 ship
	do
	{
	row = rand() % 10;
	col = rand() % 10;
	dir = intToDir(rand() % 4);
	} while(b.attemptToPlaceShip(row, col, dir, 2, SHIP2) == 0);


}

//print state of board
//inputs/outputs: n/a
void Computer::printBoard()
{
	b.printBoard();
}

//print state of board without revealing ship placement
//inputs/outputs: n/a
void Computer::printHiddenBoard()
{
	b.printHiddenBoard();
}

//check to see if own ship is hit and updates board accordingly
//inputs: row and col that is targeted
//outputs: 1 if hit occurs, 0 if not. -1 signals an out of bounds shot
int Computer::attemptHit(int row, int col)
{
	//out of bounds shot
	if(row < 0 || row > 9 || col < 0 || col > 9)
	{
		return -1;
	}
	//hit empty spot
	if(b.getBoardCoordinate(row, col) == EMPTY)
	{
		b.setBoardCoordinate(row, col, MISS);
		return 0;
	}
	//hit spot that was already hit
	else if(b.getBoardCoordinate(row, col) == HIT || b.getBoardCoordinate(row, col) == MISS)
	{
		return 0;
	}
	//hit spot with a ship
	else if(b.getBoardCoordinate(row, col) == SHIP2)
	{
		b.setBoardCoordinate(row, col, HIT);
		lives--;
		ship2Status--;
		if(ship2Status == 0)
		{
			cout << "2-length ship sunk!" << endl;
		}
		return 1;
	}
	else if(b.getBoardCoordinate(row, col) == SHIP31)
	{
		b.setBoardCoordinate(row, col, HIT);
		lives--;
		ship31Status--;
		if(ship31Status == 0)
		{
			cout << "3-length ship sunk!" << endl;
		}
		return 1;
	}
	else if(b.getBoardCoordinate(row, col) == SHIP32)
	{
		b.setBoardCoordinate(row, col, HIT);
		lives--;
		ship32Status--;
		if(ship32Status == 0)
		{
			cout << "3-length ship sunk!" << endl;
		}
		return 1;
	}
	else if(b.getBoardCoordinate(row, col) == SHIP4)
	{
		b.setBoardCoordinate(row, col, HIT);
		lives--;
		ship4Status--;
		if(ship4Status == 0)
		{
			cout << "4-length ship sunk!" << endl;
		}
		return 1;
	}
	else if(b.getBoardCoordinate(row, col) == SHIP5)
	{
		b.setBoardCoordinate(row, col, HIT);
		lives--;
		ship5Status--;
		if(ship5Status == 0)
		{
			cout << "5-length ship sunk!" << endl;
		}
		return 1;
	}
	//should never get here
	return -1;
}

//returns number of lives for the computer
//input: n/a
//output: number of lives remaining
int Computer::getLives()
{
	return lives;
}


//Guesses a random location to fire and then proceeds to ask player for hit status.
//input: bool determining whether the smartAI will be activated based on player input from beginning of game and player object
//output: 1 if hit occurs, 0 if miss
int Computer::fireAtPlayer(bool smartAI, Player* p)
{
	unsigned int row = 0, col = 0;
	//intelligent AI path
	if(smartAI)
	{
		/*
		cout << "----smartAI attribute states--------" << endl;
		cout << "curentdirlength: " << currentDirLength << endl;
		cout << "initial hit: " << initialHit[0] << "," << initialHit[1] << endl;
		cout << "followDir: " << followDir << endl;
		cout << "switchedDir: " << switchedDir << endl;
		cout << "switchedAxis: " << switchedAxis << endl;
		cout << "dir: " << (char)dir << endl;
		cout << "------------------------------------" << endl;
		*/
		//no leads on any ships yet; choose random coordinate
		if(currentDirLength == 0)
		{
			return makeRandomShot(p);
		}
		//else we have a lead on sinking a ship
		else
		{
			//cout << "Lead on sinking a ship found " << endl;
			int hit = tryDirection(initialHit[0], initialHit[1], dir, currentDirLength, p);

			//still not sure what direction the ship is in, so currentDirLength = 1
			if(followDir == false)
			{
				//cout << "Looking for a direction" << endl;

				//cycle guessed direction while the guess is out of bounds or already shot at
				while(hit == -1)
				{
					loopCounter++;
					if(loopCounter > 5)
					{
						resetSmartVariables();
						return makeRandomShot(p);
					}
					cycleNextDirection();
					hit = tryDirection(initialHit[0], initialHit[1], dir, currentDirLength, p);

				}
				//direction found
				if(hit == SHIP5SUNK || hit == SHIP4SUNK || hit == SHIP3SUNK || hit == SHIP2SUNK)
				{
					resetSmartVariables();

				}
				else if(hit == 1)
				{
					currentDirLength++;
					followDir = true;

				}
				else
				{
					cycleNextDirection();
				}
				return hit;
			}
			//possible direction lead found
			else
			{
				//cout << "Direction found, following  direction: " << (char)dir << endl;
				//out of bounds or already hit, turn around and try other direction
				if(hit == -1)
				{
					currentDirLength = 1;
					//haven't switched direction yet along same axis: make sure we switch only once along the same axis
					if(switchedDir == false)
					{
						//cout << "SWITCHING DIRECTION" << endl;
						setOppositeDirection();
					}
					else if(switchedAxis == false)
					{
						//switch axis
						//cout << "SWITCHING AXIS" << endl;
						switchedAxis = true;
						cycleNextDirection();

					}
					do
					{
						loopCounter++;
						//if loop occurs, just go back to guessing randomly
						if(loopCounter > 5)
						{
							//cout << "LOOP DETECTED, proceed to random shot" << endl;
							resetSmartVariables();
							return makeRandomShot(p);
						}
						hit = tryDirection(initialHit[0], initialHit[1], dir, currentDirLength, p);
						//only way that hit is still -1 is if the cycled direction was out of bounds or already hit, so switch to opposite direction
						if (hit == -1)
						{
							//cout << "re-evaluating direction" << endl;
							//just switched direction and got blocked
							if(switchedDir == true && switchedAxis == false)
							{
								switchedDir = false;
								switchedAxis = true;
								cycleNextDirection();
							}
							else
							{
							setOppositeDirection();
							}
							//cout << "Right before attempting hit, dir is: " << (char)dir << endl;
							hit = tryDirection(initialHit[0], initialHit[1], dir, currentDirLength, p);
						}
					}while(hit == -1);


				}
				//else
				//{
				if(hit == SHIP5SUNK || hit == SHIP4SUNK || hit == SHIP3SUNK || hit == SHIP2SUNK)
				{
					//cout << "DEBUG: SHIP SANK, back to random" << endl;
					resetSmartVariables();

				}
				else if(hit == 1)
				{
					currentDirLength++;
				}
				return hit;
				//}
			}
		}

	}
	//simple AI path
	else
	{
		//choose a random coordinate
		row = rand() % 10;
		col = rand() % 10;
		cout << "Computer fires at: " << (char)('A' + row) << col << endl;
		return p->attemptHit(row, col);
	}

	//should never get here
	return -1;
}

//--------------------------------------------------------------------
//smartAI helper functions

//try to fire in a given direction to check if out of bounds
//inputs: row, col, direction to check in, and pointer to player to attemptHit
//output: -1 if out of bounds, 0 if miss, 1 if hit
int Computer::tryDirection(unsigned int row, unsigned int col, direction dir, unsigned int distance, Player* p)
{
	int result;
	if(dir == UP)
		row -= distance;
	else if(dir == RIGHT)
		col += distance;
	else if(dir == DOWN)
		row += distance;
	else if (dir == LEFT)
		col -= distance;

	//out of bounds
	if(row < 0 || row > 9 || col < 0 || col > 9)
	{
		//cout << "DEBUG: guessed coordinate: "  << row << "," << col << " out of bounds" << endl;
		return -1;
	}
	//already fired at this spot
	if(memBoard.getBoardCoordinate(row, col) == HIT || memBoard.getBoardCoordinate(row, col) == MISS)
	{
		//cout << "DEBUG: guessed direction: " << row << "," << col << " already hit " << (char)memBoard.getBoardCoordinate(row, col) << endl;
		return -1;
	}

	cout << "Computer fires at: " << (char)('A' + row) << col << endl;
	result = p->attemptHit(row, col);

	//some sort of hit occured
	if(result > 0)
	{
		//cout << "Set " << row << "," << col << " to hit" << endl;
		memBoard.setBoardCoordinate(row, col, HIT);
	}
	else if(result == 0)
	{
		//cout << "Set " << row << "," << col << " to miss" << endl;
		memBoard.setBoardCoordinate(row, col, MISS);
	}
	return result;
}

//Cycles direction to guess in a clockwise pattern
//input/output: n/a
void Computer::cycleNextDirection()
{
	if(dir == UP)
		dir = RIGHT;

	else if(dir == RIGHT)
		dir = DOWN;

	else if(dir == DOWN)
		dir = LEFT;

	else if(dir == LEFT)
		dir = UP;

}

//resets all variables after finishing off a whole ship
//inputs/outputs: n/a
void Computer::resetSmartVariables()
{
	initialHit[0] = -1;
	initialHit[1] = -1;
	followDir = false;
	switchedDir = false;
	switchedAxis = false;
	currentDirLength = 0;
	loopCounter = 0;
	dir = UP;
}

//sets dir to opposite direction of the current direction
void Computer::setOppositeDirection()
{
	if(dir == UP)
		dir = DOWN;

	else if(dir == RIGHT)
		dir = LEFT;

	else if(dir == DOWN)
		dir = UP;

	else if (dir == LEFT)
		dir = RIGHT;

	switchedDir = true;
}

//Make a random shot at the player
//input: player to fire at
//output: 0 for miss, 1 for hit
int Computer::makeRandomShot(Player* p)
{
	unsigned int row, col;
	//cout << "Random shot mode" << endl;
	//generate new random coordinates so that we don't repeat a spot
	do
	{
	row = rand() % 10;
	col = rand() % 10;
	}while(memBoard.getBoardCoordinate(row, col) == HIT || memBoard.getBoardCoordinate(row, col) == MISS);

	cout << "Computer fires at: " << (char)('A' + row) << col << endl;
	int hit = p->attemptHit(row, col);
	if(hit > 0)
	{
		//found a coordinate; ship found
		currentDirLength = 1;
		initialHit[0] = row;
		initialHit[1] = col;
		//cout << "Set " << row << "," << col << " to hit" << endl;
		memBoard.setBoardCoordinate(row, col, HIT);
	}
	else
	{
		//cout << "Set " << row << "," << col << " to miss" << endl;
		memBoard.setBoardCoordinate(row, col, MISS);

	}
	return hit;
}
