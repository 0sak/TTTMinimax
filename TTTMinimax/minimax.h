#pragma once
#include"game.h"


struct aiNextMove {
	int x = 0;
	int y = 0;
};

class MinimaxAlgo {
public:

	bool alphaBetaPruning = true;
	int nodeCounter = 0;

	Game game;
	
	void play();
	int maxValue(int alpha, int beta);
	aiNextMove minimax();
	int minValue(int alpha, int beta);
};