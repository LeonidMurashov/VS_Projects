#pragma once

using namespace NeuralNetworkLibrary2;

class NeuralCar : public Car
{
protected:
	std::vector<double> sensorResults;
	b2Vec2 skanVecs[7];
	Vertex line[7][2];

public:
	NeuralNetwork *Network;	// Put me in protected

	// Defined Network constructor
	NeuralCar(Texture &tex, IntRect texRect, char* userData, NeuralNetwork *_Network) :Car(tex, texRect, userData)
	{		
		Network = _Network;
	}

	void Draw(sf::RenderWindow& window, bool drawRays)
	{
		b2Vec2 pos = body->GetPosition();
		float angle = body->GetAngle();
		sp.setPosition(pos.x*SCALE, pos.y*SCALE);
		sp.setRotation(angle*DEG);
		window.draw(sp);
		if (drawRays)
		{
			for (int i = 0; i < 7; i++)
			{
				line[i][0].color = sf::Color::Red;
				line[i][1].color = sf::Color::Blue;
				window.draw(line[i], 2, sf::Lines);
			}
		}

		// Draw Speed vector
		speedVertex[0].color = sf::Color::Black;
		speedVertex[1].color = sf::Color::Black;
		window.draw(speedVertex, 2, sf::Lines);
	}

	/*template <class T>
	std::string to_string(T param)
	{
		std::string str = "";
		std::stringstream ss;
		ss << param;
		std::getline(ss, str);
		return str;
	}*/

	void WatchEnv(std::vector<BoxObject> blocks)
	{
		const int Ray_Distance = 8;

		b2Vec2 wheelPointVec(body->GetWorldCenter().x + wheelOffset * sin(body->GetAngle()) / SCALE, body->GetWorldCenter().y - wheelOffset * cos(body->GetAngle()) / SCALE);

		for (int i = 0; i < 7; i++)
		{
			line[i][0] = Vertex(sf::Vector2f(wheelPointVec.x * SCALE, wheelPointVec.y * SCALE));
			if (sensorResults.size())
				line[i][1] = Vertex((sf::Vector2f(wheelPointVec.x * SCALE + sensorResults[i] * skanVecs[i].x * SCALE, wheelPointVec.y * SCALE + sensorResults[i] * skanVecs[i].y * SCALE)));
			else
				line[i][1] = Vertex((sf::Vector2f(wheelPointVec.x * SCALE + skanVecs[i].x * SCALE, wheelPointVec.y * SCALE + skanVecs[i].y * SCALE)));

		}

		// Create Ray vectors
		int angles[7] = { 0, -20, 20, 45, -45, 60, -60 };
		for (int i = 0; i < 7; i++)
			skanVecs[i] = b2Vec2(Ray_Distance * cos(body->GetAngle() + (angles[i] - 90) / DEG), Ray_Distance * sin(body->GetAngle() + (angles[i] - 90) / DEG));

		// RayCast to get distances
		sensorResults.clear();
		for (int i = 0; i < 7; i++)
		{
			b2RayCastInput input;
			input.p1 = wheelPointVec;
			input.p2 = wheelPointVec + skanVecs[i];
			input.maxFraction = Ray_Distance / 8; // constant devision by 8

			double closestFraction = Ray_Distance / 8;
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

			sensorResults.push_back(closestFraction);
		}

		// Run Network
		vector<double> NetworkInput = sensorResults;
		// Adding wheels angle to sensors result
		//NetworkInput.push_back(GetWheelsAngle());
		vector<double> NetworkOutput;
		NetworkOutput = Network->Run(NetworkInput);
		//cout << NetworkOutput[0] << endl;

		if (IS_READING_JOYSTICK)
		{
	#ifdef ARDUINO
			if (device->IsConnected())
			{
				device->WriteData(String(std::to_string(NetworkOutput[0]) + '\n'));
				//sleep(sf::microseconds(20));
				//comPort->WriteData(String("r " + std::to_string((Joystick::getAxisPosition(0, Joystick::Axis::X) + 100) * 180 /(double) 200) + '\n'));
			}
	#else
			int angle = round(NetworkOutput[0] * DEG) - 17;
			if (angle < 0)
				angle = 0;
			device.WriteData((char)angle);
	#endif
		}
		
		if (!IS_READING_JOYSTICK)
			SetWheelsTargetAngle(NetworkOutput[0]);

		//((sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100) * 180 / (double)200) / (double)DEG
	
		//std::cout << forOut +180 << std::endl;
		//Sleep(100);

	  //set up input
     /* b2RayCastInput input;
      input.p1 = p1;
      input.p2 = p2;
      input.maxFraction = 1;
  
      //check every fixture of every body to find closest
      float closestFraction = 1; //start with end of line as p2
      b2Vec2 intersectionNormal(0,0);
      for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
          for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
  
              b2RayCastOutput output;
              if ( ! f->RayCast( &output, input ) )
                  continue;
              if ( output.fraction < closestFraction ) {
                  closestFraction = output.fraction;
                  intersectionNormal = output.normal;
              }            
          }*/
      }

	  void SaveNetwork(char* filePath)
	  {
		  Network->SaveToFile(filePath);
	  }
};

