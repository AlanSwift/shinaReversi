#pragma once
#ifndef SHINA_KIZINA_H
#define SHINA_KIZINA_H
#include "lib\mcts.h"
//#include "alphaBetaPron.h"
//#include "reversiEnv.h"
#include "lib\reversiEnv.h"
#include "alphaBetaSearch.h"


class Kizuna {
public:
	void step(int x, int y)
	{
		if (x == -1 && y == -1)
		{
			cntStep += 1;
			env.applyNullMove();
			//env.applyMove(toSquare(x, y));
			//env.ChangePlayer();
		}
		else {
			//assert(x >= 0 && x <=7 && y >= 0 && y<=7);
			cntStep += 1;
			env.applyMove(toSquare(x,y));
			//env.step(x * 8 + y);
			//env.ChangePlayer();
		}
	}
	void render()
	{
		env.print();
		//env.render();
	}
	int search()
	{
		if (cntStep < 40)
		{
			
			Mcts * tree = new Mcts(&env, 30000);
			return tree->search();
		}
		else {
			int tmp[MAX_MOVES];
			int depth = 0;
			SVPair move(-1, 0);
			start = clock();
			if (env.generateMoves(tmp) > 0)
				move = getBestMove(env, depth);
			return move.first;
			//start = clock();
			//AlphaBeta* ab = new AlphaBeta(&env);
			//return ab->search(0).first;
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
	
	/*Position pos;*/


};


#endif // !SHINA_KIZINA_H

