#include "lib\mcts.h"

MctNode * MctNode::UCTSelectChild()
{
	double score = -1000000;
	MctNode* ret = nullptr;
	//cout << score << endl;
	for (auto & e : childrens)
	{
		double utc = e->wins / e->visits + 0.5*sqrt(log(visits / e->visits));
		if (utc > score)
		{
			score = utc;
			ret = e;
		}
	}
	return ret;
}

MctNode* MctNode::addChild(Position mov, reversiEnv * env)
{
	MctNode * node = new MctNode(env, mov, this);
	//cout << "pppp " << allPosibleMoves << endl;
	allPosibleMoves ^= (1ull << mov);
	//cout << "ffff " << allPosibleMoves << endl;
	childrens.push_back(node);
	return node;
}


int Mcts::search()
{
	MctNode* node;
	reversiEnv* state;
	for (int i = 0; i < iters; i++)
	{
		node = rootNode;
		
		state = new reversiEnv(*env);
		srand(time(NULL));
		// selection
		while (node->allPosibleMoves == 0 && !node->childrens.empty())
		{
			
			node = node->UCTSelectChild();
			state->step(node->move);
		}
		
		// expand
		//debug(rootNode->allPosibleMoves);
		if (node->allPosibleMoves != 0)
		{
			cnt = 0;
			int pos = 0;
			LL temp = node->allPosibleMoves;
			while (temp)
			{
				if (temp & 1)
				{
					buf[cnt++] = pos;
				}
				pos++;
				temp >>= 1;
			}
			int choose = buf[rand()%cnt];
			state->step(choose);
			node = node->addChild(choose, state);
		}
		//debug(rootNode->allPosibleMoves);
		//cout << rootNode->allPosibleMoves << endl;
		//system("pause");
		
		while (!state->isOver())
		{
			if (state->getPossibleMoves() == 0)
			{
				state->ChangePlayer();
			}

			int minVal = -100000;
			int pos = -1;
			Board allmoves = state->getPossibleMoves();
			for (int j = 0; j < 64; j++)
			{
				if (allmoves&(1ull << j))
				{
					if (RankofPos[j / 8][j % 8] > minVal)
					{
						minVal = RankofPos[j / 8][j % 8];
						pos = j;
					}
				}
			}
			state->step(pos);
		}
		// backpropagate
		int winner = state->calcFinal();

		while (node != nullptr)
		{
			node->update(winner);
			node = node->parent;
		}


	}

	int minVisitTimes = -1000;
	int pos = -1;
	for (auto &e : rootNode->childrens)
	{
		if (e->visits > minVisitTimes)
		{
			minVisitTimes = e->visits;
			pos = e->move;
		}
	}
	return pos;

}


