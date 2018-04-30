//#pragma once
//#ifndef SHINA_REVERSIENV_H
//#define SHINA_REVERSIENV_H
//#include "board.h"
///*
//	nextPlayer is the player who will move next time, assume now is thinking.
//*/
//class reversiEnv
//{
//public:
//	reversiEnv() :nextPlayer(black),basicEval(0)
//	{
//		//black
//		//  0 1 
//		//  1 0
//		// black first
//		myBoard = new ChessBoard(false);
//	}
//	reversiEnv(const reversiEnv& e):nextPlayer(e.nextPlayer),basicEval(e.basicEval)
//	{
//		myBoard = new ChessBoard(true, e.myBoard->black, e.myBoard->white);
//	}
//	bool step(Position action);
//	inline Board getPossibleMoves()
//	{
//		PLL state = getOwnAndEnemy();
//		return findCorrectMoves(state.first, state.second);
//	}
//	inline void ChangePlayer()
//	{
//		nextPlayer ^= 1ull;
//		basicEval = -basicEval;
//	}
//	inline int calcFinal()
//	{
//		/**
//		 *  Description:
//		 *  
//		 *  @return : return winner
//		 */
//		int cntBlack = countBit(myBoard->black);
//		int cntWhite = countBit(myBoard->white);
//		
//		return cntBlack > cntWhite ? black : (cntBlack < cntWhite ? white : draw);
//	}
//	inline bool check(Player e)
//	{
//		return e == black ? (findCorrectMoves(myBoard->black,myBoard->white) != 0) : (findCorrectMoves(myBoard->white,myBoard->black) != 0);
//	}
//	inline bool isOver()
//	{
//		return (findCorrectMoves(myBoard->black, myBoard->white) == 0) && (findCorrectMoves(myBoard->white, myBoard->black) == 0);
//	}
//	inline bool willOver()
//	{
//		return (countBit(myBoard->black) + countBit(myBoard->white)) == 63;
//	}
//	inline void reset(Board blackChess = -1, Board whiteChess = -1)
//	{
//		delete myBoard;
//		myBoard = new ChessBoard(true, blackChess, whiteChess);
//		nextPlayer = black;
//	}
//	inline void render()
//	{
//		showBoard(myBoard->black, myBoard->white);
//	}
//	inline int getPlayer()
//	{
//		return nextPlayer;
//	}
//	inline double evalGameOver() const
//	{
//		/**
//		 *  Description: evaluate function 1 which to evaluate the final state
//		 *  @return: the evaluate value of the result
//		 */
//		PLL state = getOwnAndEnemy();
//		//swap(state.first, state.second);
//		int off = countBit(state.first) - countBit(state.second);
//		return off > 0 ? (1e8 + off) : (off < 0 ? -1e8 + off : 0);
//	}
//	int evalState();
//	inline LL getHashcode()
//	{
//		hashcode = 0;
//		for (int i = 0; i < 64; i++)
//		{
//			if (myBoard->black & (1ull << i))
//			{
//				hashcode ^= PIECE_HASH_VALUE[i][black];
//			}
//			if (myBoard->white & (1ull << i))
//			{
//				hashcode ^= PIECE_HASH_VALUE[i][white];
//			}
//
//		}
//		return hashcode;
//	}
//
//	~reversiEnv()
//	{
//		delete myBoard;
//	}
//	inline void copyFrom(reversiEnv*env)
//	{
//		nextPlayer = env->nextPlayer;
//		basicEval = env->basicEval;
//		myBoard->black = env->myBoard->black;
//		myBoard->white = env->myBoard->white;
//
//	}
//	
//private:
//	int nextPlayer;
//	ChessBoard* myBoard;
//	int basicEval;
//	LL hashcode;
//	inline int toPos(int x, int y) const
//	{
//		return x * 8 + y;
//	}
//	inline bool isEmpty(int pos) const
//	{
//		return !((myBoard->black | myBoard->white)&(1ull << pos));
//	}
//	inline bool BoardNotEmpty(Board x, int pos) const
//	{
//		return ((x>>pos)&1);
//	}
//	inline PLL& getOwnAndEnemy()const
//	{
//		return this->nextPlayer == black ? make_pair(this->myBoard->black, this->myBoard->white) :
//			make_pair(this->myBoard->white,this->myBoard->black);
//	}
//	inline void setOwnAndEnemy(PLL &state)
//	{
//		if (nextPlayer == black)
//		{
//			myBoard->black = state.first;
//			myBoard->white = state.second;
//		}
//		else {
//			myBoard->black = state.second;
//			myBoard->white = state.first;
//		}
//	}
//};
//
//
//#endif // !SHINA_REVERSIENV_H
