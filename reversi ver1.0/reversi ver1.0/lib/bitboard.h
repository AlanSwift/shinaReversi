#pragma once
#ifndef SHINA_BITBOARD_H
#define SHINA_BITBOARD_H
#include "config.h"
#include <assert.h>

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
		cout << buf[i] << " ";
		if ((i + 1) % 8 == 0)
		{
			cout << endl;
		}
		own >>= 1;
		opp >>= 1;
	}
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



inline int countBit(Board x)
{
	int ans = 0;
	while (x)
	{
		if (x & 1)
		{
			ans++;
		}
		x >>= 1;
	}
	return ans;
}

inline Board flip_vertical(Board x)
{
	LL k1 = 0x00FF00FF00FF00FF;
	LL k2 = 0x0000FFFF0000FFFF;
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

inline Board calcFlipHalf(Position pos, Board own, Board opp)
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

inline Board calcFlip(Position pos, Board own, Board opp)
{
	/**
	 *  Description
	 *  @param pos: 0-63, the position to take
	 *  @param own: bitboard (0=top left, 63=bottom right)
	 *  @param opp: bitboard
	 *  @param return: flip the stones of the enemy when I place stone at pos
	 */
	cout << "fuck" << pos << endl;
	Board f1 = calcFlipHalf(pos, own, opp);
	Board f2 = calcFlipHalf((~pos)&63, rotate180(own), rotate180(opp));
	return f1 | rotate180(f2);
}



#endif
