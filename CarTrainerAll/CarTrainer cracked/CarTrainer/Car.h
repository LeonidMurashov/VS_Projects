#pragma once

class Car : public BoxObject
{
protected:
	double wheelsAngle;
	int wheelOffset = 16;

public:

	void SetWheelsAngle(double _wheelsAngle)
	{
		if (_wheelsAngle < 0)
			_wheelsAngle = 0;
		else if (_wheelsAngle > 180 / DEG)
			_wheelsAngle = 180 / DEG;

		wheelsAngle = ((_wheelsAngle - 90 / DEG) - (_wheelsAngle - 90 / DEG) / 2) / 1.5;
	}

	Car(Texture &tex, IntRect texRect, char* userData) : BoxObject(tex, texRect, userData, true)
	{
		wheelsAngle = 0;

	}

	void DoStep(double speed)
	{
		body->SetAngularVelocity(wheelsAngle*speed);

		//body->SetTransform(body->GetPosition(), body->GetAngle() + (float32)deltaAngle);
		b2Vec2 forceVec((float32)speed * cos(body->GetAngle() + (float32)wheelsAngle - 90 / DEG), (float32)speed * sin(body->GetAngle() + (float32)wheelsAngle - 90 / DEG));
		body->SetLinearVelocity(forceVec);
		
		speedText.setString(std::to_string((int)speed * 9) + "ÊÌ/×");

		// Vertex(sf::Vector2f((forceVec.x + wheelPointVec.x) * SCALE, (forceVec.y + wheelPointVec.y) * SCALE));
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