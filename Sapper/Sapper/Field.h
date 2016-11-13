#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Field
{
private:
	vector<vector<Sprite>> blocks;
	Texture tex;

public:
	Field(string textureFile, int LINE_SIZE, int BLOCK_DEMENTION, int GAME_DEMENTION, int DISPLAY_WIDTH, int DISPLAY_HEIGHT);
	~Field();

	void Place(string textureFile, int LINE_SIZE, int BLOCK_DEMENTION, int GAME_DEMENTION, int DISPLAY_WIDTH, int DISPLAY_HEIGHT);
	void Draw(RenderWindow &window);

};

