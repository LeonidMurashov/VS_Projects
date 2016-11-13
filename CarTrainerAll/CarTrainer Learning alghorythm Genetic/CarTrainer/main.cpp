
/*
*
*	Author: Leonid Murashov 02.09.2016
*
*	Main version of learning alghorythm(genetic)
*	for CarTrainer
*	Genetic algorythm.
*
*/

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
#define START_POS_Y 970
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

const int Population_Size = 200;
bool momentum = false;

#ifdef ARDUINO
#include "SerialClass.h"
#define COM_PORT "COM7"
Serial *device = new Serial(COM_PORT);
#else
#include "USBUART.h"
USBUART device;
#endif


#include "NeuralNetwork2.h"
#include "GeneticEngine.h"
#include "BoxObject.h"
#include "Car.h"
#include "NeuralCar.h"
#include "MyContactListener.h"
vector<NeuralCar*> cars;
MyContactListner *contactListner = new MyContactListner;


void SetWall(int x, int y, int w, int h);

// Instructions for NNs
vector<int> layerSizes = { NEURAL_INPUTS_COUNT, 1 };
vector<TransferFunction> transferFunctions = { TransferFunction::None,
												TransferFunction::Linear };

NeuralNetwork* GenRandomNetwork()
{
	NeuralNetwork *NN = new NeuralNetwork(layerSizes, transferFunctions);

	// Check Random networks for capability
	vector<double> vec;
	for (int i = 0; i < NEURAL_INPUTS_COUNT; i++)
		vec.push_back(randDouble());
	vector<double> res = NN->Run(vec);
	if (res[0] <= 0 || res[0] > 180)
		NN = GenRandomNetwork();
	return NN;
}


int main()
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "rus");
	std::string mapAdress;

	// Getting map number
