#include<iostream> 
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
using namespace std;

vector<int> a = { 1, 4, 6 , 4, 2};
int main() 
{
	for (auto b : a)
		if (b == 2)
			cout << "yes";
	return 0;
}

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