#pragma once
#include<iostream>


class Game {
public:
	char player = 'X', ai = 'O', none = 'n';
	char board[3][3];

	Game();

	bool checkWinner(char player);
	void printBoard();
	void getPlayerMove();
	bool isTie();

};