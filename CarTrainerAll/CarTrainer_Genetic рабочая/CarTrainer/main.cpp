
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;
using std::cout;
using std::endl;
using std::vector;

#define DISPLAY_WIDTH 1680
#define DISPLAY_HEIGHT 1050

#define START_POS_X 850
#define START_POS_Y 950
#define START_ANGLE 270

/* uncomment to use with Arduino */
/* comment to use with USB-UART */
//#define ARDUINO

/* uncomment to use joystick for input */
#define IS_READING_JOYSTICK false
#define NEURAL_INPUTS_COUNT 7



b2Vec2 Gravity(0.f, 0.f);
b2World World(Gravity);
Text speedText;

const int Population_Size = 100;

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
#include "MyContactListener.h"
vector<NeuralCar*> cars;
MyContactListner *contactListner = new MyContactListner;

void SetWall(int x, int y, int w, int h);


NeuralNetwork* GenRandomNetwork(int lay_in, int lay_out)
{
	NeuralNetwork *NN = NeuralNetwork::GetRandomNetwork(lay_in, lay_out);

	// Check Random networks for capability
	vector<double> vec;
	for (int i = 0; i < lay_in; i++)
		vec.push_back(randDouble());
	vector<double> res = NN->Run(vec);
	if (res[0] <= 0)
		NN = GenRandomNetwork(lay_in, lay_out);
	return NN;
}

int main()
{
	srand((unsigned int)time(NULL));
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


	//NeuralNetwork *Network = NeuralNetwork::LoadFromFile("myXML.xml");
	//if (!Network)
	//	throw("Cannot load a Network");

	//NeuralNetwork *Network = NeuralNetwork::GetRandomNetwork(NEURAL_INPUTS_COUNT, 2);
	//Network->SaveToFile("myXML.xml");

	std::vector<BoxObject> blocks;

	sf::RenderWindow window(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "Car Trainer", Style::Fullscreen);
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// Loading and creating relief
	Texture t1;
	t1.loadFromFile("Images/block.jpg");

	Image relief;
	assert(relief.loadFromFile(mapAdress));

	int blockSize = DISPLAY_WIDTH / relief.getSize().x,
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

	// Setting up the label
	Font font;//шрифт 
	assert(font.loadFromFile("C:\\Windows\\Fonts\\3575.ttf"));//передаем нашему шрифту файл шрифта
	speedText.setFont(font);
	speedText.setCharacterSize(40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пиксел€х);//сам объект текст (не строка)
	speedText.setColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	speedText.setStyle(sf::Text::Bold || sf::Text::Regular);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	speedText.setPosition(DISPLAY_WIDTH - 180, DISPLAY_HEIGHT - 55);//задаем позицию текста
	speedText.setString("— ќ–ќ—“№");

	// Setting up the NeuralCars
	vector<NeuralNetwork*> Networks;
	for (int i = 0; i < Population_Size; i++)
		Networks.push_back(GenRandomNetwork(NEURAL_INPUTS_COUNT, 1));

	Texture pTex;
	pTex.loadFromFile("Images/player.png");
	for (int i = 0; i < Population_Size; i++)
	{
		cars.push_back(new NeuralCar(pTex, IntRect(0, 0, 20, 35), "NeuralCar", Networks[i]));
		cars[i]->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
	}

	//////////Box2D//////////////	
	World.SetContactListener(contactListner);

	Texture finTex;
	finTex.loadFromFile("Images//finish.jpg");
	BoxObject finish(finTex, IntRect(0, 0, blockSize*5, blockSize), "Finish", false);
	finish.body->SetTransform(b2Vec2((START_POS_X+300) / SCALE, (START_POS_Y-00) / SCALE), START_ANGLE / DEG);
	
	int step = 8;
	bool robotRooling = true;

	Clock clock;

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
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Up)
				step++;
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Down)
				step--;
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::R)
				robotRooling^=1;
		}

		// Check contacts before step
		for (NeuralCar * currCar : cars)
		{
			for (b2ContactEdge* contact = currCar->body->GetContactList(); contact; contact = contact->next)
			{
				if (contact->contact->IsTouching())
				{
					// Save Network in case of it gets to finish
					if (contact->contact->GetFixtureA()->GetBody()->GetUserData() == finish.body->GetUserData() ||
						contact->contact->GetFixtureB()->GetBody()->GetUserData() == finish.body->GetUserData())
					{
						currCar->SaveNetwork("D://gg.txt");

						// Set player at starting position
						currCar->body->SetAngularVelocity(0);
						currCar->body->SetLinearVelocity(b2Vec2(0, 0));
						currCar->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
						currCar->Network = GenRandomNetwork(NEURAL_INPUTS_COUNT, 1);
					}

					// Reload car in case of it crashes the track wall
					if (contact->contact->GetFixtureA()->GetBody()->GetUserData() == blocks[0].body->GetUserData())
					{
						// Set player at starting position
						currCar->body->SetAngularVelocity(0);
						currCar->body->SetLinearVelocity(b2Vec2(0, 0));
						currCar->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);

						currCar->Network = GenRandomNetwork(NEURAL_INPUTS_COUNT, 1);
					}
				}
			}
		}

		// Do World step		
		World.Step(clock.getElapsedTime().asSeconds(), 8, 3);
		clock.restart();
		for (NeuralCar * currCar : cars)
		{
			currCar->DoStep(step);
			//if (robotRooling)
				currCar->WatchEnv(blocks);
		}

		// Display functions
		window.clear(Color::White);
		finish.Draw(window);
		for (size_t i = 0; i < blocks.size(); i++)
			blocks[i].Draw(window);
		for (NeuralCar * currCar : cars)
			currCar->Draw(window, robotRooling);
		window.draw(speedText);
		window.display();
	}

	return 0;
}


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