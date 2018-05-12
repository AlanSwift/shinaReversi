#include "lib\alphaBetaSearch.h"


HashNode hashTable[HASH_TABLE_SIZE + 1];

void initHashTable()
{
	memset(hashTable, 0, sizeof(hashTable));
	for (int i = 0; i < HASH_TABLE_SIZE + 1; i++)
	{
		hashTable[i].iter = -1;
	}
}

SVPair probeHash(int iter,int depth, Value alpha, Value beta, const reversiEnv &pos, bool &cut)
{
	HashValue key = pos.getHashValue();
	int idx = key & HASH_TABLE_MASK;
	HashNode &node = hashTable[idx];

	if (iter!=node.iter||node.key != key)
		return SVPair(-1, UNKNOWN_VALUE);

	if (node.depth >= depth) {
		cut = true;
		if (node.type == EXACT) {
			return SVPair(node.bestMove, node.value);
		}
		else if (node.type == ALPHA) {
			if (node.value <= alpha)
				return SVPair(node.bestMove, node.value);
		}
		else {
			assert(node.type == BETA);
			if (node.value >= beta)
				return SVPair(node.bestMove, node.value);
		}
		cut = false;
	}

	return SVPair(node.bestMove, node.value);
}

void recordHash(int iter,const reversiEnv &pos, Value value, int depth, HashType type, int bestMove)
{
	HashValue key = pos.getHashValue();
	int idx = key & HASH_TABLE_MASK;
	HashNode &node = hashTable[idx];
	if (node.iter != iter)
	{
		node.key = key;
		node.value = value;
		node.depth = depth;
		node.type = type;
		node.bestMove = bestMove;
		node.iter = iter;
	}
	else
	{
		if (node.depth <= depth) {
			node.key = key;
			node.value = value;
			node.depth = depth;
			node.type = type;
			node.bestMove = bestMove;
		}
	}
	
}

SVPair AlphabetaSearch::alphabeta(int depth, Value alpha, Value beta, const reversiEnv &pos, bool requireMove)
{
	if (pos.isGameEnd())
		return SVPair(-1, pos.getGameEndEval());

	bool cut = false;
	SVPair lastsv = probeHash(iter,depth, alpha, beta, pos, cut);
	if (cut && (!requireMove || lastsv.first != -1))
		return lastsv;

	if (depth == 0) {
		Value val = pos.getEval();
		recordHash(iter,pos, val, depth, EXACT, -1);
		return SVPair(-1, val);
	}

#ifndef FIXED_DEPTH
	if (this->isTimeUp())
		return SVPair(-1, pos.getEval());
#endif

	int moves[MAX_MOVES];
	int totMoves;
	if (pos.preSet)
	{
		totMoves = pos.generateMovesWithPreMove(moves,pos.truePossibleMoves);
	}
	else {
		totMoves = pos.generateMoves(moves);
	}

	if (totMoves == 0) {
		reversiEnv newPos(pos);
		newPos.applyNullMove();
		Value val = -alphabeta(depth, -beta, -alpha, newPos).second;
		return SVPair(-1, val);
	}

	if (lastsv.first != -1) {
		for (int i = 0; i < totMoves; ++i) {
			if (moves[i] == lastsv.first) {
				std::swap(moves[0], moves[i]);
				break;
			}
		}
		assert(moves[0] == lastsv.first);
		sortMoves(depth, moves + 1, totMoves - 1);
	}
	else
		sortMoves(depth, moves, totMoves);

	Value bestValue = -BND;
	int bestMove = -1;
	HashType hasht = ALPHA;

	for (int i = 0; i < totMoves; ++i) {
		reversiEnv newPos(pos);
		newPos.applyMove(moves[i]);

		Value val;
		if (lastsv.first != -1 && i != 0) {
			val = -alphabeta(depth - 1, -alpha - 1, -alpha, newPos).second;
			if (val > alpha && val < beta)
				val = -alphabeta(depth - 1, -beta, -alpha, newPos).second;
		}
		else {
			val = -alphabeta(depth - 1, -beta, -alpha, newPos).second;
		}

		if (val > bestValue) {
			bestValue = val;
			bestMove = moves[i];
			if (val >= beta) {
				recordHash(iter, pos, bestValue, depth, BETA, bestMove);
				return SVPair(bestMove, bestValue);
			}
			if (val > alpha) {
				alpha = val;
				hasht = EXACT;
			}
		}
	}

	recordHash(iter,pos, bestValue, depth, hasht, bestMove);

	return SVPair(bestMove, bestValue);
}

void AlphabetaSearch::printBestPath(int depth, const reversiEnv &pos)
{
	Value val = pos.isGameEnd() ? pos.getGameEndEval() : pos.getEval();
	printf("dep=%d, val=%d\n", depth, val);
	pos.print();

	if (depth != 0) {
		bool cut = false;
		SVPair lastsv = probeHash(iter,depth, -BND, BND, pos, cut);
		assert(cut);
		reversiEnv newPos(pos);
		newPos.applyMove(lastsv.first);
		printBestPath(depth - 1, newPos);
	}
}

SVPair AlphabetaSearch::getBestMove(const reversiEnv &pos, int &maxdepth)
{
	//initHashTable();
	//printf("11111\n");
	SVPair ret(-1, 0);

#ifndef FIXED_DEPTH
	for (int depth = 1; depth <= MAX_DEPTH; ++depth) {
#else
	for (int depth = 1; depth <= DEBUG_MAX_DEPTH; ++depth) {
#endif
		//printf("depth: %d\n", depth);
		SVPair cur = alphabeta(depth, -BND, +BND, pos, true);

		ret = cur;
		maxdepth = depth;
#ifndef FIXED_DEPTH
		if (isTimeUp())
			break;
#else
		printf("finish depth %d (%d,%d)\n", depth, cur.first, cur.second);
#endif

		
	}

	// #ifdef FIXED_DEPTH
	//     printBestPath(DEBUG_MAX_DEPTH, pos);
	// #endif
	//cout << maxdepth << endl;
	return ret;
}
