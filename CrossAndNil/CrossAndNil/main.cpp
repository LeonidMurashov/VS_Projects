#include <iostream>
#include <time.h>
using namespace std;

char RandChar()
{
	short a = rand() % 3;
	if (a == 0)
		return '0';
	else if (a == 1)
		return '1';
	return '2';
}

int main()
{
	srand(time(NULL));
	for (int k = 0; k < 100; k++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				cout << RandChar() << " ";
			cout << endl;
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

/*#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <time.h>
using namespace std;
char map[3][3];

void Rotate()
{
	char map2[3][3];
	for(int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			map2[j][2 - i] = map[i][j];
	//memcpy_s(map, sizeof(map), map2, sizeof(map2));
	memcpy(map, map2, sizeof(map));
}
char map3[3][3] = { { '0', '0', '0' },{ '0', '0', '0' },{ '0', '0', '0' } };

void Rotate2()
{
	char map2[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			map2[j][2 - i] = map3[i][j];
	//memcpy_s(map, sizeof(map), map2, sizeof(map2));
	memcpy(map3, map2, sizeof(map3));
}

bool CheckWin()
{
	for (int i = 0; i < 4; i++)
	{
		if (map3[0][0] == '1' && map3[0][1] == '1' && map3[0][2] == '1')
		{
			return true;
		}
		if (map3[0][0] == '2' && map3[0][1] == '2' && map3[0][2] == '2')
		{
			return true;
		}

		if (map3[0][0] == '1' && map3[1][1] == '1' && map3[2][2] == '1')
		{
			return true;
		}
		if (map3[0][0] == '2' && map3[1][1] == '2' && map3[2][2] == '2')
		{
			return true;
		}

		if (map3[0][1] == '1' && map3[1][1] == '1' && map3[2][1] == '1')
		{
			return true;
		}
		if (map3[0][1] == '2' && map3[1][1] == '2' && map3[2][1] == '2')
		{
			return true;
		}
		Rotate2();
	}
	return false;
}

char mapTest[3][3] = { {'1', '2', '2' },{ '2', '1', '2' },{ '1','1','1' } };
  
int main()
{
	srand(time(NULL));
	while (true)
	{
		
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				map3[i][j] = '0';

		bool crossWin = false, nilWin = false;
		int count1 = 0, count2 = 0;
		int passes = 9;
		for (int i = 0; i < passes; i++)
		{
			generation:
			int x = rand() % 3,
				y = rand() % 3;
			if (map3[x][y] != '0')
				goto generation;
			map3[x][y] = i % 2 == 0 ? '1' : '2';
			if(CheckWin()) break;

		}
		//memcpy(map3, mapTest, sizeof(map3));
		//cout << CheckWin() << endl;
		//system("pause");
		
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				char a = map3[i][j];
				map[i][j] = a;

				if (a == '1')
					count1++;
				if (a == '2')
					count2++;
			}

		float winCount = 0;
		for (int i = 0; i < 4; i++)
		{
			if (map[0][0] == '1' && map[0][1] == '1' && map[0][2] == '1')
			{
				winCount++;
				crossWin = true;
			}
			if (map[0][0] == '2' && map[0][1] == '2' && map[0][2] == '2')
			{
				winCount++;
				nilWin = true;
			}

			if (map[0][0] == '1' && map[1][1] == '1' && map[2][2] == '1')
			{
				winCount += 0.5;
				crossWin = true;
			}
			if (map[0][0] == '2' && map[1][1] == '2' && map[2][2] == '2')
			{
				winCount += 0.5;
				nilWin = true;
			}

			if (map[0][1] == '1' && map[1][1] == '1' && map[2][1] == '1')
			{
				winCount += 0.5;
				crossWin = true;
			}
			if (map[0][1] == '2' && map[1][1] == '2' && map[2][1] == '2')
			{
				winCount += 0.5;
				nilWin = true;
			}
			Rotate();
		}
		// winCount > 1 - exists
		if (crossWin && nilWin || (count1 - 1 != count2 && count1 != count2) || (crossWin && count1 - 1 != count2) || (nilWin && count1 != count2))
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
		cout << endl;
	}
	system("pause");
	return 0;
	}*/