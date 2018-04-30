//#include "lib\alphaBetaPron.h"
//#include "lib\hashlib.h"
//extern HashLib chessHash;
//
//AlphaBeta::AlphaBeta(reversiEnv * env)
//{
//	rootState = new reversiEnv(*env);
//}
//
//AlphaBeta::AlphaBeta(const AlphaBeta & e)
//{
//	rootState = new reversiEnv(*e.rootState);
//}
//
//AlphaBeta::~AlphaBeta()
//{
//	delete rootState;
//}
//
//PII AlphaBeta::search(int * maxDepth)
//{
//	return __search(rootState, maxDepth);
//}
//
//PII AlphaBeta::__search(reversiEnv * env, int * maxDepth)
//{
//	chessHash.reset();
//
//	PLL ans = PLL(-1, 0);
//
//	for (int i = 0; i < MAX_DEPTH; i++)
//	{
//		PII res = alphaBetaSearch(i + 1, -inf, inf, env, true);
//		ans = res;
//		if (isTimeUp())
//		{
//			break;
//		}
//	}
//	return ans;
//}
//inline bool __comp(int a, int b)
//{
//	return RankofPos[a/8][a%8] > RankofPos[b/8][b%8];
//}
//
//PII AlphaBeta::alphaBetaSearch(int depth, int alpha, int beta, reversiEnv * env, bool requireMove)
//{
//	if (env->isOver())	return PII(-1, env->evalGameOver());
//
//	bool cut = false;
//	PII fromHash = chessHash.probe(env, depth, alpha, beta, &cut);
//	if (cut && (!requireMove || fromHash.first != -1))
//	{
//		return fromHash;
//	}
//
//	if (depth == 0)
//	{
//		int val = env->evalState();
//		chessHash.put(env, val, depth, EXACT, -1);
//		return PII(-1, val);
//	}
//
//	LL possibleMoves = env->getPossibleMoves();
//	if (possibleMoves == 0) {
//		reversiEnv *envSun = new reversiEnv(*env);
//		envSun->ChangePlayer();
//		int val = -alphaBetaSearch(depth, -beta, -alpha, envSun).second;
//		return PII(-1, val);
//	}
//	if (isTimeUp())
//	{
//		return PII(-1, env->evalState());
//	}
//
//	int moves[64] = {};
//	int cntMoves = 0;
//	int pos = 0;
//	LL tmp = possibleMoves;
//	while (tmp)
//	{
//		if (tmp & 1)
//		{
//			moves[cntMoves++] = pos;
//		}
//		pos++;
//		tmp >>= 1;
//	}
//	if (fromHash.first != -1)
//	{
//		for (int i = 0; i < cntMoves; i++)
//		{
//			if (moves[i] == fromHash.first)
//			{
//				swap(moves[0], moves[i]);
//				break;
//			}
//		}
//		if (depth >= MIN_SORT)
//		{
//			sort(moves + 1, moves + cntMoves, __comp);
//		}
//	}
//	else {
//		if (depth >= MIN_SORT)
//		{
//			sort(moves, moves + cntMoves, __comp);
//		}
//	}
//
//
//	int bestVal = -inf;
//	int bestPos = -1;
//	HashType hashtype = ALPHA;
//
//	for (int i = 0; i < cntMoves; i++)
//	{
//		reversiEnv * envSun = new reversiEnv(*env);
//		envSun->step(moves[i]);
//		int val;
//		if (fromHash.first!=-1&&!i)
//		{
//			val = -alphaBetaSearch(depth - 1, -alpha - 1, -alpha, envSun).second;
//			if (val > alpha && val < beta)
//			{
//				val = -alphaBetaSearch(depth - 1, -beta, -alpha, envSun).second;
//			}
//		}
//		else {
//			val = -alphaBetaSearch(depth - 1, -beta, -alpha, envSun).second;
//		}
//		if (val > bestVal)
//		{
//			bestPos = moves[i];
//			bestVal = val;
//			if (val > beta)
//			{
//				chessHash.put(env, bestVal, depth, BETA, bestPos);
//
//				return PII(bestPos, bestVal);
//			}
//			if (val > alpha)
//			{
//				alpha = val;
//				hashtype = EXACT;
//			}
//			
//		}
//	}
//	chessHash.put(env, bestVal, depth, hashtype, bestPos);
//	return PII(bestPos, bestVal);
//
//}
