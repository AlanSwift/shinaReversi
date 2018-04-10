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

	setOwnAndEnemy(state);
	nextPlayer ^= 1ull;
	return true;
}

reversiEnv::~reversiEnv()
{
	delete myBoard;
}


