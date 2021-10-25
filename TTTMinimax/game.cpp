#include "game.h"

//Erstelle Board wenn Objekt Spiel erstellt wird -- Konstruktor.
Game::Game(){
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j] = Player::none;
			}
		}
	}

void Game::printBoard(){
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << static_cast<char>(board[i][j]) << "    ";
		}
		std::cout << std::endl;
	}
}

bool Game::isTie() {
	for (unsigned int i = 0; i < 3; i++)
	{
		if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
			return false;
	}
	return true;
}

bool Game::checkWinner(Player player) {

	// diagonal Win
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
		return true;

	if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
		return true;
	
	for (unsigned int i = 0; i < 3; i++)
	{
		// vertical Win
		if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
			return true;

		// horizontal Win
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
			return true;
	}

	return false;
}

void Game::getPlayerMove() {
	bool fail = true;
	int x = -1, y = -1;

	do {
		std::cout << "Type x-Coord : ";
		std::cin >> x;
		std::cout << "Type y-Coord : ";
		std::cin >> y;

		fail = board[x][y] != Player::none;
		if (fail) {
			std::cout << "Only numbers betweeen 0-2 ! or coords already taken !" << std::endl;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (fail);
	board[x][y] = Player::player;
}