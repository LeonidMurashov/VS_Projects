
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

const float SCALE = 30.f;
const float DEG = 57.29577f;

b2Vec2 Gravity(0.f, 0.f);
b2World World(Gravity);

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

struct  BoxObject
{
	b2Body *body;
	Sprite sp;

	BoxObject(Texture &tex, IntRect texRect, char* userData, bool isDynamic)
	{
		sp.setTexture(tex);
		sp.setTextureRect(texRect);
		sp.setOrigin(texRect.width / 2, texRect.height / 2);

		//b2PolygonShape shape;
		//shape.SetAsBox(texRect.width / 2 / SCALE, texRect.height / 2 / SCALE);

		b2CircleShape shape;
		shape.m_radius = 25/SCALE;

		b2BodyDef bdef;
		if(isDynamic)
			bdef.type = b2_dynamicBody;

		body = World.CreateBody(&bdef);
		body->CreateFixture(&shape, 2);
		body->SetUserData(userData);
	}

	void Draw(sf::RenderWindow& window)
	{		
		b2Vec2 pos = body->GetPosition();
		float angle = body->GetAngle();
		sp.setPosition(pos.x*SCALE, pos.y*SCALE);
		sp.setRotation(angle*DEG);
		window.draw(sp);		
	}
};

#define DISPLAY_WIDTH 1680
#define DISPLAY_HEIGHT 1050

int main()
{
	srand(time(NULL));

	std::vector<BoxObject> boxes;

	sf::RenderWindow window(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "Space Rider", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Texture t1, t2;
	t1.loadFromFile("Images/spaceFullHD.jpg");
	t2.loadFromFile("Images/SpaceShip.png");
	t2.setSmooth(true);
	Sprite sGround(t1), sBox(t2);

	for (int i = 0; i < 50; i++)
	{
		boxes.push_back(BoxObject(t2, IntRect(0, 0, 50, 56), "SpaceShip", true));
		boxes[i].body->SetTransform(b2Vec2(rand() % DISPLAY_WIDTH / SCALE, rand() % DISPLAY_HEIGHT / SCALE), rand()%360 / DEG);
	}


	//////////Box2D//////////////
	//SetWall(0, 0, 10, 600);
	//SetWall(590, 0, 10, 600);

	
	boxes[0].body->SetFixedRotation(true);
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
			if (myEvent.type == sf::Event::JoystickMoved)
				boxes[0].body->SetTransform(boxes[0].body->GetPosition(), ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 360 / (double)200 + 180) / (double)DEG);
				//	std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
			if (myEvent.type == sf::Event::JoystickButtonPressed && Joystick::isButtonPressed(0, 2))
			{
				for (int i = 0; i < 50; i++)
				{
					boxes.push_back(BoxObject(t2, IntRect(0, 0, 50, 56), "SpaceShip", true));
					boxes[boxes.size()-1].body->SetTransform(b2Vec2(rand() % DISPLAY_WIDTH / SCALE, rand() % DISPLAY_HEIGHT / SCALE), rand() % 360 / DEG);
				}
			}
			if (myEvent.type == sf::Event::JoystickButtonPressed && Joystick::isButtonPressed(0, 1))
			{
				boxes[0].body->SetTransform(b2Vec2(DISPLAY_WIDTH/2/SCALE, DISPLAY_HEIGHT / 2 / SCALE), 0);
			}
		}

		double angle = boxes[0].body->GetAngle() - 3.14/2;
		std::cout.precision(4);
		std::cout << angle << " sin = "<< sin(angle) << std::endl;
		b2Body *myBody = boxes[0].body;
		myBody->SetLinearVelocity(b2Vec2(15 * cos(angle), 15 * sin(angle)));

		World.Step(1 / 60.f, 8, 3);

		window.clear(Color::White);
		// Display functions 
		window.draw(sGround);

		for (int i = 0; i < boxes.size(); i++)
			boxes[i].Draw(window);
		window.display();
	}

	return 0;
}