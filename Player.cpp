#include "Player.h"
#include <iostream>

Player::Player() : lives(5+4+3+3+2), ship2Status(2), ship31Status(3), ship32Status(3), ship4Status(4), ship5Status(5) //initialize lives to num of ship markers,
{

}


//places a ship on the player's board
//inputs: input string from player, and the size of the ship that is to be placed
//outputs: 1 if successful, 0 if invalid (goes off board, intersects another ship)
int Player::placeShip(string input, int size, marker shipNum)
{
	//int row = convertLetterToIndex(input[0]); 
	int row = input[0] - 'A'; 
	int col = input[1] - '0'; //convert to int
	char dir = input[2];
	//cout << "DEBUG: row = " << row << ", col = " << col << ", dir = " << dir << endl;
	//check for invalid inputs
	if(input.length() != 3 || (row > 9 || row < 0) || (col > 9 || col < 0) || !(dir == LEFT || dir == RIGHT || dir == UP || dir == DOWN))
	{
		cout << "An invalid character was entered" << endl;
		return 0;
	}

	//check for bound errors or crossing ships. Place the ship as long as no illegal placements occur
	int place = b.attemptToPlaceShip(row, col, dir, size, shipNum);

	if(place == 1)
	{
		cout << "Ship added" << endl;
		b.printBoard();
		return 1;
	}
	else{
		cout << "Ship out of bounds or intersection error" << endl;
		return 0;
	}
	
	
}


//print state of board
//inputs/outputs: n/a
void Player::printBoard()
{
	b.printBoard();
}

//returns number of lives for the player
//input: n/a
//output: number of lives remaining
int Player::getLives()
{
	return lives;
}


//check own board to see if ship is hit and updates board accordingly
//inputs: row and col that is targeted
//outputs: 1 if hit occurs, 0 if not. -1 signals an out of bounds shot
//Additionally for the smartAI, it returns a global constant 2, 3, 4, or 5 indicating if a particular ship was sunk
int Player::attemptHit(int row, int col)
{
	//out of bounds shot
	if(row < 0 || row > 9 || col < 0 || col > 9)
	{
		//cout << "Player::atemptHit: Out of bounds " << endl;
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
		ship2Status--;
		if(ship2Status == 0)
		{
			cout << "2-length ship sunk!" << endl;
			lives -= 2;
			return SHIP2SUNK;
		}
		return 1;
	}
	else if(b.getBoardCoordinate(row, col) == SHIP31)
	{
		b.setBoardCoordinate(row, col, HIT);
		ship31Status--;
		if(ship31Status == 0)
		{
			cout << "3-length ship sunk!" << endl;
			lives -= 3;
			return SHIP3SUNK;
		}
		return 1;
	}
	else if(b.getBoardCoordinate(row, col) == SHIP32)
	{
		b.setBoardCoordinate(row, col, HIT);
		ship32Status--;
		if(ship32Status == 0)
		{
			cout << "3-length ship sunk!" << endl;
			lives -= 3;
			return SHIP3SUNK;
		}
		return 1;
	}
	else if(b.getBoardCoordinate(row, col) == SHIP4)
	{
		b.setBoardCoordinate(row, col, HIT);
		ship4Status--;
		if(ship4Status == 0)
		{
			lives -= 4;
			cout << "4-length ship sunk!" << endl;
			return SHIP4SUNK;
		}
		return 1;
	}
	else if(b.getBoardCoordinate(row, col) == SHIP5)
	{
		b.setBoardCoordinate(row, col, HIT);
		ship5Status--;
		if(ship5Status == 0)
		{
			cout << "5-length ship sunk!" << endl;
			lives -= 5;
			return SHIP5SUNK;
		}
		return 1;
	}


	//should never get here
	return -1;
}