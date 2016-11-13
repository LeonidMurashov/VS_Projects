#pragma once

class Car : public BoxObject
{
protected:
	Vertex speedVertex[2];

	// Wheel distance from center of car
	int wheelOffset = 16;
	double wheelsTargetAngle = 90 / DEG;
	
private:
	// Momentum for wheels
	const double MOMENTUM = 45;
	double wheelsAngle;
	
	// Set wheels angle instantly
	void SetWheelsAngle(double _wheelsAngle)
	{
		if (_wheelsAngle < 0)
			_wheelsAngle = 0;
		else if (_wheelsAngle > 180 / DEG)
			_wheelsAngle = 180 / DEG;

		wheelsAngle = ((_wheelsAngle - 90 / DEG) - (_wheelsAngle - 90 / DEG) / 2) / 1.5;
	}

public:	

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
	{  return wheelsAngle; }

	Car(Texture &tex, IntRect texRect, char* userData) : BoxObject(tex, texRect, userData, true)
	{
		wheelsAngle = 0;
	}

	// Do all phisics here
	void DoStep(double speed, double timeElapsed, std::vector<BoxObject> blocks)
	{
		body->SetAngularVelocity(wheelsAngle * speed);
		b2Vec2 forceVec((float32)speed * cos(body->GetAngle() + (float32)wheelsAngle - 90 / DEG), (float32)speed * sin(body->GetAngle() + (float32)wheelsAngle - 90 / DEG));		
		body->SetLinearVelocity(forceVec);
		
		// Turning wheels
		if (momentum && speed)
			wheelsAngle += MOMENTUM*timeElapsed*(wheelsAngle < wheelsTargetAngle ? 1 : -1) / DEG;
		else
			wheelsAngle = wheelsTargetAngle;		

		// RayCast speed vector
		const float32 Force_Vec_Length = 8;
		b2Vec2 wheelPointVec(body->GetWorldCenter().x + wheelOffset * sin(body->GetAngle()) / SCALE, body->GetWorldCenter().y - wheelOffset * cos(body->GetAngle()) / SCALE);
		
		// The same forceVec, for drawing only
		b2Vec2 forceVecForDrawing(Force_Vec_Length * cos(body->GetAngle() + (float32)wheelsAngle - 90 / DEG), Force_Vec_Length * sin(body->GetAngle() + (float32)wheelsAngle - 90 / DEG));
		b2RayCastInput input;
		input.p1 = wheelPointVec;
		input.p2 = wheelPointVec + forceVecForDrawing;
		input.maxFraction = Force_Vec_Length / 8; // constant devision by 8

		double closestFraction = Force_Vec_Length / 8;
		for (BoxObject block : blocks)
		{
			b2RayCastOutput output;
			b2Fixture* f = block.body->GetFixtureList();
			if (!f->RayCast(&output, input, 0))
				continue;
			if (output.fraction < closestFraction)
			{
				closestFraction = output.fraction;
			}
		}

		speedVertex[0] = Vertex(sf::Vector2f(wheelPointVec.x * SCALE, wheelPointVec.y * SCALE));
		speedVertex[1] = Vertex((sf::Vector2f(wheelPointVec.x * SCALE + closestFraction * forceVecForDrawing.x * SCALE, wheelPointVec.y * SCALE + closestFraction * forceVecForDrawing.y * SCALE)));
	
		//b2Vec2 forceVec((float32)Force_Vec_Length * cos(body->GetAngle() + (float32)GetWheelsAngle() - 90 / DEG), Force_Vec_Length * sin(body->GetAngle() + (float32)GetWheelsAngle() - 90 / DEG));

	}

	void Draw(sf::RenderWindow& window)
	{
		b2Vec2 pos = body->GetPosition();
		float angle = body->GetAngle();
		sp.setPosition(pos.x*SCALE, pos.y*SCALE);
		sp.setRotation(angle*DEG);
		window.draw(sp);

		// Draw Speed vector
		speedVertex[0].color = sf::Color::Black;
		speedVertex[1].color = sf::Color::Black;
		window.draw(speedVertex, 2, sf::Lines);
	}

};