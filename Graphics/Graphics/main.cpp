#include <SFML/Graphics.hpp>

using namespace sf;

#define DISPLAY_WIDTH 1650
#define DISPLAY_HEIGHT 1050
int WinMain()
{
	RenderWindow window(sf::VideoMode(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2), "3D Engine");// , Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	Image img;
	img.create(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, Color::White);
	img.setPixel(5, 10, Color::Black);

	while (window.isOpen())
	{
		// Handle events
		sf::Event myEvent;
		while (window.pollEvent(myEvent))
		{
			if (myEvent.type == sf::Event::Closed ||
				(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Escape))
				window.close();
		}

		Texture txt;
		txt.loadFromImage(img);

		Sprite sprite;
		sprite.setPosition(0, 0);
		sprite.setTexture(txt);

		window.clear(Color::White);
		// Display functions 
		window.draw(sprite);
		window.display();
	}
	return 0;
}