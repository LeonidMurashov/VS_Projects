#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include "Extra.hpp"
using namespace std;

vector<map<string, string>> eventsRaw;
vector<map<string, string>> structureRaw;
char* eventsAdress = "D:\\Windows\\Desktop\\course-217-events.csv";
char* structureAdress = "D:\\Windows\\Desktop\\course-217-structure.csv";
int i2 = 0;

struct Step
{
	int id;
	int position;
	long long viewed = 0, returned = 0;
	double returnability = 0;

	Step(int _id, int _position)
	{
		id = _id;
		position = _position;
	}

	void CalculateReturnability()
	{
		if (viewed != 0)
			returnability = returned / (double)viewed;
	}
};

vector<Step*> structure;
Step* FindStepById(int id)
{
	int N = structure.size();
	for (int i = 0; i < N; i++)
		if (structure[i]->id == id)
			return structure[i];
	return nullptr;
}

struct Student
{
	int id;
	vector<pair<int, vector<long long>>> stats; // <<stepID, <times>>>

	Student(int _id)
	{
		id = _id;
	}

	void PushBackInStats(int stepID, long long time)
	{
		for(int i = 0; i < stats.size(); i++)
			if (stats[i].first == stepID)
			{
				stats[i].second.push_back(time);
				return;
			}
		
		// If does not exists
		stats.push_back(make_pair(stepID, vector<long long>{ time }));
	}

	static bool StatsComparator(pair<int, vector<long long>> a, pair<int, vector<long long>> b)
	{
		return FindStepById(a.first)->position < FindStepById(b.first)->position;
	}
	void SortStats()
	{
		sort(stats.begin(), stats.end(), StatsComparator);
	
		// Sort times
		for (auto &i : stats)
			sort(i.second.begin(), i.second.end());
	}

	void Analize()
	{
		for (int i = 0; i < stats.size(); i++)
		{
			Step* step = FindStepById(stats[i].first);
			step->viewed++;

			if(i != stats.size() - 1)
			{
				if (FindStepById(stats[i + 1].first)->position - step->position == 1)
				{
					long long minTime = stats[i].second[0],
						maxTime = stats[i].second[stats[i].second.size() - 1];
					for (int j = 0; j < stats[i + 1].second.size(); j++)
					{
						long long nextStepTimeI = stats[i + 1].second[j];
						if (minTime < nextStepTimeI && nextStepTimeI < maxTime)
						{
							step->returned++;
							break;
						}
					}
				}
			}
		}
	}
};

// Read and remember Raw data
void FillArray(vector<map<string, string>> &myArray, char* fileAdress)
{
	myArray.clear();
	int fileSize = FileSize(fileAdress) / 31; // characters in line average count 
	ifstream file;
	system("cls");
	cout << "Reading files: 0%";
	file.open(fileAdress);
	assert(file.is_open());

	string str, prevStr;

	file >> str;
	vector<string> titles = split(str);
	short  titlesSize = titles.size();
	while (!file.eof())
	{
		vector<string> data;
		prevStr = str;
		file >> str;

		data = split(str);

		map<string, string> toArray;
		for (int i = 0; i < titlesSize; i++)
			toArray[titles[i]] = data[i];
		myArray.push_back(toArray);
		i2++;
		if (i2 % 5000 == 0) { SetCursorPosistion(15, 0); cout << to_string(int(i2 / (double)fileSize * 100) + 1) + "%"; }
	}
	file.close();
	i2 = 0;
	SetCursorPosistion(0, 0);
	cout << "Reading files: 100%";
}

bool CompareStepsPosition(map<string, string> a, map<string, string> b)
{
	int mPA = stoi(a["module_position"]), mPB = stoi(b["module_position"]),
		lPA = stoi(a["lesson_position"]), lPB = stoi(b["lesson_position"]),
		sPA = stoi(a["step_position"]), sPB = stoi(b["step_position"]);

	if (mPA != mPB)
		return mPA < mPB;
	else if (lPA != lPB)
		return lPA < lPB;
	else
		return sPA < sPB;
}

bool CompareStepsRetunability(Step* a, Step* b)
{
	return a->returnability > b->returnability;
}

vector<Student*> students;
Student* FindStudentByID(int id)
{
	int N = students.size();
	for (int i = 0; i < N; i++)
		if (students[i]->id == id)
			return students[i];
	return nullptr;
}

int main()
{
	FillArray(structureRaw, structureAdress);
	FillArray(eventsRaw, eventsAdress);

	// Processing Raw structure
	sort(structureRaw.begin(), structureRaw.end(), CompareStepsPosition);
	for (int i = 0; i < structureRaw.size(); i++)
		structure.push_back(new Step(stoi(structureRaw[i]["step_id"]), i));
		
	// Fill in students activity
	cout << endl << "Preparing data: 0%";
	int N = eventsRaw.size();
	for (int i = 0; i < N; i++)
	{
		int userID = stoi(eventsRaw[i]["user_id"]),
			stepID = stoi(eventsRaw[i]["step_id"]);
		long long eventTime = stoll(eventsRaw[i]["time"]);
		Student* student = FindStudentByID(userID);
		if (student)
		{
			student->PushBackInStats(stepID, eventTime);
		}
		else
		{
			student = new Student(userID);
			student->PushBackInStats(stepID, eventTime);
			students.push_back(student);
		}
		if (i2 % 1000 == 0)
		{
			SetCursorPosistion(16, 1);
			cout << to_string(int(i2 / (double)N * 100)) + "%";
		}
		i2++;
	}
	SetCursorPosistion(0, 1);
	cout << "Preparing data: 100%";

	// Sort and Analize data
	cout << endl << "Analizing stats: 0%";
	N = students.size();
	for (int i = 0; i < N; i++)
	{
		students[i]->SortStats();
		students[i]->Analize();
		if (i % 100 == 0)
		{
			SetCursorPosistion(17, 2);
			cout << to_string(int((i / (double)N * 100))) + "%";
		}
	}
	SetCursorPosistion(0, 2);
	cout << "Analizing stats: 100%";

	for (int i = 0; i < structure.size(); i++)
		structure[i]->CalculateReturnability();

	cout << endl;
	sort(structure.begin(), structure.end(), CompareStepsRetunability);
	for (int i = 0; i < min(structure.size(), 10); i++)
	{
		cout << structure[i]->id;
		if (i != min(structure.size(), 10) - 1)
			cout << ",";
	}

	// Check if original file used
	cout << endl;
	if (eventsAdress != "D:\\Windows\\Desktop\\course-217-events.csv")
		cout << "-----------WARNING! NOT AN ORIGINAL FILE ADRESS USED!-----------" << endl;

	system("pause");
	return 0;
}