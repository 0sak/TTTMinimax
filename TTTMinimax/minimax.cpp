#include"minimax.h"

aiNextMove MinimaxAlgo::minimax() {
	int score = std::numeric_limits<int>::max();
	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	aiNextMove move;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game.board[i][j] == game.none) {
				nodeCounter++;
				game.board[i][j] = game.ai;

				int temp = maxValue(alpha, beta);

				if (temp < score) {
					score = temp;
					move.x = i;
					move.y = j;
				}
				game.board[i][j] = game.none;
			}
		}
	}
	return move;
}

int MinimaxAlgo::maxValue(int alpha, int beta) {
	if (game.checkWinner(game.player))
		return 1;
	else if (game.checkWinner(game.ai))
		return -1;
	else if (game.isTie())
		return 0;

	int score = std::numeric_limits<int>::min();
	if (alphaBetaPruning == true) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game.board[i][j] == game.none) {
					nodeCounter++;
					game.board[i][j] = game.player;
					score = std::max(score, minValue(alpha, beta));
					game.board[i][j] = game.none;
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
				if (game.board[i][j] == game.none) {
					nodeCounter++;
					game.board[i][j] = game.player;
					score = std::max(score, minValue(alpha, beta));
					game.board[i][j] = game.none;
				}
			}
		}
	}
	return score;
}

int MinimaxAlgo::minValue(int alpha, int beta) {
	if (game.checkWinner(game.player))
		return 1;
	else if (game.checkWinner(game.ai))
		return -1;
	else if (game.isTie())
		return 0;

	int score = std::numeric_limits<int>::max();
	if (alphaBetaPruning == true) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game.board[i][j] == game.none) {
					nodeCounter++;
					game.board[i][j] = game.ai;
					score = std::min(score, maxValue(alpha, beta));
					game.board[i][j] = game.none;
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
				if (game.board[i][j] == game.none) {
					nodeCounter++;
					game.board[i][j] = game.ai;
					score = std::min(score, maxValue(alpha, beta));
					game.board[i][j] = game.none;
				}
			}
		}
	}
	return score;
}

void MinimaxAlgo::play() {
	game.printBoard();
	bool winLoseTie = false;

	//Game Loop
	do {
		game.getPlayerMove();
		if (game.checkWinner(game.player)) {
			std::cout << "X won the game !" << std::endl;
			winLoseTie = true;
		}
		else {
			std::cout << "\nAI XY : ";
			aiNextMove aiXY = minimax();
			std::cout << "computer-x : " << aiXY.x << " --- " << " computer-y : " << aiXY.y << std::endl;
			game.board[aiXY.x][aiXY.y] = game.ai;

			if (game.checkWinner(game.ai)) {
				std::cout << "O won the game !" << std::endl;
				winLoseTie = true;
			}
		}
		if (game.isTie()) {
			std::cout << "Nobody won the Game, Tie!" << std::endl;
			winLoseTie = true;
		}
		game.printBoard();
	} while(!winLoseTie);
}