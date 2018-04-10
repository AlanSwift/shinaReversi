#pragma once
#ifndef SHINA_REVERSIENV_H
#define SHINA_REVERSIENV_H
#include "board.h"
/*
	nextPlayer is the player who will move next time, assume now is thinking.
*/
class reversiEnv
{
public:
	reversiEnv() :nextPlayer(black)
	{
		myBoard = new ChessBoard(false);
	}
	reversiEnv(const reversiEnv& e):nextPlayer(e.nextPlayer)
	{
		myBoard = new ChessBoard(true, e.myBoard->black, e.myBoard->white);
	}
	bool step(Position action);
	inline Board getPossibleMoves()
	{
		PLL state = getOwnAndEnemy();
		return findCorrectMoves(state.first, state.second);
	}
	inline void ChangePlayer()
	{
		nextPlayer ^= 1ull;
	}
	inline int calcFinal()
	{
		/**
		 *  Description:
		 *  
		 *  @return : return winner
		 */
		int cntBlack = countBit(myBoard->black);
		int cntWhite = countBit(myBoard->white);
		
		return cntBlack > cntWhite ? black : (cntBlack < cntWhite ? white : draw);
	}
	inline bool check(Player e)
	{
		return e == black ? (findCorrectMoves(myBoard->black,myBoard->white) != 0) : (findCorrectMoves(myBoard->white,myBoard->black) != 0);
	}
	inline bool isOver()
	{
		return (findCorrectMoves(myBoard->black, myBoard->white) == 0) && (findCorrectMoves(myBoard->white, myBoard->black) == 0);
	}
	inline void reset(Board blackChess = -1, Board whiteChess = -1)
	{
		delete myBoard;
		myBoard = new ChessBoard(blackChess, whiteChess);
		nextPlayer = black;
	}
	inline void render()
	{
		showBoard(myBoard->black, myBoard->white);
	}
	inline int getPlayer()
	{
		return nextPlayer;
	}
	~reversiEnv();
	
private:
	int nextPlayer;
	ChessBoard* myBoard;
	inline PLL& getOwnAndEnemy()
	{
		return this->nextPlayer == black ? make_pair(this->myBoard->black, this->myBoard->white) :
			make_pair(this->myBoard->white,this->myBoard->black);
	}
	inline void setOwnAndEnemy(PLL &state)
	{
		if (nextPlayer == black)
		{
			myBoard->black = state.first;
			myBoard->white = state.second;
		}
		else {
			myBoard->black = state.second;
			myBoard->white = state.first;
		}
	}
};


#endif // !SHINA_REVERSIENV_H
