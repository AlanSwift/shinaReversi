#include "lib\Kizuna.h"
#include <iostream>
#include <cstdio>
using namespace std;

clock_t start;

int main()
{
	Kizuna env;
	env.render();
	int x, y;
	while (cin >> x >> y)
	{
		cout << x << " " << y << endl;
		env.step(x,y);
		env.render();
		int choose=env.search();
		if (choose == -1)
		{
			cout << "Solution:" << endl;
			cout << -1 << " " << -1 << endl;
			env.step(-1, -1);
		}
		else {
			cout << "Solution:" << endl;
			cout << choose / 8 << " " << choose % 8 << endl;
			env.step(choose / 8, choose % 8);
		}
		env.render();
	}
    return 0;
}

