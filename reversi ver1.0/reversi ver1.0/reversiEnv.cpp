#include "lib\reversiEnv.h"

bool reversiEnv::step(Position action)
{
	PLL state = getOwnAndEnemy();
	cout << nextPlayer << endl;
	cout << "&&&&& " << action << " " << state.first << " " << state.second << endl;
	Board flip = calcFlip(action, state.first, state.second);
	cout << "flip:  " << flip << endl;
	if (countBit(flip) == 0)
	{
		return false;
	}
	state.first ^= flip;
	state.first |= (1 << action);
	state.second ^= flip;

	setOwnAndEnemy(state);
	nextPlayer ^= 1;
	return true;
}


