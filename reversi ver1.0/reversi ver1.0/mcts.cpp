#include "lib\mcts.h"

MctNode * MctNode::UCTSelectChild()
{
	double score = -1000000;
	MctNode* ret = nullptr;
	//cout << score << endl;
	for (auto & e : childrens)
	{
		double utc = e->wins / e->visits + 1.414*sqrt(log(visits / e->visits));
		if (utc > score)
		{
			score = utc;
			ret = e;
		}
	}
	return ret;
}

MctNode* MctNode::addChild(int mov, reversiEnv * env)
{
	MctNode * node = new MctNode(env, mov, this);
	//cout << "pppp " << allPosibleMoves << endl;
	allPosibleMoves ^= (1ull << mov);
	//cout << "ffff " << allPosibleMoves << endl;
	childrens.push_back(node);
	return node;
}

int Mcts::selectBest(LL temp, reversiEnv*env)
{
	int cnt = 0;
	int pos = 0;
	reversiEnv state=reversiEnv(*env);
	int bitpos = 0;

	int score = 2147483647;
	int sonScore;
	int ans = -1;
	//LL tmp = temp;
	//while (temp)
	//{
	//	if (temp & 1)
	//	{
	//		buf[cnt++] = pos;
	//	}
	//	pos++;
	//	temp >>= 1;
	//}
	////int choose = buf[rand() % cnt];
	//temp = tmp;

	while (temp)
	{
		bitpos=getlsbid(temp);
		//state = reversiEnv(*env);
		state.copyFrom(env);
		//state.print();
		//state->render();
		state.applyMove(bitpos);
		//state.print();
		//state->render();
		// 5 4 3
		if (state.isGameEnd())
		{
			sonScore = state.getGameEndEval();
		}
		else {
			sonScore = state.getEval();
		}
		if (sonScore < score)
		{
			score = sonScore;
			ans = bitpos;
		}
		temp ^= (1LL << bitpos);
	}
	return ans;
}

int cnt1 = 0;
int cnt0 = 0;

int Mcts::search()
{
	MctNode* node;
	reversiEnv state;
	for (int i = 0; i < iters; i++)
	{
		//cout << i << endl;
		node = rootNode;
		
		state.copyFrom(env);
		srand(time(NULL));
		// selection
		//cout << "selection" << endl;
		while (node->allPosibleMoves == 0 && !node->childrens.empty())
		{
			
			node = node->UCTSelectChild();
			state.applyMove(node->move);
			//state->step(node->move);
			//state->ChangePlayer();
		}
		
		// expand
		//debug(rootNode->allPosibleMoves);
		//cout << "expand" << endl;
		if (node->allPosibleMoves != 0)
		{
			LL temp = node->allPosibleMoves;
			int choose = selectBest(temp, &state);
			/*cnt = 0;
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
			int choose = buf[rand()%cnt];*/
			//cout << "Choose: " << choose << endl;
			state.applyMove(choose);
			//state->step(choose);
			//state->ChangePlayer();
			node = node->addChild(choose, &state);
		}
		//debug(rootNode->allPosibleMoves);
		//cout << rootNode->allPosibleMoves << endl;
		//system("pause");
		//cout << "simulation" << endl;
		
		while (!state.isGameEnd())
		{
			if (state.generateMovesLL() == 0)
			{
				state.applyNullMove();
				continue;
			}
			//if (i == 61)
			//{
			//	state.print();
			//	
			//}

			//int minVal = -100000;
			int pos = -1;
			Board allmoves = state.generateMovesLL();
			/*for (int j = 0; j < 64; j++)
			{
				if (allmoves&(1ull << j))
				{
					if (RankofPos[j / 8][j % 8] > minVal)
					{
						minVal = RankofPos[j / 8][j % 8];
						pos = j;
					}
				}
			}*/
			pos = selectBest(allmoves, &state);
			//if (i == 61)
			//{
			//	state.print();
			//	cout << "------------" << pos << endl;
			//}
			
			state.applyMove(pos);
			//state->step(pos);
			//state->ChangePlayer();
		}
		// backpropagate
		//state->render();
		//cout << "backprop" << endl;
		int winner = 0;
		int blackC = state.countBlackPieces();
		int whiteC = state.countWhitePieces();
		//state.print();
		if (blackC == whiteC)
		{
			winner = draw;
		}
		else if (blackC > whiteC)
		{
			winner = black;
		}
		else {
			winner = white;
		}
		//if (winner == 1)
		//{
		//	cnt1++;
		//}
		//if (winner == 0)
		//{
		//	cnt0++;
		//}

		//state->render();
		while (node != nullptr)
		{
			node->update(winner);
			
			node = node->parent;
		}
		//cout << endl;


	}

	double minVisitTimes = -2147483647;
	int pos = -1;
	for (auto &e : rootNode->childrens)
	{
		if (e->wins / e->visits > minVisitTimes)
		{
			minVisitTimes = e->wins/e->visits;
			pos = e->move;
		}
	}
	//cout << "0: " << cnt0 << " 1: " << cnt1 << endl;
	return pos;

}


