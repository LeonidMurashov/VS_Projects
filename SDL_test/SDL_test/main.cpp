#include <iostream>
#include <SDL.h>
using namespace std;

//#define NDEBUG	///Uncomment on production
#include <assert.h>

int main(int argc, char** argv)
{
	// ���������� ��� ������ ���������
	SDL_Joystick *joy;
	SDL_Event event;

	// ������������� SDL ��� ������������� ���������
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
		throw("Can not initialize SDL!");
	
	// ��������
	assert(SDL_JoystickEventState(SDL_ENABLE));
	// ��������� ;)
	joy = SDL_JoystickOpen(0);

	while (1)
	{
		// �������������� ��������

		SDL_PollEvent(&event);

		// �������� ��������, ��������������� �������� ���������
		// �� ��� �
		int xAxis = SDL_JoystickGetAxis(joy, 0);

		int btn1 = SDL_JoystickGetButton(joy, 0);
		int btn2 = SDL_JoystickGetButton(joy, 1);
		int btn3 = SDL_JoystickGetButton(joy, 2);
		int btn4 = SDL_JoystickGetButton(joy, 3);
		// �������
		cout << xAxis << " " << btn1 << " " << btn2 << " " << btn3 << " " << btn4 << endl;
	}
	return 0;
}
