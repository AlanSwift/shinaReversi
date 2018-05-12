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
	int iter;
};


void initHashTable();
SVPair probeHash(int iter,int depth, Value alpha, Value beta, const reversiEnv &pos, bool &cut);
void recordHash(int iter,const reversiEnv &pos, Value value, int depth, HashType type, int bestMove);



inline bool approximatelyBetter(int move1, int move2)
{
	return VALUE[move1] > VALUE[move2];
}

inline void sortMoves(int depth, int moves[], int tot)
{
	if (depth >= MOVESORT_MIN_DEPTH)
		std::sort(moves, moves + tot, approximatelyBetter);
}


class AlphabetaSearch
{
public:
	SVPair alphabeta(int depth, Value alpha, Value beta, const reversiEnv &pos, bool requireMove = false);
	SVPair getBestMove(const reversiEnv &pos, int &maxdepth);
	void printBestPath(int depth, const reversiEnv &pos);
	inline void recordStartTime()
	{
		start = clock();
	}
	inline double getTime()
	{
		return (clock() - start)*1.0 / CLOCKS_PER_SEC;
	}
	inline bool isTimeUp()
	{
		return clock() - start > 0.98*ALPHABETATIMELIMIT * CLOCKS_PER_SEC;
	}

	int iter;
private:
	
	
	clock_t start;

};

#endif
