#include "lib\config.h"

void debug(LL x)
{
	cout << "--------Debug-------------" << endl;
	for (int i = 0; i < 64; i++)
	{
		if (x&(1ull << i))
		{
			cout << "o" << " ";
		}
		else {
			cout << "-" << " ";
		}
		if ((i + 1) % 8 == 0)
		{
			cout << endl;
		}
	}
	cout << "$$$$$$$$$$$$$$$$$$$$" << endl;
}