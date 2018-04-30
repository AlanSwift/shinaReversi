#ifndef SEARCH_H_
#define SEARCH_H_


#include "constant.h"
#include "bitboard.h"
#include "position.h"
extern clock_t start;

struct HashNode {
	HashValue key;
	Value value;
	int depth;
	HashType type;
	int bestMove;
};

bool isTimeUp();

void initHashTable();
SVPair probeHash(int depth, Value alpha, Value beta, const Position &pos, bool &cut);
void recordHash(const Position &pos, Value value, int depth, HashType type, int bestMove);

SVPair alphabeta(int depth, Value alpha, Value beta, const Position &pos, bool requireMove = false);
SVPair getBestMove(const Position &pos, int &maxdepth);

inline bool isTimeUp()
{
	return clock()-start > 0.98*3 * CLOCKS_PER_SEC;
}

inline bool approximatelyBetter(int move1, int move2)
{
	return VALUE[move1] > VALUE[move2];
}

inline void sortMoves(int depth, int moves[], int tot)
{
	if (depth >= MOVESORT_MIN_DEPTH)
		std::sort(moves, moves + tot, approximatelyBetter);
}

#endif
