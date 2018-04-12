#pragma once
#ifndef SHINA_ALPHABETA_PRONING_H
#define SHINA_ALPHABETA_PRONING_H
#include "config.h"
#include "reversiEnv.h"

class AlphaBeta {
public:
	AlphaBeta(reversiEnv* env);
	AlphaBeta(const AlphaBeta&e);
	~AlphaBeta();

	pair<int,int> search(int * maxDepth);
private:
	pair<int,int> __search(reversiEnv* env, int* maxDepth);
	pair<int, int> alphaBetaSearch(int depth, int alpha, int beta, reversiEnv* env, bool requireMove = false);
	reversiEnv* rootState;
	const int MIN_SORT = 3;
	const int MAX_DEPTH = 64;
	const int inf = 0x7f7f7f7f;
	inline bool isTimeUp()
	{
		//return false;
		return (clock()-start) > 0.98 * CLOCKS_PER_SEC*2;
	}
};

#endif