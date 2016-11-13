#pragma once

class Car : public BoxObject
{
protected:
	// Wheel distance from center of car
	int wheelOffset = 16;
	double wheelsTargetAngle = 90 / DEG;

private:
	// Momentum for wheels
	const double MOMENTUM = 70;
	double wheelsAngle;

public:

	// Set wheels angle instantly
	void SetWheelsAngle(double _wheelsAngle)
	{
		if (_wheelsAngle < 0)
			_wheelsAngle = 0;
		else if (_wheelsAngle > 180 / DEG)
			_wheelsAngle = 180 / DEG;

		wheelsAngle = ((_wheelsAngle - 90 / DEG) - (_wheelsAngle - 90 / DEG) / 2) / 1.5;
	}

	// Set targetWheelsAngle, used for wheel momenting
	void SetWheelsTargetAngle(double _wheelsTargetAngle)
	{
		if (_wheelsTargetAngle < 0)
			_wheelsTargetAngle = 0;
		else if (_wheelsTargetAngle > 180 / DEG)
			_wheelsTargetAngle = 180 / DEG;

		wheelsTargetAngle = ((_wheelsTargetAngle - 90 / DEG) - (_wheelsTargetAngle - 90 / DEG) / 2) / 1.5;
		//wheelsAngle = ((_wheelsTargetAngle - 90 / DEG) - (_wheelsTargetAngle - 90 / DEG) / 2) / 1.5;
	}

	double GetWheelsAngle()
	{
		return wheelsAngle;
	}

	Car(Texture &tex, IntRect texRect, char* userData) : BoxObject(tex, texRect, userData, true)
	{
		wheelsAngle = 0;
	}

	// Do all phisics here
	void DoStep(double speed, double timeElapsed, bool isReadingJoystic)
	{
		body->SetAngularVelocity(wheelsAngle * speed);
		b2Vec2 forceVec((float32)speed * cos(body->GetAngle() + (float32)wheelsAngle - 90 / DEG), (float32)speed * sin(body->GetAngle() + (float32)wheelsAngle - 90 / DEG));
		body->SetLinearVelocity(forceVec);

		// Turning wheels
		if (!isReadingJoystic)
			if (momentum)
				wheelsAngle += MOMENTUM*timeElapsed*(wheelsAngle < wheelsTargetAngle ? 1 : -1) / DEG;
			else
				wheelsAngle = wheelsTargetAngle;
		//cout << "Wheels: " << wheelsAngle << " Target: " << wheelsTargetAngle << endl;
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