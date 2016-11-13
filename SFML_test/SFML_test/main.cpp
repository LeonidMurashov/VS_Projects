
#include <SFML/Graphics.hpp>

int WinMain()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong!");
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;
	float time;

	while (window.isOpen())
	{
		// Handle events
		sf::Event myEvent;
		while (window.pollEvent(myEvent))
		{
			if (myEvent.type == sf::Event::Closed ||
			   (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Escape))
				window.close();
			//if (myEvent.type == sf::Event::JoystickMoved)
			//	std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
		}

		window.clear();
		// Display-functions 

		time = clock.getElapsedTime().asMilliseconds();
		clock.restart();



		window.display();
	}

	return 0;
}