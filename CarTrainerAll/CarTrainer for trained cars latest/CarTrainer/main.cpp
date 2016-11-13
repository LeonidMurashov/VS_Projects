
/* 
*
*	Author: Leonid Murashov 02.09.2016
*
*	Main workplace(CarTrainer) for cars trained 
*	in learning alghorythm for CarTrainer
*
*	Use buttons R, H, Del, Escape and arrows
*
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;
using std::cout;
using std::endl;

#define DISPLAY_WIDTH 1680
#define DISPLAY_HEIGHT 1050

#define START_POS_X 850
#define START_POS_Y 940
#define START_ANGLE 270

/* uncomment to use with Arduino */
/* comment to use with USB-UART */
//#define ARDUINO

int WHEEL_ANGLE_BIAS;
#define NEURAL_INPUTS_COUNT 7

#include "MyContactListener.h"


b2Vec2 Gravity(0.f, 0.f);
b2World World(Gravity);
Text speedText;
MyContactListner *contactListner = new MyContactListner;
bool IS_READING_JOYSTICK = true;
bool momentum = true;

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

void Set_WHEEL_ANGLE_BIAS()
{
	//Set WHEEL_ANGLE_BIAS by wheel turning and checking
	if (device.IsConnected())
	{
		device.WriteData(90);
		Sleep(300);
		WHEEL_ANGLE_BIAS = 90 - ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200);
		//cout << ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) << endl << endl << endl;

		device.WriteData(90 + WHEEL_ANGLE_BIAS);
		Sleep(300);

		// Letdown the wheel(stop byte)
		device.WriteData(255);

		cout << "WHEEL_ANGLE_BIAS: " << WHEEL_ANGLE_BIAS << endl;
	}
}

int main()
{
	srand((unsigned int)time(NULL));
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


	NeuralNetwork *Network = NeuralNetwork::LoadFromFile("myXML.xml");
	if (!Network)
		throw("Cannot load a Network");

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

	int blockSize = DISPLAY_WIDTH/relief.getSize().x,
		width = relief.getSize().x,
		height = relief.getSize().y;

	for (int i = 0; i<width; i++)
		for (int j = 0; j < height; j++)
		{
			if (relief.getPixel(i, j).r < 128)
			{
				blocks.push_back(BoxObject(t1, IntRect(0, 0, blockSize, blockSize), "Track border", false));
				blocks[blocks.size() - 1].body->SetTransform(b2Vec2(((i + 0.6) * blockSize) / SCALE, ((j + 0) * blockSize) / SCALE), 0);
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

	// Setting up the init label
	Text initText;
	initText.setFont(font);
	initText.setCharacterSize(60);
	initText.setColor(Color::Black);
	initText.setStyle(sf::Text::Bold || sf::Text::Regular);
	initText.setString("Инициализация руля...");
	Vector2f ilPos(DISPLAY_WIDTH / 2 - 300, DISPLAY_HEIGHT / 2 - 30);
	initText.setPosition(ilPos);

	// Background 
	Texture bgTex;
	bgTex.loadFromFile("Images//fon.jpg");
	Sprite bg;
	bg.setTexture(bgTex);

	//////////Box2D//////////////	
	World.SetContactListener(contactListner);

	Texture pTex;
	pTex.setSmooth(true);
	pTex.loadFromFile("Images/player.png");
	NeuralCar *player = new NeuralCar(pTex, IntRect(0, 0, 20, 35), "Player", Network);
	player->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);

	int step = 0;
	bool robotRooling = true;
	bool isWheelBiasSet = false;


	window.clear(Color::White);
	window.draw(bg);
	window.draw(initText);
	window.display();

	if (device.IsConnected())
	{
		device.WriteData(30);
		Sleep(500);
		device.WriteData(150);
		Sleep(300);
		device.WriteData(90);
	}
	
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
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::R)
			{
				robotRooling ^= 1;
				// Letdown the wheel(stop byte)
				if (!robotRooling)
				{
					IS_READING_JOYSTICK = true;
					device.WriteData(255);
				}
				else
					IS_READING_JOYSTICK = false;
				if(IS_READING_JOYSTICK)
					player->SetWheelsAngle(((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG);				
			}
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::H)
			{
				IS_READING_JOYSTICK ^= 1;
				if (!robotRooling)
					IS_READING_JOYSTICK = true;
				robotRooling = true;
				// Letdown the wheel(stop byte)
				if (!IS_READING_JOYSTICK)
					device.WriteData(255);
			}
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::M)
			{
				// Switching on/off the momentum of wheels
				momentum ^= 1;
			}
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Delete)
			{
				// Set player at starting position
				player->body->SetAngularVelocity(0);
				player->body->SetLinearVelocity(b2Vec2(0, 0));
				player->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);

				if (robotRooling && IS_READING_JOYSTICK)
				{
					device.WriteData(90 + WHEEL_ANGLE_BIAS);
					Sleep(300);
				}
			}
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Up)
				step++;
			if (myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Down)
				step--;
			if (myEvent.type == sf::Event::JoystickMoved)
			{
				if (IS_READING_JOYSTICK)
					player->SetWheelsAngle(((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG);
				//cout << ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) << endl;
				if (!isWheelBiasSet)
				{
					Set_WHEEL_ANGLE_BIAS();
					isWheelBiasSet = true;
					clock.restart();
				}
			}

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
					if (IS_READING_JOYSTICK)
						player->SetWheelsAngle(((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG);
				}
			}			
		}

		// Check contacts before step
		for (b2ContactEdge* contact = player->body->GetContactList(); contact; contact = contact->next)
		{			
			//Check if contact with track wall
			if (contact->contact->IsTouching() && 
				contact->contact->GetFixtureA()->GetBody()->GetUserData() == blocks[0].body->GetUserData())
			{

				// Set player at starting position
				player->body->SetAngularVelocity(0);
				player->body->SetLinearVelocity(b2Vec2(0,0));
				player->body->SetTransform(b2Vec2(START_POS_X / SCALE, START_POS_Y / SCALE), START_ANGLE / DEG);
				player->SetWheelsAngle(90);
				Sleep(500);
				//step--;
				
				if (robotRooling && IS_READING_JOYSTICK)
				{
					device.WriteData(90 + WHEEL_ANGLE_BIAS);
					Sleep(300);
				}
			}
		}	

		// Do World step		
		double timeElapsed = clock.getElapsedTime().asSeconds();
		World.Step(timeElapsed, 8, 3);
		clock.restart();
		
		player->DoStep(step, timeElapsed, IS_READING_JOYSTICK);
		if (robotRooling)
			player->WatchEnv(blocks); 

		if (!momentum && !IS_READING_JOYSTICK)
			speedText.setString("momentum off\n		 " + std::to_string((int)step * 10) + "КМ/Ч");
		else if(IS_READING_JOYSTICK)
			speedText.setString("       joystick\n		 " + std::to_string((int)step * 10) + "КМ/Ч");
		else
			speedText.setString("\n		 " + std::to_string((int)step * 10) + "КМ/Ч");

		// Display functions
		window.clear(Color::White);
		window.draw(bg);
		for (size_t i = 0; i < blocks.size(); i++)
			blocks[i].Draw(window);
		player->Draw(window, robotRooling);

		window.draw(speedTextBG);
		window.draw(speedText);
		window.display();
	}
	
	return 0;
}