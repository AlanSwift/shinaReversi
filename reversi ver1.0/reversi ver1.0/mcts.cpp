#include "lib\mcts.h"

MctNode * MctNode::UCTSelectChild(int confidience)
{
	double score = -1000000;
	double tscore;
	MctNode* ret = nullptr;
	//cout << score << endl;
	double beta = sqrt( confidience/ (3 * visits + confidience));
	
	for (auto & e : childrens)
	{
		//double utc = e->wins / e->visits + 1.414*sqrt(log(visits / e->visits));

		tscore = (1 - beta)*e->wins / e->visits + beta*e->score+ sqrt(2*log(visits) / e->visits);
		if (tscore > score)
		{
			score = tscore;
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
			sonScore = state.getEval(state.countAllPieces());
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
	int choose;
	reversiEnv state;
#ifdef FIXED_DEPTH
	for (int i = 0; i < iters; i++)
	{
#else
	int cnt = 0;
	while(1)
	{
		++cnt;
		if (cnt % 1000 == 0 && isTimeUp())
		{
			break;
		}
		else
		{
#endif
			//cout << i << endl;
			node = rootNode;

			state.copyFrom(env);
			srand(time(NULL));
			// selection
			//cout << "selection" << endl;
			while (node->allPosibleMoves == 0 && !node->childrens.empty())
			{

				node = node->UCTSelectChild(confidence);
				state.applyMove(node->move);
				//state->step(node->move);
				//state->ChangePlayer();
			}

			// expand
			//debug(rootNode->allPosibleMoves);
			//cout << "expand" << endl;
			if (node->allPosibleMoves != 0)
			{

				if (rand() % 100<95)
				{
					LL temp = node->allPosibleMoves;
					choose = selectBest(temp, &state);
				}
				else {
					int bitcnt = 0;
					int pos = 0;
					
					LL temp = node->allPosibleMoves;
					while (temp)
					{
						buf[bitcnt++] = getlsbid(temp);
						
						temp ^= getlsb(temp);
					}
					choose = buf[rand()%bitcnt];
				}
				
				
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
				if (rand()%100<95)
				{
					pos = selectBest(allmoves, &state);
				}
				else {
					int cntbit=state.generateMoves(buf);
					pos = buf[rand() % cntbit];
				}
				
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
				node->update(winner,k);
				node = node->parent;
			}
			//cout << endl;

#ifdef FIXED_DEPTH
#else
		}
#endif
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
	cout << cnt << endl;
	//cout << "0: " << cnt0 << " 1: " << cnt1 << endl;
	return pos;

}


