 
#include <iostream> 
#include <vector>
#include <queue>
using namespace std;
int main(int argc, char *argv[])
{
	vector<vector<int>> map;
	vector<bool> levels;
	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; i++)
	{
		int K;
		cin >> K;
		vector<int> level;
		for (int j = 0; j < K; j++)
		{
			int m;
			cin >> m;
			level.push_back(m);
		}
		map.push_back(level);
		levels.push_back(false);
	}

	queue<int> q;
	int level = 0;
	vector<int> last;
	q.push(k);

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();
		if (map[curr - 1].empty())
			continue;
		last.clear();
		for (int e : map[curr-1])
			if (!levels[e-1])
			{
				last.push_back(e);
				q.push(e);
			}
		levels[curr-1] = true;
		level++;
	}

	cout << level << endl;
	for (int e : last)
	{
		cout << e << " ";
	}

}

/*#include<windows.h>
#include<iostream>
#include <string>
#include <comutil.h>
#pragma comment(lib, "comsuppw" ) // link with comsuppw.lib

int main() {
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile(L"d:\\*", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			_bstr_t b(FindFileData.cFileName);
			const char* c = b;
			std::cout << c << "\n";
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}*/
/*#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	char ch;
	int i;
	float f;
	char str[80];
	ifstream in("test");
	if (!in) {
		cout << "Cannot open file.\n";
		return 1;
	}
	ifstream fin("D://Python//Genetic_Plotter//main.py");
	string str;
	fin >> str;
	in >> i;
	in >> f;
	in >> ch;
	in >> str;
	cout << i << " " << f << " " << ch << "\n";
	cout << str;
	in.сlоse();
	return 0;
}*/

/*#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

	LPWSTR command = L"C://Users//User//Anaconda3//python.exe";// D://Python//Genetic_Plotter//main.py";
	LPCWSTR pythonPath = L"C://Program Files (x86)//Python35-32//python.exe";
	LPWSTR geneticPlotterAdress = L"D://Python//Genetic_Plotter//main.py";
	PROCESS_INFORMATION pi;

	LPWSTR cmd = L"notepad";

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	if (CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
	
	TCHAR czCommandLine[] = L"Notepad";
	CreateProcess(NULL, command, NULL, NULL, false, NULL, NULL, NULL, new STARTUPINFO(), &pi);
	
	//CreateProcess(pythonPath, geneticPlotterAdress, NULL, NULL, false, NULL, NULL, NULL, new STARTUPINFO(), &pi);
	//WaitForSingleObject(pi.hProcess, (100));

	// Terminate GeneticPlotter.exe
	//TerminateProcess(pi.hProcess, NO_ERROR);

	return 0;
}*/
/*
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}*/
/*
int main() 
{

	LPCWSTR geneticPlotterAdress = L"C://Users//User//Anaconda3//python.exe";
	PROCESS_INFORMATION pi; 

		// Run GeneticPlotter.exe
	string myString = string("D://Python//Genetic_Plotter//main.py");// to_string(graphResolution.X) + " " + to_string(graphResolution.Y));// +" \"" + (string)logfileName + "\" \"" + (string)graphFile + "\"");
	CreateProcess(geneticPlotterAdress, (LPWSTR)(std::wstring(s2ws(myString))).c_str(), NULL, NULL, false, NULL, NULL, NULL, new STARTUPINFO(), &pi);
	WaitForSingleObject(pi.hProcess, (999));

	// Terminate GeneticPlotter.exe
	TerminateProcess(pi.hProcess, NO_ERROR);
	string command("python D://Python//Genetic_Plotter//main.py");

	FILE* in = popen(command.c_str(), "r");
	pclose(in);

	return 0;
}*/

/*#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void SetCursorPosistion(int x, int y)
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(hOut, Position);
}

int main()
{
	SetCursorPosistion(3, 3);
	cout << "hello";
	return 0;
}*/

