#include <iostream>
#include <limits>
#include <algorithm>
#include "minimax.h"

int main() {
	MinimaxAlgo minimaxGame;
	minimaxGame.play();
	std::cout << "NodeCounter : " << minimaxGame.nodeCounter << std::endl;
	std::cin.ignore();
}