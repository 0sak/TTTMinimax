#pragma once
#include<iostream>

enum class Player {
	player = 'X',
	ai = 'O',
	none = 'n'
};

class Game {
public:

	Player board[3][3];

	Game();
	void printBoard();
	bool isTie();
	bool checkWinner(Player player);
	void getPlayerMove();

};