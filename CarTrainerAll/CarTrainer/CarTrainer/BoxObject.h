#pragma once

const float SCALE = 30.f;
const float DEG = 57.29577f;

using namespace sf;

class  BoxObject
{
public:
	b2Body *body;
	Sprite sp;
	bool destroyFlag = false;
	

	BoxObject(Texture &tex, IntRect texRect, char* userData, bool isDynamic)
	{
		sp.setTexture(tex);
		sp.setTextureRect(texRect);
		sp.setOrigin((float)(texRect.width / 2.0), (float)(texRect.height / 2.0));

		b2PolygonShape shape;
		shape.SetAsBox(texRect.width / 2 / SCALE, texRect.height / 2 / SCALE);

		//b2CircleShape shape;
		//shape.m_radius = 25 / SCALE;

		b2BodyDef bdef;
		if (isDynamic)
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

	~BoxObject()
	{
		destroyFlag = true;
	}
};

