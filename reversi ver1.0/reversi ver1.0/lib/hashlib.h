#pragma once
#ifndef SHINA_HASHLIB_H
#define SHINA_HASHLIB_H
#include "config.h"

enum HashType{
	EXACT,
	ALPHA,
	BETA
};

class HashLib {
public:
	HashLib(){}

	inline void reset()
	{
		memset(hashTable, 0, sizeof(hashTable));
	}

	inline void put(reversiEnv *env, int value, int depth, HashType type, int bestMove)
	{
		LL key = env->getHashcode();
		int idx = key & HASH_TABLE_MASK;
		HashNode &node = hashTable[idx];

		if (node.depth <= depth) {
			node.key = key;
			node.val = value;
			node.depth = depth;
			node.type = type;
			node.bestMove = bestMove;
		}
	}
	inline PII probe(reversiEnv* env, int depth, int alpha, int beta, bool * cut)
	{
		LL key = env->getHashcode();
		int idx = key & HASH_TABLE_MASK;
		HashNode &node = hashTable[idx];

		if (node.key != key)
		{
			return PII(-1, 2e8);
		}
			

		if (node.depth >= depth) {
			*cut = true;
			if (node.type == EXACT) {
				return PII(node.bestMove, node.val);
			}
			else if (node.type == ALPHA) {
				if (node.val <= alpha)
					return PII(node.bestMove, node.val);
			}
			else {
				assert(node.type == BETA);
				if (node.val >= beta)
					return PII(node.bestMove, node.val);
			}
			*cut = false;
		}

		return PII(node.bestMove, node.val);
	}
	

private:
	struct HashNode {
		LL key;
		int val;
		int depth;
		HashType type;
		int bestMove;

	};
	

	enum { HASH_TABLE_SIZE = 1 << 23 };
	const int HASH_TABLE_MASK = HASH_TABLE_SIZE - 1;

	HashNode hashTable[HASH_TABLE_SIZE + 1];

	
};


#endif
