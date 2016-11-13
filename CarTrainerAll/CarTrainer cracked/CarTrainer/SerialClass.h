#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

#define ARDUINO_WAIT_TIME 0
#define MAX_READ_DATA 256
#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <windows.h>
#include <string>

class Serial
{
private:
	// ���������� COM-�����
	HANDLE hSerial;
	// ������ ����������
	bool connected;
	// ��������� ���������� � ����������
	COMSTAT status;
	// ��������� ������
	DWORD errors;

public:
	// ������������� � ��������� COM-������
	Serial(char *portName);
	// �������� ����������
	//NOTA: �� �����-�� �������� �� ������ ����������������
	// ����� ������������� ���������
	~Serial();
	// ��������� ������ � ����� � ���� nbChar ������, ���
	// ����� ��������� ���� � ���������� ������ 
	// ��������� ������
	// ���������� -1 ��� ������
	int ReadData(char *buffer, unsigned int nbChar);
	int ReadData(std::string &str);
	// ���������� ������ �� ������ � ����
	// ���������� true ��� �����
	bool WriteData(char *buffer, unsigned int nbChar);
	bool WriteData(std::string str);
	// ���������� ������ ����������
	bool IsConnected();


};

#endif // SERIALCLASS_H_INCLUDED