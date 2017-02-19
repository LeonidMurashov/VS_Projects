#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool IsSimmetric(string a)
{
	for (int i = 0; i < a.size() / 2; i++)
		if (a[i] != a[a.size() - 1 - i])
			return false;
	return true;
}

bool AreSimmetric(string a, string b)
{
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[a.size() - 1 - i])
			return false;
	return true;
}

int main()
{
	map<int, string> strings;
	map<int, int> simmetrical;
	map<int, bool> isSimmetric;
	map<int, int> costs;
	
	int k, n;
	cin >> k >> n;
	
	for (int i = 0; i < k; i++)
	{
		string a; 
		int cost;
		cin >> a >> cost;

		costs[i] = cost;
		simmetrical[i] = -1;

		if (IsSimmetric(a))
			isSimmetric[i] = true;
		else
			isSimmetric[i] = false;

		for (auto& item : strings)
			if (AreSimmetric(a, item.second) && simmetrical[item.first] == -1)
			{
				simmetrical[item.first] = i;
				simmetrical[i] = item.first;
				break;
			}
		strings[i] = a;
	}

	for (auto& item : simmetrical)
	{
		cout << strings[item.first] << " " << strings[item.second] << endl;
	}

	int maxCost = 0;
	for (auto& item : isSimmetric)
	{
		if (item.second == true && costs[item.first] > 0)
		{
			if (costs[item.first] > maxCost)
				maxCost = costs[item.first];
		}
	}

	system("pause");
	return 0;
}