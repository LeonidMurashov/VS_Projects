#pragma once
#include <windows.h>
#include "ftd2xx.h"
#include <bitset>

class USBUART
{
	FT_HANDLE handle;
	unsigned char port;
	DWORD numBytes;
public:
	USBUART();
	~USBUART();

	bool IsConnected();
	bool WriteData(char byte);
};

