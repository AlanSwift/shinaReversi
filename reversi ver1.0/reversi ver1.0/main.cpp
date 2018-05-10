//#include "lib\Kizuna.h"
//#include <iostream>
//#include <cstdio>
//using namespace std;
//
//clock_t start;
//
//int main()
//{
//	Kizuna env1, env2;
//	int conf1 = 1000;//shangyici 2000 ying
//	int conf2 = 2000;
//	double k1 = 400;
//	double k2 = 400;
//	int choose;
//	do {
//		choose = env1.search(conf1,k1);
//		if (choose == -1)
//		{
//			env1.step(-1, -1);
//			env2.step(-1, -1);
//			
//		}
//		else {
//			env1.step(choose / 8, choose % 8);
//			env2.step(choose / 8, choose % 8);
//			
//		}
//		env1.render();
//		choose = env2.search(conf2,k2);
//		if (choose == -1)
//		{
//			env2.step(-1, -1);
//			env1.step(-1, -1);
//		}
//		else {
//			env2.step(choose / 8, choose % 8);
//			env1.step(choose / 8, choose % 8);
//		}
//		env1.render();
//	} while (!env1.isGameEnd());
//	cout << "Game end....." << endl;
//	cout << "Black: " << env1.getBlackCount() << endl;
//	cout << "White: " << env1.getWhiteCount() << endl;
//	if (env1.getBlackCount() > env1.getWhiteCount())
//	{
//		cout << "Winner: Black!" << endl;
//	}
//	else if (env1.getBlackCount() < env1.getWhiteCount())
//	{
//		cout << "Winner: White!" << endl;
//	}
//	else {
//		cout << "Winner: Draw!" << endl;
//	}
//	/*Kizuna env;
//	env.render();
//	int x, y;
//	while (cin >> x >> y)
//	{
//		cout << x << " " << y << endl;
//		env.step(x,y);
//		env.render();
//		int choose=env.search();
//		if (choose == -1)
//		{
//			cout << "Solution:" << endl;
//			cout << -1 << " " << -1 << endl;
//			env.step(-1, -1);
//		}
//		else {
//			cout << "Solution:" << endl;
//			cout << choose / 8 << " " << choose % 8 << endl;
//			env.step(choose / 8, choose % 8);
//		}
//		env.render();
//		if (env.isGameEnd())
//		{
//			cout << endl;
//			cout << "Game end....." << endl;
//			cout << "Black: " << env.getBlackCount() << endl;
//			cout << "White: " << env.getWhiteCount() << endl;
//			if (env.getBlackCount() > env.getWhiteCount())
//			{
//				cout << "Winner: Black!" << endl;
//			}
//			else if (env.getBlackCount() < env.getWhiteCount())
//			{
//				cout << "Winner: White!" << endl;
//			}
//			else {
//				cout << "Winner: Draw!" << endl;
//			}
//			return 0;
//		}
//	}*/
//    return 0;
//}
//
