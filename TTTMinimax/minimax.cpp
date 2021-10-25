#include"minimax.h"

Move MinimaxAlgo::minimax() {
	int score = std::numeric_limits<int>::max();
	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	Move move;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game.board[i][j] == Player::none) {
				nodeCounter++;
				game.board[i][j] = Player::ai;

				int temp = maxValue(alpha, beta);

				if (temp < score) {
					score = temp;
					move.x = i;
					move.y = j;
				}
				game.board[i][j] = Player::none;
			}
		}
	}
	return move;
}

int MinimaxAlgo::maxValue(int alpha, int beta) {
	if (game.checkWinner(Player::player))
		return 1;
	else if (game.checkWinner(Player::ai))
		return -1;
	else if (game.isTie())
		return 0;

	int score = std::numeric_limits<int>::min();
	if (alphaBetaPruning == true) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game.board[i][j] == Player::none) {
					nodeCounter++;
					game.board[i][j] = Player::player;
					score = std::max(score, minValue(alpha, beta));
					game.board[i][j] = Player::none;
					if (score >= beta)
						return score;

					alpha = std::max(alpha, score);
				}
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game.board[i][j] == Player::none) {
					nodeCounter++;
					game.board[i][j] = Player::player;
					score = std::max(score, minValue(alpha, beta));
					game.board[i][j] = Player::none;
				}
			}
		}
	}
	return score;
}

int MinimaxAlgo::minValue(int alpha, int beta) {
	if (game.checkWinner(Player::player))
		return 1;
	else if (game.checkWinner(Player::ai))
		return -1;
	else if (game.isTie())
		return 0;

	int score = std::numeric_limits<int>::max();
	if (alphaBetaPruning == true) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game.board[i][j] == Player::none) {
					nodeCounter++;
					game.board[i][j] = Player::ai;
					score = std::min(score, maxValue(alpha, beta));
					game.board[i][j] = Player::none;
					if (score <= alpha)
						return score;

					beta = std::min(beta, score);
				}
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game.board[i][j] == Player::none) {
					nodeCounter++;
					game.board[i][j] = Player::ai;
					score = std::min(score, maxValue(alpha, beta));
					game.board[i][j] = Player::none;
				}
			}
		}
	}
	return score;
}

void MinimaxAlgo::play() {
	int turn = 0;
	bool exit = false;

	game.printBoard();
	std::cout << "x,y\n";

	do {
		if (turn == 0)
		{
			game.getPlayerMove();
		}
		if (game.checkWinner(Player::player)) {
			std::cout << "X won the game !" << std::endl;
			exit = true;
		}
		else {
			std::cout << "\nAI XY : ";
			Move aiXY = minimax();
			std::cout << "computer-x : " << aiXY.x << " --- " << " computer-y : " << aiXY.y << std::endl;
			game.board[aiXY.x][aiXY.y] = Player::ai;

			if (game.checkWinner(Player::ai)) {
				std::cout << "O won the game !" << std::endl;
				exit = true;
			}
		}
		if (game.isTie()) {
			std::cout << "Nobody won the Game, Tie!" << std::endl;
			exit = true;
		}
		//turn = 1;
		game.printBoard();
	} while (!exit);
}