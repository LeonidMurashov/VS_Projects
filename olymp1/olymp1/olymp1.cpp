// olymp.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int a,b;
	cin>>a>>b;
	b--;
	b%=a;
	b++;
	cout <<b;
	return 0;
}

