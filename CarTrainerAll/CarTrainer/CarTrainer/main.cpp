
#include <iostream>
#include <windows.h>
#include "ftd2xx.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

#define DISPLAY_WIDTH 1650
#define DISPLAY_HEIGHT 1050

#define START_POS_X 850
#define START_POS_Y 950
#define START_ANGLE 270

b2Vec2 Gravity(0.f, 0.f);
b2World World(Gravity);


#include "SerialClass.h"
#define COM_PORT "COM7"
Serial *comPort;


#include "BoxObject.h"
#include "Car.h"
#include "NeuralCar.h"

/*	SetWall()
x, y - top left corner coordinates
w, h - width and height
*/
void SetWall(int x, int y, int w, int h)
{
	b2PolygonShape gr;
	gr.SetAsBox(w / 2 / SCALE, h / 2 / SCALE);

	b2BodyDef bdef;
	bdef.position.Set((x + w / 2) / SCALE, (y + h / 2) / SCALE);

	b2Body *b_ground = World.CreateBody(&bdef);
	b_ground->CreateFixture(&gr, 1);
}

int main()
{ 
	srand((unsigned int)time(NULL));

	NeuralNetwork *Network = NeuralNetwork::LoadFromFile("myXML.xml");
	if (!Network)
		throw("Cannot load a Network");

	//NeuralNetwork *Network = NeuralNetwork::GetRandomNetwork(7, 2);
	//Network->SaveToFile("myXML.xml");

	std::vector<BoxObject> blocks;

	sf::RenderWindow window(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "Car Trainer", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Texture t1;	
	t1.loadFromFile("Images/block.jpg");

	Image relief;
	assert(relief.loadFromFile("Images/track_map.png"));

	for(int i = 0; i<33; i++)
		for (int j = 0; j < 21; j++)
		{
			if (relief.getPixel(i, j).r < 128)
			{
				blocks.push_back(BoxObject(t1, IntRect(0, 0, 50, 50), "Track border", false));
				blocks[blocks.size() - 1].body->SetTransform(b2Vec2((i * 50 +25) / SCALE, (j * 50 +25) / SCALE), 0);
			}
		}

	Clock clock;
	//////////Box2D//////////////
	

	Texture pTex;
	pTex.loadFromFile("Images/player.jpg");
	NeuralCar *player = new NeuralCar(pTex, IntRect(0, 0, 20, 35), "Player", Network);
	player->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);

	int step = 8;
	bool robotRooling = true;

	comPort = new Serial(COM_PORT);

	// Main cycle
	while (window.isOpen())
	{
		// Handle events
		sf::Event myEvent;
  		while (window.pollEvent(myEvent))
		{
			if (myEvent.type == sf::Event::Closed ||
				(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Escape))
				window.close();	
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::R)
			{
				robotRooling ^= 1;
				//if(!robotRooling)
					player->SetWheelsAngle(((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG);
			}
			if (myEvent.type == sf::Event::JoystickMoved)
				//if(!robotRooling)
					player->SetWheelsAngle( ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG);
			if (myEvent.type == sf::Event::JoystickButtonPressed)
			{
				if (Joystick::isButtonPressed(0, 0))
					step--;
				if (Joystick::isButtonPressed(0, 1))
					step++;
				if (Joystick::isButtonPressed(0, 3))
				{
					robotRooling ^= 1;
					//if (!robotRooling)
						player->SetWheelsAngle(((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG);
				}
			}
			
		}
		// Check contacts before step
		for (b2ContactEdge* contact = player->body->GetContactList(); contact; contact = contact->next)
		{
			if (contact->contact->IsTouching())
			{
				//player->destroyFlag = true;
				if (robotRooling)
				{
					//NeuralNetwork *Network = NeuralNetwork::GetRandomNetwork(7, 2);
					//player->Network = Network;
					//Network->SaveToFile("myXML.xml");
				}

				player->body->SetAngularVelocity(0);
				player->body->SetLinearVelocity(b2Vec2(0,0));
				player->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
			}
		}
		if (player->destroyFlag)
		{
			delete player;
			player = new NeuralCar(pTex, IntRect(0, 0, 20, 35), "Player");
			player->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
		}

		World.Step(1 / 60.f, 8, 3);


		player->DoStep(step);
		if (robotRooling)
			player->WatchEnv(blocks); 

		window.clear(Color::White);
		// Display functions 

		for (int i = 0; i < blocks.size(); i++)
			blocks[i].Draw(window);
		player->Draw(window, robotRooling);

		window.display();
	}

	return 0;
}