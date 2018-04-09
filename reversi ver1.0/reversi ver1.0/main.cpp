
#include "lib\bitboard.h"

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
	cout << countBit(ans1) << " " << countBit(ans2) << endl;
	LL ans = findCorrectMoves(ans2, ans1);

	int cnt = 0;
	while (cnt<64)
	{
		if (ans & 1)
		{
			cout << "1" << " ";
		}
		else {
			cout << "0 ";
		}
		cnt++;
		if (cnt % 8 == 0)
		{
			cout << endl;
		}
		ans >>= 1;
	}
	showBoard(ans2,ans1);
    return 0;
}

