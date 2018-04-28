#include "lib\reversiEnv.h"

bool reversiEnv::step(Position action)
{
	PLL state = getOwnAndEnemy();
	//cout << nextPlayer << endl;
	//cout << "&&&&& " << action << " " << state.first << " " << state.second << endl;
	Board flip = calcFlip(action, state.first, state.second);
	//cout << "flip:  " << flip << endl;
	if (countBit(flip) == 0)
	{
		return false;
	}
	state.first ^= flip;
	state.first |= (1ull << action);
	state.second ^= flip;
	while (flip)
	{
		int bitpos = bitScanForward(flip);
		basicEval += RankofPos[bitpos / 8][bitpos % 8]*2;
		flip ^= (1ull << bitpos);
	}
	basicEval += RankofPos[action/8][action%8];

	setOwnAndEnemy(state);
	//ChangePlayer();
	return true;
}

int reversiEnv::evalState()
{
	PLL state = getOwnAndEnemy();
	//swap(state.first, state.second);
	int my_tiles = 0, opp_tiles = 0, my_front_tiles = 0, opp_front_tiles = 0;
	double p = 0, c = 0, l = 0, m = 0, f = 0, d = 0;
	//debug(state.first);
	//debug(state.second);
	d = basicEval;

	// Piece difference, frontier disks and disk squares
	LL frontier = getFrontier(state.first, state.second);

	my_tiles = countBit(state.first);
	opp_tiles = countBit(state.second);
	my_front_tiles = countBit(frontier & state.first);
	opp_front_tiles = countBit(frontier & state.second);
	if (my_tiles > opp_tiles)
		p = (100.0 * my_tiles) / (my_tiles + opp_tiles);
	else if (my_tiles < opp_tiles)
		p = -(100.0 * opp_tiles) / (my_tiles + opp_tiles);
	if (my_front_tiles > opp_front_tiles)
		f = -(100.0 * my_front_tiles) / (my_front_tiles + opp_front_tiles);
	else if (my_front_tiles < opp_front_tiles)
		f = (100.0 * opp_front_tiles) / (my_front_tiles + opp_front_tiles);

	// Corner occupancy
	my_tiles = opp_tiles = 0;
	my_tiles += BoardNotEmpty(state.first, toPos(0, 0));
	opp_tiles += BoardNotEmpty(state.second, toPos(0, 0));
	my_tiles += BoardNotEmpty(state.first, toPos(0, 7));
	opp_tiles += BoardNotEmpty(state.second, toPos(0, 7));
	my_tiles += BoardNotEmpty(state.first, toPos(7, 0));
	opp_tiles += BoardNotEmpty(state.second, toPos(7, 0));
	my_tiles += BoardNotEmpty(state.first, toPos(7, 7));
	opp_tiles += BoardNotEmpty(state.second, toPos(7, 7));
	c = 25 * (my_tiles - opp_tiles);
	//c = 25 * (my_tiles - opp_tiles);

	// Corner closeness
	my_tiles = opp_tiles = 0;
	if (isEmpty(toPos(0, 0))) {
		my_tiles += BoardNotEmpty(state.first, toPos(0, 1));
		opp_tiles += BoardNotEmpty(state.second, toPos(0, 1));
		my_tiles += BoardNotEmpty(state.first, toPos(1, 0));
		opp_tiles += BoardNotEmpty(state.second, toPos(1, 0));
		my_tiles += BoardNotEmpty(state.first, toPos(1, 1));
		opp_tiles += BoardNotEmpty(state.second, toPos(1, 1));
	}
	if (isEmpty(toPos(0, 7))) {
		my_tiles += BoardNotEmpty(state.first, toPos(0, 6));
		opp_tiles += BoardNotEmpty(state.second, toPos(0, 6));
		my_tiles += BoardNotEmpty(state.first, toPos(1, 6));
		opp_tiles += BoardNotEmpty(state.second, toPos(1, 6));
		my_tiles += BoardNotEmpty(state.first, toPos(1, 7));
		opp_tiles += BoardNotEmpty(state.second, toPos(1, 7));
	}
	if (isEmpty(toPos(7, 0))) {
		my_tiles += BoardNotEmpty(state.first, toPos(6, 0));
		opp_tiles += BoardNotEmpty(state.second, toPos(6, 0));
		my_tiles += BoardNotEmpty(state.first, toPos(6, 1));
		opp_tiles += BoardNotEmpty(state.second, toPos(6, 1));
		my_tiles += BoardNotEmpty(state.first, toPos(7, 1));
		opp_tiles += BoardNotEmpty(state.second, toPos(7, 1));
	}
	if (isEmpty(toPos(7, 7))) {
		my_tiles += BoardNotEmpty(state.first, toPos(6, 6));
		opp_tiles += BoardNotEmpty(state.second, toPos(6, 6));
		my_tiles += BoardNotEmpty(state.first, toPos(6, 7));
		opp_tiles += BoardNotEmpty(state.second, toPos(6, 7));
		my_tiles += BoardNotEmpty(state.first,toPos(7, 6));
		opp_tiles += BoardNotEmpty(state.second, toPos(7, 6));
	}
	l = -12.5 * (my_tiles - opp_tiles);

	// Mobility
	my_tiles = countBit(findCorrectMoves(state.first, state.second));
	opp_tiles = countBit(findCorrectMoves(state.second, state.first));
	if (my_tiles > opp_tiles)
		m = (100.0 * my_tiles) / (my_tiles + opp_tiles);
	else if (my_tiles < opp_tiles)
		m = -(100.0 * opp_tiles) / (my_tiles + opp_tiles);

	// final weighted score
	double score = ((10 * p) + (801.724 * c) + (382.026 * l) + (78.922 * m) + (74.396 * f) + (10 * d)) * 100;

	return (int)score;
}





