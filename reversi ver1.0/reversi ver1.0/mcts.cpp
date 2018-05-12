#include "lib\mcts.h"
#include "lib\alphaBetaSearch.h"

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

		tscore = (1 - beta)*e->wins / (e->visits+1e-8) + beta*e->score+ sqrt(2*log(visits) / (e->visits+ 1e-8));
		if (tscore > score)
		{
			score = tscore;
			ret = e;
		}
	}
	return ret;
}

MctNode* MctNode::addChild(int mov, reversiEnv * env,int tscore)
{
	MctNode * node = new MctNode(env, mov, this,tscore);
	//cout << "pppp " << allPosibleMoves << endl;
	//debug(allPosibleMoves);
	//cout << mov / 8 << " " << mov % 8 << endl;
	//cout << "************" << endl;
	allPosibleMoves ^= (1ull << mov);
	//debug(allPosibleMoves);
	//system("pause");
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

	while (temp)
	{
		bitpos=getlsbid(temp);
		state.copyFrom(env);
		state.applyMove(bitpos);
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
		if (cnt % 100 == 0 && this->isTimeUp())
		{
			break;
		}
		else
		{
#endif
			node = rootNode;

			state.copyFrom(env);
			srand(time(NULL));
			// selection
			while (node->allPosibleMoves == 0 && !node->childrens.empty())
			{

				node = node->UCTSelectChild(confidence);
				state.applyMove(node->move);
			}

			// expand
			if (node->allPosibleMoves != 0)
			{
				//printf("%d  expand\n", node->stepCnt);
				/*AlphabetaSearch ab;
				ab.recordStartTime();
				state.setTruePossibleMoves(node->allPosibleMoves);
				state.preSet = true;
				int depth = 0;

				SVPair ans = ab.getBestMove(state, depth);
				state.setTruePossibleMoves(-1);
				state.preSet = false;
				state.applyMove(ans.first);

				node = node->addChild(choose, &state, ans.second);*/
				if (node->stepCnt < ALPHABETASTEPLIMIT)
				{
					LL temp = node->allPosibleMoves;
					choose = selectBest(temp, &state);
					state.applyMove(choose);
					node = node->addChild(choose, &state);
				}
				else {
					//int randNum = rand() % 100;
					if (true)
					{
						AlphabetaSearch ab;
						ab.iter = cnt;
						ab.recordStartTime();
						state.setTruePossibleMoves(node->allPosibleMoves);
						state.preSet = true;
						int depth = 0;
						
						SVPair ans = ab.getBestMove(state, depth);
						state.preSet = false;

						state.applyMove(ans.first);
						
						node = node->addChild(ans.first, &state, ans.second);
					}
					else {
						LL temp = node->allPosibleMoves;
						choose = selectBest(temp, &state);
						if (!state.isValidMove(choose / 8, choose % 8))
						{
							debug(node->allPosibleMoves);
							debug(state.truePossibleMoves);
							state.print();
							printf("invalid  22: %d\n", choose);
							system("pause");
						}
						state.applyMove(choose);
						node = node->addChild(choose, &state);
					}
				}
					
				
				/*if (rand() % 100<95)
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
				state.applyMove(choose);
				node = node->addChild(choose, &state);*/
			}

			while (!state.isGameEnd())
			{
				if (state.generateMovesLL() == 0)
				{
					state.applyNullMove();
					continue;
				}
				int pos = -1;
				Board allmoves = state.generateMovesLL();
				if (rand()%100<95)
				{
					pos = selectBest(allmoves, &state);
				}
				else {
					int cntbit=state.generateMoves(buf);
					pos = buf[rand() % cntbit];
				}
				state.applyMove(pos);
			}
			// backpropagate
			int winner = 0;
			int blackC = state.countBlackPieces();
			int whiteC = state.countWhitePieces();
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
			while (node != nullptr)
			{
				node->update(winner,k);
				node = node->parent;
			}
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
			minVisitTimes = e->wins/(e->visits+1e-8);
			pos = e->move;
		}
	}
	cout << cnt << endl;
	return pos;

}


