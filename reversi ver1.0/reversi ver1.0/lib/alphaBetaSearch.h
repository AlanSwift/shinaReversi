#ifndef SHINA_SEARCH_H_
#define SHINA_SEARCH_H_


#include "config.h"
#include "bitboard.h"
#include "reversiEnv.h"
extern clock_t start;

struct HashNode {
	HashValue key;
	Value value;
	int depth;
	HashType type;
	int bestMove;
};


void initHashTable();
SVPair probeHash(int depth, Value alpha, Value beta, const reversiEnv &pos, bool &cut);
void recordHash(const reversiEnv &pos, Value value, int depth, HashType type, int bestMove);

SVPair alphabeta(int depth, Value alpha, Value beta, const reversiEnv &pos, bool requireMove = false);
SVPair getBestMove(const reversiEnv &pos, int &maxdepth);



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
