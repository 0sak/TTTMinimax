#pragma once
#include"game.h"


struct Move {
	int x = 0;
	int y = 0;
};

class MinimaxAlgo {
public:

	bool alphaBetaPruning = true;
	int nodeCounter = 0;

	Game game;
	
	Move minimax();
	int maxValue(int alpha, int beta);
	int minValue(int alpha, int beta);
	void play();
};