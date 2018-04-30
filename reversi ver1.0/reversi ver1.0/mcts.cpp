//#include "lib\mcts.h"
//
//MctNode * MctNode::UCTSelectChild()
//{
//	double score = -1000000;
//	MctNode* ret = nullptr;
//	//cout << score << endl;
//	for (auto & e : childrens)
//	{
//		double utc = e->wins / e->visits + 1.414*sqrt(log(visits / e->visits));
//		if (utc > score)
//		{
//			score = utc;
//			ret = e;
//		}
//	}
//	return ret;
//}
//
//MctNode* MctNode::addChild(Position mov, reversiEnv * env)
//{
//	MctNode * node = new MctNode(env, mov, this);
//	//cout << "pppp " << allPosibleMoves << endl;
//	allPosibleMoves ^= (1ull << mov);
//	//cout << "ffff " << allPosibleMoves << endl;
//	childrens.push_back(node);
//	return node;
//}
//
//int Mcts::selectBest(LL temp, reversiEnv*env)
//{
//	int cnt = 0;
//	int pos = 0;
//	reversiEnv* state=new reversiEnv(*env);
//	int bitpos = 0;
//
//	int score = -2147483647;
//	int sonScore;
//	int ans = -1;
//	//LL tmp = temp;
//	//while (temp)
//	//{
//	//	if (temp & 1)
//	//	{
//	//		buf[cnt++] = pos;
//	//	}
//	//	pos++;
//	//	temp >>= 1;
//	//}
//	////int choose = buf[rand() % cnt];
//	//temp = tmp;
//
//	while (temp)
//	{
//		bitpos=bitScanForward(temp);
//		state->copyFrom(env);
//		//state->render();
//		state->step(bitpos);
//		//state->render();
//		if (state->isOver())
//		{
//			sonScore = state->evalGameOver();
//		}
//		else {
//			sonScore = state->evalState();
//		}
//		if (sonScore > score)
//		{
//			score = sonScore;
//			ans = bitpos;
//		}
//		temp ^= (1LL << bitpos);
//	}
//	return ans;
//}
//
//int cnt1 = 0;
//int cnt0 = 0;
//
//int Mcts::search()
//{
//	MctNode* node;
//	reversiEnv* state;
//	for (int i = 0; i < iters; i++)
//	{
//		node = rootNode;
//		
//		state = new reversiEnv(*env);
//		srand(time(NULL));
//		// selection
//		while (node->allPosibleMoves == 0 && !node->childrens.empty())
//		{
//			
//			node = node->UCTSelectChild();
//			state->step(node->move);
//			state->ChangePlayer();
//		}
//		
//		// expand
//		//debug(rootNode->allPosibleMoves);
//		if (node->allPosibleMoves != 0)
//		{
//			LL temp = node->allPosibleMoves;
//			int choose = selectBest(temp, state);
//			/*cnt = 0;
//			int pos = 0;
//			LL temp = node->allPosibleMoves;
//			while (temp)
//			{
//				if (temp & 1)
//				{
//					buf[cnt++] = pos;
//				}
//				pos++;
//				temp >>= 1;
//			}
//			int choose = buf[rand()%cnt];*/
//			//cout << "Choose: " << choose << endl;
//			state->step(choose);
//			state->ChangePlayer();
//			node = node->addChild(choose, state);
//		}
//		//debug(rootNode->allPosibleMoves);
//		//cout << rootNode->allPosibleMoves << endl;
//		//system("pause");
//		
//		while (!state->isOver())
//		{
//			if (state->getPossibleMoves() == 0)
//			{
//				state->ChangePlayer();
//			}
//
//			//int minVal = -100000;
//			int pos = -1;
//			Board allmoves = state->getPossibleMoves();
//			/*for (int j = 0; j < 64; j++)
//			{
//				if (allmoves&(1ull << j))
//				{
//					if (RankofPos[j / 8][j % 8] > minVal)
//					{
//						minVal = RankofPos[j / 8][j % 8];
//						pos = j;
//					}
//				}
//			}*/
//			pos = selectBest(allmoves, state);
//			state->step(pos);
//			state->ChangePlayer();
//		}
//		// backpropagate
//		//state->render();
//		int winner = state->calcFinal();
//		//if (winner == 1)
//		//{
//		//	cnt1++;
//		//}
//		//if (winner == 0)
//		//{
//		//	cnt0++;
//		//}
//
//		//state->render();
//		while (node != nullptr)
//		{
//			node->update(winner);
//			
//			node = node->parent;
//		}
//
//
//	}
//
//	double minVisitTimes = -2147483647;
//	int pos = -1;
//	for (auto &e : rootNode->childrens)
//	{
//		if (e->wins / e->visits > minVisitTimes)
//		{
//			minVisitTimes = e->wins/e->visits;
//			pos = e->move;
//		}
//	}
//	//cout << "0: " << cnt0 << " 1: " << cnt1 << endl;
//	return pos;
//
//}
//
//
