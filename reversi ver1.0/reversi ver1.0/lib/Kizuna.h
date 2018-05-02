#pragma once
#ifndef SHINA_KIZINA_H
#define SHINA_KIZINA_H
#include "mcts.h"
#include "alphaBetaSearch.h"


class Kizuna {
public:
	bool step(int x, int y)
	{
		if (x == -1 && y == -1)
		{
			cntStep += 1;
			env.applyNullMove();
			return true;
			//env.applyMove(toSquare(x, y));
			//env.ChangePlayer();
		}
		else {
			//assert(x >= 0 && x <=7 && y >= 0 && y<=7);
			if (!env.isValidMove(x, y))
			{
				cout << "Invalid Moves......" << endl;
				return false;
			}
			cntStep += 1;
			env.applyMove(toSquare(x,y));
			return true;
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
		if (cntStep < STEPLIMIT)
		{
			start = clock();
			Mcts * tree = new Mcts(&env, 30000);
			int ans = tree->search();
			clock_t end = clock();
			double time = (end - start)*1.0 / CLOCKS_PER_SEC;
			cout << "Time: " << time << endl;
			return ans;
		}
		else {
			int tmp[MAX_MOVES];
			int depth = 0;
			SVPair move(-1, 0);
			start = clock();
			if (env.generateMoves(tmp) > 0)
				move = getBestMove(env, depth);
			clock_t end = clock();
			double time = (end - start)*1.0 / CLOCKS_PER_SEC;
			cout << "Time: " << time << endl;
			return move.first;
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

