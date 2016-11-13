//Построение с VS2010 
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
using namespace sf;
using namespace std;
int main()
{
	cout << "Loading..."<<endl<<endl;
	RenderWindow window(VideoMode(800, 600), "MyMinecraft");
	
		Texture tex;
		tex.loadFromFile("D:\\VS_projects\\Minecraftcraft\\sprite.jpg");
		Sprite background(tex);

		while (window.isOpen())
		{

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();

				if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
					window.close();

				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Right);// mRight = 1;
					if (event.key.code == Mouse::Left);//  mLeft = 1;
				}
			}
			window.draw(background);

			window.display();
		}
		cout << endl << "Finished.";

}