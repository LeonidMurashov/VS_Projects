#include "windows.h"
#include <iostream>

void ComWrite(char character)
{
	HANDLE hCom = CreateFile(L"Com6", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hCom == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hCom);
		throw("Com port error");
	} //if ( hCom == INVALID_HANDLE_VALUE )
	else
	{
		DCB dcb;
		GetCommState(hCom, &dcb);
		dcb.BaudRate = CBR_9600;
		dcb.fParity = false;
		dcb.ByteSize = 8;
		dcb.Parity = EVENPARITY;
		dcb.StopBits = ONESTOPBIT;
		SetCommState(hCom, &dcb);
		DWORD feedback = 0;
		char buf = character;
		WriteFile(hCom, &buf, sizeof(buf), &feedback, NULL);
		CloseHandle(hCom);
	}
}

void main()
{
	// Do not work
	ComWrite((char)255);
	ComWrite('\n');
}