/*
#include <iostream>
#include <bitset>

using namespace std;

// Convert unsigned long long to String
string ULL2STR(unsigned long long ull)
{
	string s1, s2, s3;
	unsigned long long a = ull;
	s3 = to_string((unsigned int)a % (unsigned int)10000);
	a /= (unsigned int)10000;
	s2 = to_string((unsigned int)a % (unsigned int)10000);
	a /= (unsigned int)10000;
	s1 = to_string((unsigned int)a % (unsigned int)10000);
	if (s1 == "0")
	{
		s1 = "";
		if (s2 == "0")
			s2 = "";
	}
	return s1 + " " + s2 + " " + s3;
}

void main()
{
	cout << ULL2STR(1000000) << endl;

	system("pause");


	*/


	//главная функция потока, выполняет передачу байтов из буфера в COM-порт


/*
	// Initialization of NeuralNetwork	
	vector<int> layerSizes{ 200007, 6000, 24 };
	vector<NeuralNetworkLibrary2::TransferFunction> transforms{ NeuralNetworkLibrary2::TransferFunction::None,
																NeuralNetworkLibrary2::TransferFunction::Sigmoid,
																NeuralNetworkLibrary2::TransferFunction::Linear };
	NeuralNetworkLibrary2::NeuralNetwork *Network = new NeuralNetworkLibrary2::NeuralNetwork(layerSizes, transforms);
	*/

//}
//	STARTUPINFO cif;
//	ZeroMemory(&cif, sizeof(STARTUPINFO));
//	PROCESS_INFORMATION pi;

	//CreateProcess(L"D:\\QT_projects\\GeneticPlotter\\build-GeneticPlotter-Desktop_Qt_5_6_0_MSVC2015_64bit-Release\\release\\GeneticPlotter.exe", NULL, NULL, NULL, false, NULL, NULL, NULL, &STARTUPINFO(), &PROCESS_INFORMATION());

	/*LPCWSTR str1 = L"D:\\QT_projects\\GeneticPlotter\\build-GeneticPlotter-Desktop_Qt_5_6_0_MSVC2015_64bit-Release\\release\\GeneticPlotter.exe";
	LPCWSTR str2 = L"c:\\windows\\notepad.exe";
	CreateProcess(L"D:\\QT_projects\\GeneticPlotter\\build-GeneticPlotter-Desktop_Qt_5_6_0_MSVC2015_64bit-Release\\release\\GeneticPlotter.exe"; , NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &STARTUPINFO(), &PROCESS_INFORMATION());
	Sleep(3000);*/
	/*if (CreateProcess(str1, NULL,
		NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi) == TRUE)
	{
		cout << "process" << endl;
		cout << "handle " << pi.hProcess << endl;
						// подождать
		TerminateProcess(pi.hProcess, NO_ERROR);	// убрать процесс
	}*/
//}




/*#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;
int main()
{
	/*WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(L"D:\\delme\\logs\\logfile.txt", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Invalid File Handle. Get Last Error reports %d\n", GetLastError());
	}
	else
	{
		FILETIME ft = FindFileData.ftLastWriteTime;
		SYSTEMTIME st;
		GetSystemTime(&st);
		cout << "Actual: " << st.wMilliseconds << endl;
		FileTimeToSystemTime(&ft, &st);
		cout << "Data: " << st.wMilliseconds << endl;

		//что то делаешь путевое
		FindClose(hFind);
	}

	Sleep(15000);

	hFind = FindFirstFile(L"D:\\delme\\logs\\logfile.txt", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Invalid File Handle. Get Last Error reports %d\n", GetLastError());
	}
	else
	{
		FILETIME ft = FindFileData.ftLastWriteTime;
		SYSTEMTIME st;
		GetSystemTime(&st);
		cout << "Actual: " << st.wMilliseconds << endl;
		FileTimeToSystemTime(&ft, &st);
		cout << "Data: " << st.wMilliseconds << endl;

		//что то делаешь путевое
		FindClose(hFind);
	}
	LPCWSTR exe = L"D:\QT_projects\GeneticPlotter\build-GeneticPlotter-Desktop_Qt_5_6_0_MSVC2015_64bit-Release\release\GeneticPlotter.exe";
	
	ShellExecute(NULL, L"open", exe, NULL, NULL, 0);

	return 0;
}*/