
#include "lib\mcts.h"

int main()
{
	/*
	int chess[100] = {
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,1,1,1,0,1,1,
		0,0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0
	};
	int chess1[100] = {
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0
	};
	LL ans1 = 0, ans2 = 0;
	for (int i = 0; i < 64; i++)
	{
		if (chess[i])
		{
			cout << "&&&&&" << i << endl;
			ans1 |= (1ll << i);
			cout << ans1 << endl;
		}
		if (chess1[i])
		{
			ans2 |= (1ll << i);
		}
	}
	cout << ans1 << " " << ans2 << endl;
	
	reversiEnv env;
	env.reset(ans2, ans1);
	env.render();
	env.step(29);
	env.render();
	env.step(21);
	env.render();
	cout << env.calcFinal() << endl;*/

	reversiEnv env;
	env.render();
	
	Mcts * tree = new Mcts(&env, 30000);
	int choose = tree->search();
	cout << "uuuu" << endl;
	cout << choose / 8 << " " << choose % 8 << endl;
	env.step(choose);
	env.render();

	
	int x, y;
	while (cin >> x >> y)
	{
		cout << x << " " << y << endl;
		int choose = x * 8 + y;
		env.step(choose);
		env.render();
		
		Mcts * tree = new Mcts(&env, 30000);
		choose = tree->search();
		cout << "uuuu" << endl;
		cout << choose / 8 << " " << choose % 8 << endl;
		env.step(choose);
		env.render();
	}


    return 0;
}

