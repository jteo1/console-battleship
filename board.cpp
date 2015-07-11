#include "board.h"
#include <iostream>
using namespace std;
Board::Board()
{
	//initalize entire board to empty '.' character
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			board[i][j] = EMPTY;
		}
	}

}

//checks for a ship intersection before attempting to place a ship
//inputs: row and col and direction of requested ship placement, along with size of the ship
//outputs: 1 if ship is successfully placed, 0 if not
int Board::attemptToPlaceShip(int row, int col, char dir, int size, marker shipNum)
{
	int i = 0;
	if(dir == LEFT && col - size + 1 >= 0) //check if dir is left
	{
		for(int i = 0; i < size; i++)
		{
			if(board[row][col - i] != '.')
			{
				return 0;
			}
		}	

		for(int i = 0; i < size; i++)
		{
			board[row][col - i] = shipNum;
		}
	}
	else if(dir == RIGHT && col + size - 1 <= 9) //check if dir is right
	{
		for(int i = 0; i < size; i++)
		{
			if(board[row][col + i] != EMPTY)
			{
				return 0;
			}
		}
		for(int i = 0; i < size; i++)
		{
			board[row][col + i] = shipNum;
		}
	}
	else if (dir == UP && row - size + 1 >= 0) //check if dir is up
	{
		for(int i = 0; i < size; i++)
		{
			if(board[row - i][col] != '.')
			{
				return 0;
			}
		}

		for(int i = 0; i < size; i++)
		{
			board[row - i][col] = shipNum;
		}
	}
	else if (dir == DOWN && row + size - 1 <= 9) //check if dir is down
	{
		for(int i = 0; i < size; i++)
		{
			if(board[row + i][col] != EMPTY)
			{
				return 0;
			}
		}

		for(int i = 0; i < size; i++)
		{
			board[row + i][col] = shipNum;
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

//print state of full board
//inputs: n/a
//outputs: full view of board
void Board::printBoard()
{
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;

	for(int i = 0; i < 10; i++)
	{
		cout << (char)(i+65) << " ";
		for(int j = 0; j < 10; j++)
		{
			cout << (char)board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//prints out state of board while masking ship placements
//inputs: n/a
//output: hidden board
void Board::printHiddenBoard()
{
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;

	for(int i = 0; i < 10; i++)
	{
		cout << (char)(i+65) << " ";
		for(int j = 0; j < 10; j++)
		{
			//don't reveal ship locations
			if(board[i][j] == SHIP32 || board[i][j] == SHIP2 || board[i][j] == SHIP31 ||board[i][j] == SHIP4 || board[i][j] == SHIP5)
				cout << (char)EMPTY << " ";
			else
				cout << (char)board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//gets the value of a coordinate. Checks are done before this function is called to ensure out of bounds doesn't occur.
//input: row and col of requested coordinate
//output: the value of the coordinate
char Board::getBoardCoordinate(int row, int col)
{
	if(row < 0 || row > 9 || col < 0 || col > 9)
	{
		return NULL;
	}
	return board[row][col];
}

//sets the value of a coordinate. Checks are done before this function is called to ensure out of bounds doesn't occur.
//input: row/col of the coordinate, and the value to replace
//output: 1 if successful, -1 if not
int Board::setBoardCoordinate(int row, int col, marker in)
{
	if(row < 0 || row > 9 || col < 0 || col > 9)
	{
		return -1;
	}
	board[row][col] = in;
	return 1;
}
