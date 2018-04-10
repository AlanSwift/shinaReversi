#pragma once
#ifndef SHINA_BOARD_H
#define SHINA_BOARD_H
#include "bitboard.h"

class ChessBoard {
public:
	ChessBoard(LL black=-1, LL white=-1)
	{
		if (black < 0 || white < 0)
		{
			this->black = (((LL)0b00010000) << 24 | ((LL)0b00001000) << 32);
			this->white = (((LL)0b00001000) << 24 | ((LL)0b00010000) << 32);
		}
		else {
			this->black = black;
			this->white = white;
		}
	}
	Board black;
	Board white;
};

#endif