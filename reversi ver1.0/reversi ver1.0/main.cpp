//
////#include "lib\mcts.h"
////#include "lib\hashlib.h"
////#include "lib\alphaBetaPron.h"
//#include "Kizina.h"
//#include <iostream>
//#include <cstdio>
//using namespace std;
//
////HashLib chessHash;
//clock_t start;
//
//int main()
//{
//	
//	/*int chess[100] = {
//		0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0,
//		0,0,0,1,0,0,0,0,
//		0,0,0,0,0,0,0,0,
//		0,0,0,0,0,1,0,0,
//		0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0
//	};
//	int chess1[100] = {
//		0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0,
//		0,0,0,0,1,0,0,0,
//		0,0,0,1,1,1,0,0,
//		0,0,0,0,1,0,0,0,
//		0,0,0,0,0,0,1,0,
//		0,0,0,0,0,0,0,0
//	};
//	LL ans1 = 0, ans2 = 0;
//	for (int i = 0; i < 64; i++)
//	{
//		if (chess[i])
//		{
//			cout << "&&&&&" << i << endl;
//			ans1 |= (1ll << i);
//			cout << ans1 << endl;
//		}
//		if (chess1[i])
//		{
//			ans2 |= (1ll << i);
//		}
//	}
//	cout << ans1 << " " << ans2 << endl;
//	
//
//	reversiEnv env;
//	env.reset(ans2, ans1);
//	env.render();
//	env.ChangePlayer();
//	AlphaBeta* ab = new AlphaBeta(&env);
//	PII ans = ab->search(0);
//	cout << ans.first << endl;*/
//	
//	/*reversiEnv env;*/
//	/*env.render();*/
//	Kizina env;
//	env.render();
//	int x, y;
//	while (cin >> x >> y)
//	{
//		cout << x << " " << y << endl;
//		//int choose = x * 8 + y;
//		env.step(x,y);
//		//env.ChangePlayer();
//		env.render();
//		start = clock();
//		//AlphaBeta* ab = new AlphaBeta(&env);
//		/*Mcts * tree = new Mcts(&env, 30000);
//		choose = tree->search();*/
//		int choose=env.search();
//		//choose = ans.first;
//		cout << "uuuu" << endl;
//		cout << choose / 8 << " " << choose % 8 << endl;
//		/*env.step(choose);
//		env.ChangePlayer();*/
//		env.step(choose / 8, choose % 8);
//		env.render();
//	}
//
//
//    return 0;
//}
//
