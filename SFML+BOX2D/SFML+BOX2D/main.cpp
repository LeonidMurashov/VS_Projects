
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

const float SCALE = 30.f;
const float DEG = 57.29577f;

b2Vec2 Gravity(0.f, 9.8f);
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
	bdef.position.Set((x + w/2) / SCALE, (y + h/2) / SCALE);

	b2Body *b_ground = World.CreateBody(&bdef);
	b_ground->CreateFixture(&gr, 1);	
}


int WinMain()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(800, 600), "Falling box");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Texture t1, t2;
	t1.loadFromFile("ground.jpg");
	t2.loadFromFile("box.jpg");
	t2.setSmooth(true);
	Sprite sGround(t1), sBox(t2);
	sBox.setOrigin(30, 30);
	

	//////////Box2D//////////////
	SetWall(0, 300, 148, 132);
	SetWall(148, 433, 456, 20);
	SetWall(640, 300, 160, 132);

	b2PolygonShape shape;
	shape.SetAsBox(30 / SCALE, 30/ SCALE);

	for (int i = 0; i < 800; i += 1)
	{
		b2BodyDef bdef;
		bdef.type = b2_dynamicBody;
		bdef.position.Set(i / SCALE, 0 / SCALE);
		bdef.angle = rand() % 90;

		b2Body *body = World.CreateBody(&bdef);
		body->CreateFixture(&shape, 2);
		body->SetUserData("box");
	}


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
			//if (myEvent.type == sf::Event::JoystickMoved)
			//	std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
		}


		World.Step(1/60.f, 8, 3);

		window.clear(Color::White);
		// Display-functions 
		window.draw(sGround);

		for (b2Body* it = World.GetBodyList(); it != 0; it = it->GetNext())
		{
			if (it->GetUserData() == "box")
			{
				b2Vec2 pos = it->GetPosition();
				float angle = it->GetAngle();
				sBox.setPosition(pos.x*SCALE, pos.y*SCALE);
				sBox.setRotation(angle*DEG);
				window.draw(sBox);
			}
		}
		window.display();
	}

	return 0;
}