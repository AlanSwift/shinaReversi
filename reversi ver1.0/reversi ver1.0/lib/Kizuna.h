#pragma once
#ifndef SHINA_KIZINA_H
#define SHINA_KIZINA_H
#include "mcts.h"


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
				cout << x << " " << y << "&&&&&&" << endl;
				system("pause");
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
	int search(int confidence,double k)
	{
		Mcts * tree = new Mcts(cntStep,&env, 30000,confidence,k);
		initHashTable();
		tree->recordStartTime();
		int ans = tree->search();
		double time = tree->getTime();
		cout << "Time: " << time << endl;
		delete tree;
		return ans;
	}
	int getPlayer()
	{
		
		return env.getPlayer();
	}
	bool isGameEnd()
	{
		return env.isGameEnd();
	}
	int getBlackCount()
	{
		return env.countBlackPieces();
	}
	int getWhiteCount()
	{
		return env.countWhitePieces();
	}

private:
	int cntStep = 0;
	int deep = 30000;
	reversiEnv env;
	
	/*Position pos;*/


};


#endif // !SHINA_KIZINA_H

