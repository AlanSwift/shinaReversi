#ifndef SHINA_REVERSIENV_H
#define SHINA_REVERSIENV_H

#include "config.h"
#include "bitboard.h"


inline int toSquare(int x, int y)
{
	return x * BOARD_WIDTH + y;
}

inline int getSquareX(int sq)
{
	return sq / BOARD_WIDTH;
}

inline int getSquareY(int sq)
{
	return sq % BOARD_WIDTH;
}

class reversiEnv {
public:
	reversiEnv();
	reversiEnv(const reversiEnv &e)
	{
		this->nullMoveCount = e.nullMoveCount;
		/*
		u64 board[2];
	int player;
	int nullMoveCount;
	int basicEval;
	HashValue hashValue;
		*/
		this->board[0] = e.board[0];
		this->board[1] = e.board[1];
		this->player = e.player;
		this->basicEval = e.basicEval;
		this->hashValue = e.hashValue;
		this->preSet = false;
	}
	bool isValidMove(int x, int y);
	bool isBlackPlayer() const;
	bool isWhitePlayer() const;
	bool isEmpty(int sq) const;
	bool isMyPiece(int sq) const;
	bool isOppPiece(int sq) const;
	bool isBlackPiece(int sq) const;
	bool isWhitePiece(int sq) const;
	int countAllPieces() const;
	int countBlackPieces() const;
	int countWhitePieces() const;
	int countMyPieces() const;
	int countOppPieces() const;
	bool isGameEnd() const;
	int generateMoves(int moves[]) const;
	int generateMovesWithPreMove(int moves[],LL mov)const;
	LL generateMovesLL();

	Value getEval(int step=-1) const;
	Value getGameEndEval() const;

	HashValue getHashValue() const;

	void print() const;

	void changePlayer();
	void applyMove(int sq);
	//void applyMoveWithHint(int sq, int hint);
	void applyNullMove();
	int getPlayer()
	{
		return player;
	}
	void copyFrom(const reversiEnv * env)
	{
		board[0] = env->board[0];
		board[1] = env->board[1];
		player = env->player;
		nullMoveCount = env->nullMoveCount;
		basicEval = env->basicEval;
		hashValue = env->hashValue;
	}
	inline void setTruePossibleMoves(LL mov)
	{
		truePossibleMoves = mov;
	}
	LL truePossibleMoves = -1;
	bool preSet = false;
private:
	u64 board[2];
	int player;
	int nullMoveCount;
	int basicEval;
	HashValue hashValue;
	

	void place(int sq);
};

inline bool reversiEnv::isBlackPlayer() const
{
	return player == 0;
}

inline bool reversiEnv::isWhitePlayer() const
{
	return player == 1;
}

inline bool reversiEnv::isEmpty(int sq) const
{
	return !(board[0] >> sq & 1) && !(board[1] >> sq & 1);
}

inline bool reversiEnv::isMyPiece(int sq) const
{
	return board[player] >> sq & 1;
}

inline bool reversiEnv::isOppPiece(int sq) const
{
	return board[player ^ 1] >> sq & 1;
}

inline bool reversiEnv::isBlackPiece(int sq) const
{
	return board[0] >> sq & 1;
}

inline bool reversiEnv::isWhitePiece(int sq) const
{
	return board[1] >> sq & 1;
}

inline int reversiEnv::countAllPieces() const
{
	return popcount(board[0] | board[1]);
}

inline int reversiEnv::countBlackPieces() const
{
	return popcount(board[0]);
}

inline int reversiEnv::countWhitePieces() const
{
	return popcount(board[1]);
}

inline int reversiEnv::countMyPieces() const
{
	return popcount(board[player]);
}

inline int reversiEnv::countOppPieces() const
{
	return popcount(board[player ^ 1]);
}

inline bool reversiEnv::isGameEnd() const
{
	return countAllPieces() == BOARD_SIZE || nullMoveCount > 1;
}

inline Value reversiEnv::getGameEndEval() const
{
	int d = countMyPieces() - countOppPieces();
	if (d == 0)
		return 0;
	return (d > 0 ? +INF : -INF) + d;
}

inline HashValue reversiEnv::getHashValue() const
{
	return hashValue << 1 | player;
}

inline void reversiEnv::changePlayer()
{
	player ^= 1;
	basicEval = -basicEval;
}

inline void reversiEnv::place(int sq)
{
	assert(isEmpty(sq));

	board[player] ^= 1ull << sq;
	basicEval += VALUE[sq];
	hashValue ^= PIECE_HASH_VALUE[sq][player];
}

#endif
