#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>

class Game
{
private:
	enum class Player {
		none = '-',
		player = 'X',
		computer = 'O'
	};

	struct Move
	{
		int x = 0;
		int y = 0;

	};

	Player board[3][3];
	int nodeCounter = 0;
	bool alphaBetaPruning = true;

public:
	Game() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j] = Player::none;
			}
		}
	}

	void printBoard(){
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << static_cast<char>(board[i][j]) << "    ";
			}
			std::cout << std::endl;
		}
	}

	//Über das ganze Board gehen und schauen ob es noch '-' gibt.
	bool isTie() {
		for (unsigned int i = 0; i < 3; i++)
		{
			if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
				return false;
		}
		return true;
	}

	bool checkWin(Player player) {
		for (unsigned int i = 0; i < 3; i++)
		{
			// Check horizontals
			if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
				return true;

			// Check verticals
			if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
				return true;
		}

		// Check diagonals
		if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
			return true;

		if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
			return true;

		return false;
	}

	Move minimax() {
		int score = std::numeric_limits<int>::max();
		int alpha = std::numeric_limits<int>::min();
		int beta = std::numeric_limits<int>::max();
		Move move;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == Player::none) {
					nodeCounter++;
					board[i][j] = Player::computer;

					int temp = maxValue(alpha,beta);

					if (temp < score) {
						score = temp;
						move.x = i;
						move.y = j;
					}
					board[i][j] = Player::none;
				}
			}
		}
		return move;
	}

	int maxValue(int alpha, int beta) {
		if (checkWin(Player::player))
			return 1;
		else if (checkWin(Player::computer))
			return -1;
		else if (isTie())
			return 0;

		int score = std::numeric_limits<int>::min();
		if (alphaBetaPruning == true) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board[i][j] == Player::none) {
						nodeCounter++;
						board[i][j] = Player::player;
						score = std::max(score, minValue(alpha, beta));
						board[i][j] = Player::none;
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
					if (board[i][j] == Player::none) {
						nodeCounter++;
						board[i][j] = Player::player;
						score = std::max(score, minValue(alpha, beta));
						board[i][j] = Player::none;
					}
				}
			}
		}
		return score;
	}

	int minValue(int alpha, int beta) {
		if (checkWin(Player::player))
			return 1;
		else if (checkWin(Player::computer))
			return -1;
		else if (isTie())
			return 0;

		int score = std::numeric_limits<int>::max();
		if (alphaBetaPruning == true) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board[i][j] == Player::none) {
						nodeCounter++;
						board[i][j] = Player::computer;
						score = std::min(score, maxValue(alpha, beta));
						board[i][j] = Player::none;
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
					if (board[i][j] == Player::none) {
						nodeCounter++;
						board[i][j] = Player::computer;
						score = std::min(score, maxValue(alpha, beta));
						board[i][j] = Player::none;
					}
				}
			}
		}
		return score;
	}

	void getPlayerMove() {
		bool fail = true;
		int x = -1, y = -1;

		do {
			std::cout << "Type x-Coord : ";
			std::cin >> x;
			std::cout << "Type y-Coord : ";
			std::cin >> y;

			fail = board[x][y] != Player::none;
			if (fail) {
				std::cout << "Only numbers betweeen 0-2 !" << std::endl;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} while (fail);
		board[x][y] = Player::player;
	}

	void play() {
		int turn = 0;
		bool exit = false;

		printBoard();
		std::cout << "x,y\n";

		do {
			if (turn == 0)
			{
				getPlayerMove();
			}
			if (checkWin(Player::player)) {
				std::cout << "X won the game !" << std::endl;
				exit = true;
			}
			else {
				std::cout << "\nComputer Move : ";
				Move aimove = minimax();
				std::cout << "computer-x : " << aimove.x << " --- " << " computer-y : " << aimove.y << std::endl;
				board[aimove.x][aimove.y] = Player::computer;

				if (checkWin(Player::computer)) {
					std::cout << "O won the game !" << std::endl;
					exit = true;
				}
			}
			if (isTie()) {
				std::cout << "Nobody won the Game, Tie!" << std::endl;
				exit = true;
			}
			//turn = 1;
			printBoard();
		} while (!exit);
	}

	int getNodeCounter() {
		return nodeCounter;
	}
};

int main() {
	Game ttt;
	ttt.play();
	std::cout << "NodeCounter : " << ttt.getNodeCounter() << std::endl;
	std::cin.ignore();
}