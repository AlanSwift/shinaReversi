
#include "lib\bitboard.h"
#include "lib\reversiEnv.h"

int main()
{
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
	

    return 0;
}

