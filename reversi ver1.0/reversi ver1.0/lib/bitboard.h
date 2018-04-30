#pragma once
#ifndef SHINA_BITBOARD_H
#define SHINA_BITBOARD_H


#include "config.h"
#include <assert.h>
#include <intrin.h>

#define N(x) ((x) >> 8)
#define S(x) ((x) << 8)
#define W(x) (((x) & 0xfefefefefefefefeull) >> 1)
#define E(x) (((x) & 0x7f7f7f7f7f7f7f7full) << 1)
#define NW(x) (N(W(x)))
#define NE(x) (N(E(x)))
#define SW(x) (S(W(x)))
#define SE(x) (S(E(x)))

inline LL getFrontier(Board own, Board opp)
{
	LL empty = ~(own | opp);
	return (N(empty)
		| S(empty)
		| W(empty)
		| E(empty)
		| NW(empty)
		| NE(empty)
		| SW(empty)
		| SE(empty));
}

inline void showBoard(Board own, Board opp)
{
	char buf[64] = {};
	for (int i = 0; i < 64; i++)
	{
		if (own & 1)
		{
			buf[i] = '*';
		}
		else if (opp & 1)
		{
			buf[i] = '#';
		}
		else {
			buf[i] = '-';
		}
		own >>= 1;
		opp >>= 1;
	}
	char out[9][9];
	out[0][0] = 'A';
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (i == 0 && j == 0)	continue;
			if (i == 0)
			{
				out[i][j] = '0' + j - 1;
			}
			else if (j == 0)
			{
				out[i][j] = '0' + i - 1;
			}
			else {
				out[i][j] = buf[(i - 1) * 8 + (j - 1)];
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << out[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

inline Board search_offset_left(Board own, Board enemy,LL mask,LL offset)
{
	LL e = enemy & mask;
	LL blank = ~(own | enemy);
	LL t = e & (own >> offset);
	t |= e & (t >> offset);
	t |= e & (t >> offset);
	t |= e & (t >> offset);
	t |= e & (t >> offset);
	t |= e & (t >> offset);
	return blank & (t >> offset);
}

inline Board search_offset_right(Board own, Board enemy, LL mask, LL offset)
{
	LL e = enemy & mask;
	LL blank = ~(own | enemy);
	LL t = e & (own << offset);
	t |= e & (t << offset);
	t |= e & (t << offset);
	t |= e & (t << offset);
	t |= e & (t << offset);
	t |= e & (t << offset);
	return blank & (t << offset);
}
	

inline Board findCorrectMoves(Board own, Board enemy)
{
	/**
	 *  Description:
	 *  @param own: bitboard (0=top left, 63=bottom right)
	 *  @param enemy: bitboard
	 *  @return: all posible moves
	 */
	LL left_right_mask = 0x7e7e7e7e7e7e7e7eull;
	LL top_bottom_mask = 0x00ffffffffffff00ull;
	LL mask = left_right_mask & top_bottom_mask;
	LL mobility = 0;
	mobility |= search_offset_left(own, enemy, left_right_mask, 1);
	mobility |= search_offset_left(own, enemy, mask, 9);
	mobility |= search_offset_left(own, enemy, top_bottom_mask, 8);
	mobility |= search_offset_left(own, enemy, mask, 7);
	mobility |= search_offset_right(own, enemy, left_right_mask, 1);
	mobility |= search_offset_right(own, enemy, mask, 9);
	mobility |= search_offset_right(own, enemy, top_bottom_mask, 8);
	mobility |= search_offset_right(own, enemy, mask, 7);
	return mobility;
}



inline int popcount(Board x)
{
	return __popcnt64(x);
}

inline int getlsbid(LL x)
{
	unsigned long index;
	unsigned char noneZero=_BitScanForward64(&index, x);
	return noneZero?index:-1;
}
inline u64 getlsb(u64 x)
{
	assert(x);
	return x & -x;
}
inline Board flip_vertical(Board x)
{
	LL k1 = 0x00FF00FF00FF00FFull;
	LL k2 = 0x0000FFFF0000FFFFull;
	x = ((x >> 8) & k1) | ((x & k1) << 8);
	x = ((x >> 16) & k2) | ((x & k2) << 16);
	x = (x >> 32) | (x << 32);
	return x;
}

inline Board flip_diag_a1h8(Board x)
{
	LL k1 = 0x5500550055005500ull;
	LL k2 = 0x3333000033330000ull;
	LL k4 = 0x0f0f0f0f00000000ull;
	LL t = k4 & (x ^ (x << 28));
	x ^= t ^ (t >> 28);
	t = k2 & (x ^ (x << 14));
	x ^= t ^ (t >> 14);
	t = k1 & (x ^ (x << 7));
	x ^= t ^ (t >> 7);
	return x;
}

inline Board rotate90(Board x)
{
	return flip_diag_a1h8(flip_vertical(x));
}

inline Board rotate180(Board x)
{
	return rotate90(rotate90(x));
}

inline Board calcFlipHalf(LL pos, Board own, Board opp)
{
	LL el[4] = { opp, opp & 0x7e7e7e7e7e7e7e7eull, opp & 0x7e7e7e7e7e7e7e7eull, opp & 0x7e7e7e7e7e7e7e7eull };
	LL masks[4] = { 0x0101010101010100ull<<pos, 0x00000000000000fell<<pos, 0x0002040810204080ull<<pos, 0x8040201008040200ull<<pos };
	Board ans = 0;
	LL out = 0;
	for (int i = 0; i < 4; i++)
	{
		out = masks[i] & ((el[i] | ~masks[i]) + 1) & own;
		ans |= (out - (out != 0))& masks[i];
	}
	return ans;
}

inline Board calcFlip(LL pos, Board own, Board opp)
{
	/**
	 *  Description
	 *  @param pos: 0-63, the position to take
	 *  @param own: bitboard (0=top left, 63=bottom right)
	 *  @param opp: bitboard
	 *  @param return: flip the stones of the enemy when I place stone at pos
	 */
	Board f1 = calcFlipHalf(pos, own, opp);
	Board f2 = calcFlipHalf((~pos)&63, rotate180(own), rotate180(opp));
	return f1 | rotate180(f2);
}



#endif
