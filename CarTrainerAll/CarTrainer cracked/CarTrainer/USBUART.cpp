#include "USBUART.h"

//using std::cout;

USBUART::USBUART()
{
	FT_Open(0, &handle);
	FT_SetBitMode(handle, (1023), 0x04);
}

USBUART::~USBUART()
{
	// Stop byte
	this->WriteData(255);
	FT_Close(handle);
}

bool USBUART::IsConnected()
{	
	return true;
}

bool USBUART::WriteData(char byte)
{
	//Open and setup Handle every call
	//if () != FT_OK) return false;
	//else
	{

		std::bitset<8> bits(byte);
		std::bitset<8> bits2;
		bits2[3] = bits[0];
		bits2[6] = bits[1];
		bits2[5] = bits[2];
		bits2[7] = bits[3];
		bits2[1] = bits[4];// у FT непоследовательная распиновка
		bits2[2] = bits[5];
		bits2[4] = bits[6];
		bits2[0] = bits[7];


		int data = bits2.to_ulong();//bits.to_ulong();

		FT_Write(handle, &data, 1, &numBytes);

	}

	return true;
}
