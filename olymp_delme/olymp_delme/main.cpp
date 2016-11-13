
#include <iostream>
#include <vector>
using namespace std;

int comb(int a1, int a2, int a3, int a4, int a5)
{
	vector <int> a = { a1,a2,a3,a4,a5 };
	int res = 0;
	int pairs = 1, tres = 1, quads = 1, quints = 1;




	if (a[0] == a[1] == a[2] == a[3] == a[4])quints++;
	else
	{
		for (int i = 0; i < 5; i++)
			for (int j = i + 1; j < 5; j++)
				for (int j1 = i + 2; j1 < 5; j1++)
					for (int j2 = i + 3; j2< 5; j2++)
						if (a[i] == a[j] == a[j1] == a[j2]) { quads++; tres -= 6; }

		for (int i = 0; i < 5; i++)
			for (int j = i + 1; j < 5; j++)
				for (int j1 = i + 2; j1 < 5; j1++)
					if (a[i] == a[j] == a[j1]) { tres++; pairs -= 6; }


		for (int i = 0; i < 5; i++)
			for (int j = i + 1; j < 5; j++)
				if (a[i] == a[j])pairs++;
	}

	if (pairs != 0)return 120 / pairs;
	else return 120;


	/*float k = 1;

	for (int i = 0; i < a.size(); i++)
		for (int j = i + 1; j < a.size(); j++)
			if (a[i] == a[j])
				a.erase(a.begin() + j);
	
	for (int i = 0; i < a.size(); i++)
		if (a[i] == 7) k = (a.size()-1)/a.size();

		 if (a.size() == 5) return 120 * k;
	else if (a.size() == 4) return 24 * k;
	else if (a.size() == 3) return 6 * k;
	else if (a.size() == 2) return 2 * k;
	else return 1;*/
}

int main()
{
	int value = 20160000020;
	int mas[] = {2,4,6,7,8,0};
	int allcomb = 0;
	
	for (int i1 = 0; i1 < 6; i1++)
	{
		for (int i2 = 0; i2 < 6; i2++)
		{
			for (int i3 = 0; i3 < 6; i3++)
			{
				for (int i4 = 0; i4 < 6; i4++)
				{
					for (int i5 = 0; i5 < 6; i5++)
					{
						if ((mas[i1] + mas[i2] + mas[i3] + mas[i4] + mas[i5]) % 3 == 1)
						{
							allcomb += comb(mas[i1], mas[i2], mas[i3], mas[i4], mas[i5]);
						}
					}
				}
			}
		}
	}

	cout << "Answer: " << allcomb << endl;
	system("pause");
	return 0;
}