#pragma once
#ifndef SHINA_REVERSIENV_H
#define SHINA_REVERSIENV_H
#include "board.h"

class reversiEnv
{
public:
	reversiEnv() :nextPlayer(black)
	{
		myBoard = new ChessBoard();
	}
private:
	int nextPlayer;
	ChessBoard* myBoard;

};


#endif // !SHINA_REVERSIENV_H
