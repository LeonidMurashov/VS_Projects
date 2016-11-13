#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Task
{
	string index;
	string name;
	bool group[3];

	Task(string _index, string _name)
	{
		index = _index;
		name = _name;
		name = name.substr(1);
		if(index.find('A') != string::npos)
			group[0] = true;
		else
			group[0] = false;
		if (index.find('B') != string::npos)
			group[1] = true;
		else
			group[1] = false;
		if (index.find('C') != string::npos)
			group[2] = true;
		else
			group[2] = false;
	}

	bool operator<(Task ob2)
	{
		return (index < ob2.index);
	}
};


int main()
{
	int N;
	bool possible = true;
	cin >> N;
	vector<Task> tasks;
	for (int i = 0; i < N; i++)
	{
		string str1, str2;
		cin >> str1;
		getline(std::cin, str2);
		tasks.push_back(Task(str1, str2));
	}

	sort(tasks.begin(), tasks.end());
	
	short actualGroup;
	if (tasks[0].group[0])
		actualGroup = 0;
	else if (tasks[0].group[1])
		actualGroup = 1;
	else
		actualGroup = 2;

	for (int i = 0; i < N; i++)
	{
		if (!tasks[i].group[actualGroup])
		{
			actualGroup++;
			if (tasks[i].group[2])
			{
				bool anyC = false;
				for (int j = i + 1; j < N; j++)
					if (tasks[j].group[2])
					{
						anyC = true;
						break;
					}
				if (anyC)
					actualGroup += 2;

			}
			if (!tasks[i].group[actualGroup])
			{
				actualGroup++;
				if (!tasks[i].group[actualGroup])
					actualGroup++;
			}
		}
		if (actualGroup > 2)
		{
			possible = false;
			break;
		}
	}
	if (possible)
		for (int i = 0; i < N; i++)
			cout << tasks[i].index << " " << tasks[i].name << endl;
	else
		cout << "Impossible" << endl;

	system("pause");
	return 0;
}