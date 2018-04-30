#ifndef BITBOARD_H_
#define BITBOARD_H_

#ifndef _BOTZONE_ONLINE
#include "constant.h"
#include <intrin.h>
#endif

inline int popcount(u64 x)
{
	return __popcnt64(x);
	//return __builtin_popcountll(x);
}

inline u64 getlsb(u64 x)
{
	assert(x);
	return x & -x;
}

inline int getlsbid(u64 x)
{
	assert(x);
	unsigned long index;
	unsigned char noneZero = _BitScanForward64(&index, x);
	return noneZero ? index : -1;
	//return __builtin_ffsll(x) - 1;
}

inline u64 getEmpty(u64 cur, u64 opp)
{
	assert(!(cur & opp));
	return ~(cur | opp);
}

inline void printBB(u64 x)
{
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			printf("%llu", (x >> (i * 8 + j) & 1));
		}
		printf("\n");
	}
	printf("\n");
}

u64 getFrontierBB(u64 cur, u64 opp);
u64 getMovesBB(u64 cur, u64 opp);
void getFlipped(int sq, int player, u64 &cur, u64 &opp, Value &val, HashValue &hash);

#endif