mapin:
	int mapNumber = 0;
	std::cout << "Введите номер карты: ";
	//std::cin >> mapNumber;
	mapNumber = 1;
	if (mapNumber == 1)
		mapAdress = "Images/track_map1.png";
	else if (mapNumber == 0)
		mapAdress = "Images/track_map0.png";
	else
		goto mapin;

	std::vector<BoxObject> blocks;

	sf::RenderWindow window(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "Car Trainer");// , Style::Fullscreen);
	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);

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

	// Setting up the speed label
	Vector2f slPos(DISPLAY_WIDTH - 280, DISPLAY_HEIGHT - 95);
	Font font;
	assert(font.loadFromFile("C:\\Windows\\Fonts\\3575.ttf"));
	speedText.setFont(font);
	speedText.setCharacterSize(40);
	speedText.setColor(Color::Black);
	speedText.setStyle(sf::Text::Bold || sf::Text::Regular);
	speedText.setPosition(slPos);
	speedText.setString("СКОРОСТЬ");
	// Creating background for label
	Texture t;
	IntRect tRect(slPos.x, slPos.y, 270, 80);
	Sprite speedTextBG;
	t.setRepeated(true);
	speedTextBG.setTexture(t);
	speedTextBG.setTextureRect(tRect);
	speedTextBG.setPosition(slPos);
	speedTextBG.setColor(Color(255, 255, 255, 200));

	// Setting up finish label
	Vector2f suclPos(5, 5);
	Text successLabel("Финиш достигнут", font, 40);
	successLabel.setColor(Color::Black);
	successLabel.setStyle(sf::Text::Bold || sf::Text::Regular);
	successLabel.setPosition(suclPos);
	// Creating background for label
	IntRect t2Rect(suclPos.x, suclPos.y, 590, 80);
	Sprite successTextBG;
	successTextBG.setTexture(t);
	successTextBG.setTextureRect(t2Rect);
	successTextBG.setPosition(suclPos);
	successTextBG.setColor(Color(255, 255, 255, 200));
	
	
	// Setting up the NeuralCars
	vector<NeuralNetwork*> Networks;
	for (int i = 0; i < Population_Size; i++)
		Networks.push_back(GenRandomNetwork());

	Texture pTex;
	pTex.setSmooth(true);
	pTex.loadFromFile("Images/player.png");
	for (int i = 0; i < Population_Size; i++)
	{
		cars.push_back(new NeuralCar(pTex, IntRect(0, 0, 20, 35), "NeuralCar", Networks[i]));
		cars[i]->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
	}

	// Background 
	Texture bgTex;
	bgTex.loadFromFile("Images//fon.jpg");
	Sprite bg;
	bg.setTexture(bgTex);

	//////////Box2D//////////////	
	World.SetContactListener(contactListner);

	Texture finTex;
	finTex.loadFromFile("Images//finish.jpg");
	BoxObject finish(finTex, IntRect(0, 0, blockSize*4.5, blockSize), "Finish", false);
	finish.body->SetTransform(b2Vec2((START_POS_X+300) / SCALE, (START_POS_Y-45) / SCALE), START_ANGLE / DEG);
	
	// Car speed is step*10
	int step = 10;
	bool robotRooling = false;

	Clock clock, mainClock, genClock;
	
	bool showSuccess = false;
	long long carsCount = 0;
	
	// For GeneticAlg
	int carsCrashed = 0, generation = 1;
	GeneticEngine geneticEngine;

	// Main cycle
	while (window.isOpen())
	{
		if (carsCount % 1000 == 0)
			srand((unsigned int)std::clock()*time(NULL));
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
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::M)
			{
				// Switching on/off the momentum of wheels
				momentum ^= 1;
			}
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Delete)
			{
				for (NeuralCar* currCar : cars)
				{
					// Reload car
					if (!currCar->IsStop())
					{
						// Set player at starting position
						currCar->body->SetAngularVelocity(0);
						currCar->body->SetLinearVelocity(b2Vec2(0, 0));
						currCar->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
						carsCount++;
						carsCrashed++;
						currCar->time = genClock.getElapsedTime();
						currCar->Stop();
					}
				}
			}
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
						currCar->SaveNetwork("D://myXML.xml");

						// Stop cars in case of the first car finished
						if (!showSuccess)
						{
							showSuccess = true;
							successLabel.setString("Финиш достигнут на " + std::to_string((int)ceil(mainClock.getElapsedTime().asSeconds()/(double)60)) + " минуте\nСпустя " + std::to_string(carsCount) + " попыток");
							step = 0;
						}
						// Reload finished car
						else
						{
							if (step)
							{
								// Set player at starting position
								currCar->body->SetAngularVelocity(0);
								currCar->body->SetLinearVelocity(b2Vec2(0, 0));
								currCar->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
							}
						}
					}

					// Reload car in case of it crashes the track wall
					if (contact->contact->GetFixtureA()->GetBody()->GetUserData() == blocks[0].body->GetUserData() &&
						!currCar->IsStop())
					{
						// Set player at starting position
						currCar->body->SetAngularVelocity(0);
						currCar->body->SetLinearVelocity(b2Vec2(0, 0));
						currCar->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
						carsCount++;
						carsCrashed++;
						currCar->time = genClock.getElapsedTime();
						currCar->Stop();
					}
				}
			}
		}
		
		// Check generation is ready
		if (carsCrashed == Population_Size)
		{
			// Send Networks and fitnesses to algorythm
			vector<NeuralNetwork*> creatures;
			vector<double> fitnesses;
			for (NeuralCar * currCar : cars)
			{
				creatures.push_back(currCar->Network);
				fitnesses.push_back(currCar->time.asMilliseconds());
			}

			// Get Networks from algorythm and attach them to cars
			creatures = geneticEngine.GeneticCircle(creatures, fitnesses, false);//!(generation % 20),);
			assert(creatures.size() == Population_Size);
			for (int i = 0; i<Population_Size; i++)
			{
				cars[i]->Network = creatures[i];
				cars[i]->Run();
			}
			carsCrashed = 0;
			generation++;
			cout << generation << endl;
		}
		
		// Do World step
		double timeElapsed = clock.getElapsedTime().asSeconds();
		World.Step(timeElapsed, 8, 3);
		clock.restart();

		for (NeuralCar * currCar : cars)
		{
			currCar->DoStep(step, timeElapsed, blocks);
			currCar->WatchEnv(blocks);
		}
		
		if(!momentum)
			speedText.setString("momentum off\n		 " + std::to_string((int)step * 10) + "КМ/Ч");
		else
			speedText.setString("\n		 " + std::to_string((int)step * 10) + "КМ/Ч");

		// Display functions
		window.clear(Color::White);
		window.draw(bg);
		finish.Draw(window);
		for (size_t i = 0; i < blocks.size(); i++)
			blocks[i].Draw(window);
		for (NeuralCar * currCar : cars)
			currCar->Draw(window, robotRooling);
		window.draw(speedTextBG);
		window.draw(speedText);
		if (showSuccess)
		{
			window.draw(successTextBG);
			window.draw(successLabel);
		}
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