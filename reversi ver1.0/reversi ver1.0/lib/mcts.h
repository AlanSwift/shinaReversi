#pragma once
#ifndef SHINA_MCTS_H
#define SHINA_MCTS_H

#include "reversiEnv.h"

/*
	player is the player just moved.
*/

class MctNode {
public:
	MctNode(reversiEnv*envPtr,Position mov=-1,MctNode* parentPtr=nullptr):
		player(envPtr->getPlayer()^1),parent(parentPtr),move(mov),visits(0),wins(0)
	{
		allPosibleMoves = envPtr->getPossibleMoves();
	}
	~MctNode()
	{

	}
	MctNode* UCTSelectChild();

	MctNode* addChild(Position mov, reversiEnv* env);
	
	inline void update(int winner)
	{
		visits++;
		wins += (winner == player ? 1 : (winner == draw ? 0 : -1));
	}
	
	int player;
	vector<MctNode*>childrens;
	MctNode* parent;
	Position move;
	int visits;
	double wins;
	Board allPosibleMoves = -1;
};
class Mcts {
public:
	Mcts(reversiEnv* env, int iterTimes = 3000):iters(iterTimes)
	{
		rootNode = new MctNode(env);
		this->env = new reversiEnv(*env);

	}
	int search();

	~Mcts()
	{
		delete env;
		MctNode* ptr;
		queue<MctNode*>rabish;
		queue<MctNode*>tmp;
		if (rootNode != nullptr)
		{
			tmp.push(rootNode);
			while (!tmp.empty())
			{
				ptr = tmp.front();
				tmp.pop();
				rabish.push(ptr);
				for (auto & e : ptr->childrens)
				{
					rabish.push(e);
				}
			}
			while (!rabish.empty())
			{
				delete rabish.front();
				rabish.pop();
			}
		}
	}

private:
	MctNode * rootNode;
	reversiEnv * env;
	int iters;
	int buf[64];
	int cnt = 0;
	const int RankofPos[10][10] =
	{
		{ 300 , 0,   20,  15,  15,  20,  0, 300 },
		{ 0,    0,   10,  11,  11,  10,  0,   0 },
		{ 20,   10,  20,  12,  12,  20, 10,  20 },
		{ 15,   11,  12,  10,  10,  12, 11,  15 },
		{ 15,   11,  12,  10,  10,  12, 11,  15 },
		{ 20,   10,  20,  12,  12,  20, 10,  20 },
		{ 0,     0,  10,  11,  11,  10,  0,   0 },
		{ 300,   0,  20,  15,  15,  20,  0, 300 }
	};
};


#endif // !SHINA_MCTS_H