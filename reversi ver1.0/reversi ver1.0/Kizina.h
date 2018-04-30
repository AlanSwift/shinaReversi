#pragma once
#ifndef SHINA_KIZINA_H
#define SHINA_KIZINA_H
//#include "mcts.h"
//#include "alphaBetaPron.h"
//#include "reversiEnv.h"
#include "position.h"
#include "alphaBetaSearch.h"


class Kizina {
public:
	void step(int x, int y)
	{
		if (x == -1 && y == -1)
		{
			cntStep += 1;
			pos.applyNullMove();
			//pos.applyMove(toSquare(x, y));
			//env.ChangePlayer();
		}
		else {
			//assert(x >= 0 && x <=7 && y >= 0 && y<=7);
			cntStep += 1;
			pos.applyMove(toSquare(x,y));
			//env.step(x * 8 + y);
			//env.ChangePlayer();
		}
	}
	void render()
	{
		pos.print();
		//env.render();
	}
	int search()
	{
		if (cntStep < 0)
		{
			
			/*Mcts * tree = new Mcts(&env, 90000);
			return tree->search();*/
		}
		else {
			int tmp[MAX_MOVES];
			int depth = 0;
			SVPair move(-1, 0);
			start = clock();
			if (pos.generateMoves(tmp) > 0)
				move = getBestMove(pos, depth);
			return move.first;
			//start = clock();
			//AlphaBeta* ab = new AlphaBeta(&env);
			//return ab->search(0).first;
		}
	}
	int getPlayer()
	{
		
		return pos.getPlayer();
	}

private:
	int cntStep = 0;
	int deep = 30000;
	/*reversiEnv env;*/
	
	Position pos;


};


#endif // !SHINA_KIZINA_H

