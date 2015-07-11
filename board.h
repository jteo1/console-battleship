#ifndef _BOARD_
#define _BOARD_
using namespace std;
				

#define SHIP2SUNK 2
#define SHIP3SUNK 3
#define SHIP4SUNK 4
#define SHIP5SUNK 5


						//2length ship, 3length ship #1, 3length ship #2, 4length ship, 5 length ship
enum marker : char {EMPTY = '.', SHIP2 = '1', SHIP31 = '2', SHIP32 = '3', SHIP4 = '4', SHIP5 = '5', HIT = 'x', MISS = '-'};
enum direction : char {UP = 'u', DOWN = 'd', LEFT = 'l', RIGHT = 'r', NONE = '0'}; 

class Board
{
private:
	marker board[10][10];

public:
	Board();
	void printBoard();
	void printHiddenBoard();
	char getBoardCoordinate(int row, int col);
	int setBoardCoordinate(int row, int col, marker in);
	int attemptToPlaceShip(int row, int col, char dir, int size, marker shipNum);


};

#endif