#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "Field.h"


#define LINE_SIZE 9


int DISPLAY_WIDTH = 900;
int  DISPLAY_HEIGHT = 900;
int GAME_DEMENTION = 700;
int BLOCK_DEMENTION = GAME_DEMENTION / LINE_SIZE;

using namespace std;
using namespace sf;

void MouseClick()
{
	INPUT inp[2];
	memset(inp, 0, sizeof(inp));
	inp[0].type = INPUT_MOUSE;
	inp[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	inp[1].type = INPUT_MOUSE;
	inp[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(2, inp, sizeof(INPUT));
}

int main()
{	
	sf::RenderWindow window(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "Car Trainer");
	DISPLAY_WIDTH = window.getSize().x;
	DISPLAY_HEIGHT = window.getSize().y;
	GAME_DEMENTION = DISPLAY_WIDTH - 200;
	BLOCK_DEMENTION = GAME_DEMENTION / LINE_SIZE;

	Texture btex;
	btex.loadFromFile("Images//background.png");
	Sprite background(btex);

	Field *field = new Field(string("Images//block.png"), LINE_SIZE, BLOCK_DEMENTION, GAME_DEMENTION, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	bool fieldDefined = false;
	Vector2i p1, p2;
	int mousePressed = 0;

	while (true)
	{
		sf::Event myEvent;
		while (window.pollEvent(myEvent))
		{
			if (myEvent.type == sf::Event::Closed ||
				(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Escape))
			{
				window.close();
				return 0;
			}
			if (sf::Mouse::Button::Left == myEvent.mouseButton.button)
			{
				if (!fieldDefined)
				{
					if (mousePressed == 1)
					{
						p1 = sf::Mouse::getPosition();
						cout << "1" << endl;
					}
					else if(mousePressed == 2)
					{
						
						p2 = sf::Mouse::getPosition();
						if (p2 == p1)
						{
							mousePressed--;
						}
						else 
						{
							fieldDefined = true;
							cout << "2" << endl;
						}
					}
					mousePressed++;
				}
			}

			if (fieldDefined)
			{
				//sf::Mouse::setPosition((p2 + p1)/2);
				SetCursorPos(((p2 + p1) / 2).x, ((p2 + p1) / 2).y);
				MouseClick();
			}


			if (window.getSize().x != window.getSize().y)
				window.setSize(Vector2u(window.getSize().x, window.getSize().x));

			DISPLAY_WIDTH = window.getSize().x;
			DISPLAY_HEIGHT = window.getSize().y;
			GAME_DEMENTION = DISPLAY_WIDTH - 100;
			BLOCK_DEMENTION = GAME_DEMENTION / LINE_SIZE;

			/**/
			field->Place(string("Images//block.png"), LINE_SIZE, BLOCK_DEMENTION, GAME_DEMENTION, DISPLAY_WIDTH, DISPLAY_HEIGHT);

			window.clear(Color::White);
			window.draw(background);
			field->Draw(window);
			window.display();
		}
	}
	return 0;
}