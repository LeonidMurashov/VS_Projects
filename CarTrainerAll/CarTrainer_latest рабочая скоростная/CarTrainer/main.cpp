
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;

#define DISPLAY_WIDTH 1680
#define DISPLAY_HEIGHT 1050

#define START_POS_X 850
#define START_POS_Y 950
#define START_ANGLE 270

/* uncomment to turn training on */
//#define GENERATE_NETWORKS

/* uncomment to use with Arduino */
/* comment to use with USB-UART */
//#define ARDUINO

b2Vec2 Gravity(0.f, 0.f);
b2World World(Gravity);
Text speedText;

#ifdef ARDUINO
#include "SerialClass.h"
#define COM_PORT "COM7"
Serial *device = new Serial(COM_PORT);
#else
#include "USBUART.h"
USBUART device;
#endif

#include "NeuralNetwork2.h"
#include "BoxObject.h"
#include "Car.h"
#include "NeuralCar.h"

//	SetWall()
//x, y - top left corner coordinates
//w, h - width and height

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
	setlocale(LC_CTYPE, "rus");
	std::string mapAdress;

	// Getting map number
	mapin:
	int mapNumber = 0;
	std::cout << "¬ведите номер карты: ";
	//std::cin >> mapNumber;
	mapNumber = 1;
	if (mapNumber == 1)
		mapAdress = "Images/track_map1.png";
	else if (mapNumber == 0)
		mapAdress = "Images/track_map0.png";
	else
		goto mapin;

	srand((unsigned int)time(NULL));

	NeuralNetwork *Network = NeuralNetwork::LoadFromFile("myXML.xml");
	if (!Network)
		throw("Cannot load a Network");

	//NeuralNetwork *Network = NeuralNetwork::GetRandomNetwork(7, 2);
	//Network->SaveToFile("myXML.xml");

	std::vector<BoxObject> blocks;

	sf::RenderWindow window(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "Car Trainer", Style::Fullscreen);
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Texture t1;	
	t1.loadFromFile("Images/block.jpg");

	Image relief;
	assert(relief.loadFromFile(mapAdress));

	int blockSize = DISPLAY_WIDTH/relief.getSize().x,
		width = relief.getSize().x,
		height = relief.getSize().y;

	for (int i = 0; i<width; i++)
		for (int j = 0; j < height; j++)
		{
			if (relief.getPixel(i, j).r < 128)
			{
				blocks.push_back(BoxObject(t1, IntRect(0, 0, blockSize, blockSize), "Track border", false));
				blocks[blocks.size() - 1].body->SetTransform(b2Vec2(((i + 0.6) * blockSize) / SCALE, ((j + 0.6) * blockSize) / SCALE), 0);
			}
		}
	/*
	for(int i = 0; i<DISPLAY_WIDTH/50; i++)
		for (int j = 0; j < DISPLAY_HEIGHT/50; j++)
		{
			if (relief.getPixel(i, j).r < 128)
			{
				blocks.push_back(BoxObject(t1, IntRect(0, 0, 50, 50), "Track border", false));
				blocks[blocks.size() - 1].body->SetTransform(b2Vec2((i * 50 +37) / SCALE, (j * 50 +37) / SCALE), 0);
			}
		}
	*/
	Font font;//шрифт 
	assert(font.loadFromFile("C:\\Windows\\Fonts\\3575.ttf"));//передаем нашему шрифту файл шрифта
	speedText.setFont(font);
	speedText.setCharacterSize(40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пиксел€х);//сам объект текст (не строка)
	speedText.setColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	speedText.setStyle(sf::Text::Bold || sf::Text::Regular);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	speedText.setPosition(DISPLAY_WIDTH - 180, DISPLAY_HEIGHT - 55);//задаем позицию текста
	speedText.setString("— ќ–ќ—“№");


	//////////Box2D//////////////	

	Texture pTex;
	pTex.loadFromFile("Images/player.jpg");
	NeuralCar *player = new NeuralCar(pTex, IntRect(0, 0, 20, 35), "Player", Network);
	player->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);

	int step = 8;
	bool robotRooling = true;
	
	Clock clock;
	int it2 = 0;

	// Main cycle
	while (window.isOpen())
	{
		it2++;
		if (clock.getElapsedTime().asSeconds() > 1)
		{
			std::cout << it2 << std::endl;
			clock.restart();
			it2 = 0;
		}
			
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
				// Letdown the wheel(stop byte)
				if (!robotRooling)
					device.WriteData(255);
				player->SetWheelsAngle(((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG);				
			}
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Up)
				step++;
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Down)
				step--;
			if (myEvent.type == sf::Event::JoystickMoved)
				//if(!robotRooling)
				;// player->SetWheelsAngle(((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG);
			if (myEvent.type == sf::Event::JoystickButtonPressed)
			{
				if (Joystick::isButtonPressed(0, 0))
					step--;
				if (Joystick::isButtonPressed(0, 1))
					step++;
				if (Joystick::isButtonPressed(0, 3))
				{
					robotRooling ^= 1;
					// Letdown the wheel(stop byte)
					if (!robotRooling)
						device.WriteData(255);
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
				#ifdef GENERATE_NETWORKS
				if (robotRooling)
				{
					NeuralNetwork *Network = NeuralNetwork::GetRandomNetwork(7, 2);
					player->Network = Network;
					Network->SaveToFile("myXML.xml");
				}
				#endif

				player->body->SetAngularVelocity(0);
				player->body->SetLinearVelocity(b2Vec2(0,0));
				player->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);

				if (robotRooling)
				{
					device.WriteData(60);
					//Sleep(500);
				}
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

		window.draw(speedText);
		window.display();
	}
	
	return 0;
}