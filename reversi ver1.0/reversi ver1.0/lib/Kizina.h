#pragma once
#ifndef SHINA_KIZINA_H
#define SHINA_KIZINA_H
#include "mcts.h"
#include "alphaBetaPron.h"
#include "reversiEnv.h"


class Kizina {
public:
	void step(int x, int y)
	{
		if (x == -1 && y == -1)
		{
			cntStep += 1;
			env.ChangePlayer();
		}
		else {
			assert(x < 0 || x >7 || y < 0 || y>7);
			cntStep += 1;
			env.step(x * 8 + y);
			env.ChangePlayer();
		}
	}
	void render()
	{
		env.render();
	}
	int search()
	{
		if (cntStep < 4000)
		{
			
			Mcts * tree = new Mcts(&env, 90000);
			return tree->search();
		}
		else {
			
			start = clock();
			AlphaBeta* ab = new AlphaBeta(&env);
			return ab->search(0).first;
		}
	}
	int getPlayer()
	{
		return env.getPlayer();
	}

private:
	int cntStep = 0;
	int deep = 30000;
	reversiEnv env;
	


};


#endif // !SHINA_KIZINA_H

