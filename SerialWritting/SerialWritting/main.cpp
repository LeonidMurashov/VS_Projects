
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "SerialClass.h"
#include <string>

#define COM_PORT "COM1"
#define BUF_SIZE 256

using namespace std;

template <class T>
string to_string(T param)
{
	string str = "";
	stringstream ss;
	ss << param;
	getline(ss, str);
	return str;
}

char* StringToChar2(std::string str)
{
	char *chars = new char[str.length() + 1];
	std::strcpy(chars, str.c_str());
	return chars;
}

int main()
{
	Serial com7(COM_PORT);
	// обнуляем буфер
	char buf[BUF_SIZE];
	for (int i = 0; i<BUF_SIZE; i++)
		buf[i] = '\0';
	
	// считываем и выводим данные из порта
	while (true)
	{
		
			//com7.WriteData(string(to_string(rand()%120) + "\n"));
			string str = (to_string(rand() % 120) + "\n");
			com7.WriteData(str);
			Sleep(0);
			//string str;
			//com7.ReadData(str);
			//cout << str;

		
	}
	system("pause");
	return 0;
}


/*
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

template <class T>
string to_string(T param)
{
	string str = "";
	stringstream ss;
	ss << param;
	getline(ss, str);
	return str;
}

int main()
{
	system("pause");
	system("Mode COM7,9600,n,8,1,P");
	for (int i = 0; i < 120; i++)
	{
		system(string("ECHO " + to_string(i) + " > COM7").c_str());
		Sleep(100);
	}
	system(string("ECHO 0 > COM7").c_str());
	return 0;
}

*/


/*#include "MySerial.h"
#include <assert.h>
using namespace std;

int main()
{	
	setlocale(LC_ALL, "Russian");

	CSerial serial;
	if (serial.Open(7, 9600))
	{
		cout << "Port opened successfully" << endl;

		static char* szMessage = "0";
		int nBytesSent = serial.SendData(szMessage, strlen(szMessage));
		assert(nBytesSent == strlen(szMessage));

		Sleep(1000);

		szMessage = "100";
		nBytesSent = serial.SendData(szMessage, strlen(szMessage));
		assert(nBytesSent == strlen(szMessage));
	}
	else
		cout << "Failed to open port!" << endl;

	system("pause");
	return 0;
}



*/

/*
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string>

char buf[128];
char* pbuf = buf;
int counter = 0;

HANDLE hCom, hEvent;
DWORD bytesRead, bWritten;

BOOL fSuccess;
HANDLE hThread;
DWORD dwParam, dwThreadId;

using namespace std;

char* StringToChar(string str)
{
	char* chars = "";
	for (int i = 0; i < str.length(); i++)
		chars += str[i];
	return chars;
}

template <class T>
string to_string(T param)
{
	string str = "";
	stringstream ss;
	ss << param;
	getline(ss, str);
	return str;
}

VOID WINAPI ThreadProc(PVOID* dummy) 
{
	printf("Ждите данные из порта СОМ7...\n");
	while (true)
	{
		ReadFile(hCom, pbuf, 1, &bytesRead, NULL);
		if (bytesRead>0)
		{
			WriteFile(hCom, pbuf++, 1, &bWritten, NULL);
			counter++;
			if (counter == 10) {
				SetEvent(hEvent);
				buf[counter] = '\0';
				counter = 0;
				pbuf = buf;
			}
		}

		char* myBuf = StringToChar(string(to_string((long long)rand()) + '\n'));
		cout << myBuf;
		WriteFile(hCom, &myBuf, sizeof(myBuf), &bWritten, NULL);

		Sleep(1000);
	}
}

int main(void) {
	setlocale(LC_ALL, "Russian");
	char* pcComPort = "COM7";
	DCB dcb;
	FILE* fout;
	hCom = CreateFile(pcComPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);
	if (hCom == INVALID_HANDLE_VALUE) {
		printf("Ошибка открытия COM7!\n");
		system("pause");
		return 1;
	}
	GetCommState(hCom, &dcb);
	dcb.BaudRate = CBR_9600;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	fSuccess = SetCommState(hCom, &dcb);
	if (!fSuccess) {
		printf("Попытка вызвать SetCommState провалилась!\n");
		system("pause");
		return 1;
	}
	printf("COM порт %s успешно сконфигурирован\n", pcComPort);
	GetCommState(hCom, &dcb);
	printf("Скорость порта %s равна %d\n", pcComPort, dcb.BaudRate);

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,
		&dwParam, 0, &dwThreadId);
	if ((fout = fopen("D:\\test", "a+")) == NULL) {
		printf("Не могу создать файл D:\\test");
		system("pause");
		return 1;
	}
	printf("Нажмите клавишу для выхода...\n");
	do {
		WaitForSingleObject(hEvent, INFINITE);
		printf("%s\n", buf);
		fwrite(buf, sizeof(char), 10, fout);
	} while (true);
	fclose(fout);
	CloseHandle(hCom);
	return 0;
}*/