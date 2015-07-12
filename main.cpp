#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "Player.h"
#include "Computer.h"

using namespace std;

void getShipInputs(Player* pb);

int main()
{
	srand((unsigned int)time(NULL));
	Player player;
	Computer computer;
	bool smartAI = false;
	bool showComputerBoard = false;
	string playerInput;
	//instructions
	cout << "BattleShip game: Player vs. CPU" << endl;
	cout << "Rules:\nGame is played on a 10x10 board. The player and CPU get a 5 length ship, a 4 length ship, two 3 length ships, and a 2 length ship. " << endl;
	cout << "\nPlease choose a CPU difficulty level. An input of '0' corresponds to a basic CPU that randomly chooses coordinates. An input of '1' corresponds to a more advanced CPU that simulates human behavior." << endl;
	//choose difficulty
	while(1)
	{
		cin >> playerInput;
		if((playerInput[0] != '0' && playerInput[0] != '1') || playerInput.size() > 2)
		{
			cout << "Invalid difficulty level entered. Please enter in either a '0' or '1'" << endl;
			continue;
		}
		if(playerInput[0] == '1')
		{
			smartAI = true;
		}
		else if(playerInput[0] == '0')
		{
			smartAI = false;
		}
		//Display computer's board during the game
		if(playerInput.size() == 2 && playerInput[1] == 'a')
		{
			showComputerBoard = true;
		}


		break;
	}

	cout << "\nTo place a ship, simply enter the coordinate and the direction, where direction is denoted by a singluar character l, u, r, or d. For example, placing a ship at A4 facing rightwards would be denoted by A4r. Please use this exact format with a total of 3 characters.\n" << endl;
	cout << "Player Board: " << endl;
	player.printBoard();

	//set up game boards for player and CPU
	computer.initializeShips();
	cout << "\nComputer Board: " << endl;
	if(showComputerBoard)
	{
		computer.printBoard();
	}
	else
	{
		computer.printHiddenBoard();
	}
	//Selecting player ship placement
	getShipInputs(&player);

	//GAME BEGINS
	int round = 1;
	while(1)
	{
		cout << "\nRound " << round << endl;
		int r = 0, c = 0;
		string playerInput;

		//player fires
		cout << "Choose a coordinate to fire" << endl;
		cin >> playerInput;
		if(playerInput.size() != 2)
		{
			cout << "Invalid number of characters, try again with only 2 characters" << endl;
			continue;
		}
		r = playerInput[0] - 'A';
		c = playerInput[1] - '0';

		cout << "Player fires at: " << playerInput[0] << playerInput[1] << endl;

		//ask cpu if target is a hit, updates board
		int playerShot = computer.attemptHit(r, c);
		if(playerShot == -1)
		{
			cout << "Invalid coordinates, try again" << endl;
			continue;
		}
		else if(playerShot == 0)
		{
			cout << "Player shot missed\n" << endl;

		}
		else if(playerShot == 1)
		{
			cout << "Player shot hits!\n" << endl;
			if(computer.getLives() == 0)
			{
				cout << "Player wins!" << endl;
				cout << "Player Board: " << endl;
				player.printBoard();
				cout << "Computer Board: " << endl;
				computer.printHiddenBoard();
				break;
			}
		}

		//computer fires
		int computerShot;
		computerShot = computer.fireAtPlayer(smartAI, &player); //delegate work of choosing coordinates and firing to computer class
		if(computerShot == 0)
		{
			cout << "Computer shot missed\n" << endl;

		}
		else if(computerShot > 0)
		{
			cout << "Computer shot hits!\n" << endl;
			if(player.getLives() == 0)
			{
				cout << "Computer wins!" << endl;
				cout << "Player Board: " << endl;
				player.printBoard();
				cout << "Computer Board was: " << endl;
				computer.printBoard();
				break;
			}
		}


		//print out board states
		cout << "Player Board: " << endl;
		player.printBoard();

		cout << "Computer Board: " << endl;
		if(showComputerBoard)
		{
			computer.printBoard();
		}
		else
		{
			computer.printHiddenBoard();
		}
		round++;
	}




}

//initializes the player's board by getting inputs
//input: pointer to a Player class
//outut: n/a
void getShipInputs(Player* pb)
{
	string playerInput = "";
	cout << "Place 5 length ship: " << endl;
	cin >> playerInput;
	while(pb->placeShip(playerInput, 5, SHIP5) == 0)
	{
		cout << "Error placing ship, please revise ship placement" << endl;
		cin >> playerInput;

	}

	cout << "Place 4 length ship: " << endl;
	cin >> playerInput;
	while(pb->placeShip(playerInput, 4, SHIP4) == 0)
	{
		cout << "Error placing ship, please revise ship placement" << endl;
		cin >> playerInput;
	}

	cout << "Place 3 length ship: " << endl;
	cin >> playerInput;
	while(pb->placeShip(playerInput, 3, SHIP32) == 0)
	{
		cout << "Error placing ship, please revise ship placement" << endl;
		cin >> playerInput;
	}

	cout << "Place 3 length ship: " << endl;
	cin >> playerInput;
	while(pb->placeShip(playerInput, 3, SHIP31) == 0)
	{
		cout << "Error placing ship, please revise ship placement" << endl;
		cin >> playerInput;
	}

	cout << "Place 2 length ship: " << endl;
	cin >> playerInput;
	while(pb->placeShip(playerInput, 2, SHIP2) == 0)
	{
		cout << "Error placing ship, please revise ship placement" << endl;
		cin >> playerInput;
	}
}
