#pragma once
#ifndef SHINA_MCTS_H
#define SHINA_MCTS_H

#include "reversiEnv.h"
extern clock_t start;


class MctNode {
public:
	MctNode(reversiEnv*envPtr,int mov=-1,MctNode* parentPtr=nullptr):
		player(envPtr->getPlayer()),parent(parentPtr),move(mov),visits(0),wins(0)
	{
		envPtr->changePlayer();
		if (envPtr->isGameEnd())
		{
			score = envPtr->getGameEndEval();
		}
		else {
			score = envPtr->getEval(envPtr->countAllPieces());
		}
		envPtr->changePlayer();
		allPosibleMoves = envPtr->generateMovesLL();
	}
	~MctNode()
	{

	}
	MctNode* UCTSelectChild(int conf);

	MctNode* addChild(int mov, reversiEnv* env);
	
	inline void update(int winner,double k)
	{
		visits++;
		
		wins += (winner == (player^1) ? 1 : (winner == draw ? 0 : -1));
		score += (winner == (player ^ 1) ? k : (winner == draw ? 0 : -k));
	}
	double score;
	int player;
	vector<MctNode*>childrens;
	MctNode* parent;
	int move;
	int visits;
	double wins;
	Board allPosibleMoves = -1;
};
class Mcts {
public:
	Mcts(int cntStep,reversiEnv* env, int iterTimes = 3000,int conf=1000,double kk=100):iters(iterTimes),confidence(conf),k(kk)
	{
		rootNode = new MctNode(env);
		this->env = new reversiEnv(*env);
		this->cneStep = cntStep;
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
	double k;
	int selectBest(LL allPossibleMoves,reversiEnv* env);
	reversiEnv * env;
	int iters;
	int buf[64];
	int cnt = 0;
	int cneStep;
	int confidence;
};


#endif // !SHINA_MCTS_H
