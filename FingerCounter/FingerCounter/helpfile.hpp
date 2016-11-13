//для скриншота
#include <windows.h> 
#include <stdio.h>
#include <gdiplus.h> 
#pragma comment(lib, "GdiPlus.lib") 


int rectx = 0, recty = 0, rectw = 0, recth = 0, state = 0, mouserectx = 0, mouserecty = 0; // for mouse Callback
bool addToCascade = false;


/**/
namespace Gdiplus
{
	static const GUID png =
	{ 0x557cf406, 0x1a04, 0x11d3,{ 0x9a, 0x73, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e } };



	void takescreenshot() // кладёт в файл (OpenCV считывает из файла, но не здесь)
	{
		//скриншот

		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = GetDC(0);
		int Height, Width;
		Height = GetSystemMetrics(SM_CYSCREEN);
		Width = GetSystemMetrics(SM_CXSCREEN);
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);
		HBITMAP hBitmap;
		hBitmap = (HBITMAP)SelectObject(memdc, membit);
		Gdiplus::Bitmap bitmap(hBitmap, NULL);
		bitmap.Save(L"D:\\VS_projects\\FingerCounter\\x64\\Debug\\screen.png", &png);
		DeleteObject(hBitmap);


	}
}


void onMouse(int event, int x, int y, int, void*)
{
	if (event == 1)//mousedown
	{
		rectx = x;
		recty = y;
		rectw = 0;
		recth = 0;
		state = 1;
	}
	if (event == 4)//mouseup
	{
		if (x > rectx) rectw = x - rectx;
		else { rectw = rectx - x; rectx = x; }
		if (y > recty) recth = y - recty;
		else { recth = recty - y; recty = y; }
		if (state == 1) addToCascade = true;
		state = 0;
	}
	if (event == 0)//mousemove
	{
		if (state == 1)
		{
			mouserectx = x;
			mouserecty = y;
			state = 2;
		}
		rectw = x - mouserectx;
		recth = y - mouserecty;
	}
}

