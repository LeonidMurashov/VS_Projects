#include <iostream>
#include <SDL.h>
using namespace std;

//#define NDEBUG	///Uncomment on production
#include <assert.h>

int main(int argc, char** argv)
{
	// Переменная для нашего джойстика
	SDL_Joystick *joy;
	SDL_Event event;

	// Инициализация SDL для использования джойстика
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
		throw("Can not initialize SDL!");
	
	// Включаем
	assert(SDL_JoystickEventState(SDL_ENABLE));
	// Открываем ;)
	joy = SDL_JoystickOpen(0);

	while (1)
	{
		// Примитивнейшая задержка

		SDL_PollEvent(&event);

		// Получаем значения, соответствующие смещению джойстика
		// по оси Х
		int xAxis = SDL_JoystickGetAxis(joy, 0);

		int btn1 = SDL_JoystickGetButton(joy, 0);
		int btn2 = SDL_JoystickGetButton(joy, 1);
		int btn3 = SDL_JoystickGetButton(joy, 2);
		int btn4 = SDL_JoystickGetButton(joy, 3);
		// Выводим
		cout << xAxis << " " << btn1 << " " << btn2 << " " << btn3 << " " << btn4 << endl;
	}
	return 0;
}
