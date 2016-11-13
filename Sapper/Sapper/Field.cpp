#include "Field.h"

using namespace std;
using namespace sf;


Field::Field(string textureFile, int LINE_SIZE, int BLOCK_DEMENTION, int GAME_DEMENTION, int DISPLAY_WIDTH, int DISPLAY_HEIGHT)
{
	tex.loadFromFile(textureFile);

	for (int i = 0; i < LINE_SIZE; i++)
	{
		vector<Sprite> vec;
		for (int j = 0; j < LINE_SIZE; j++)
		{
			Sprite sp(tex);
			vec.push_back(sp);
		}
		blocks.push_back(vec);
	}

	Place(textureFile, LINE_SIZE, BLOCK_DEMENTION, GAME_DEMENTION, DISPLAY_WIDTH, DISPLAY_HEIGHT);
}



Field::~Field()
{
	blocks.clear();
}

void Field::Place(string textureFile, int LINE_SIZE, int BLOCK_DEMENTION, int GAME_DEMENTION, int DISPLAY_WIDTH, int DISPLAY_HEIGHT)
{
	for (int i = 0; i < blocks.size(); i++)
		for (int j = 0; j < blocks[i].size(); j++)
		{
			blocks[i][j].setScale((double)BLOCK_DEMENTION / (double)tex.getSize().x, (double)BLOCK_DEMENTION / (double)tex.getSize().x);
			blocks[i][j].setOrigin(BLOCK_DEMENTION / 2, BLOCK_DEMENTION / 2);
			blocks[i][j].setPosition(Vector2f((j)*BLOCK_DEMENTION - GAME_DEMENTION / 2 + DISPLAY_WIDTH / 2, (i )*BLOCK_DEMENTION - GAME_DEMENTION / 2 + DISPLAY_HEIGHT / 2));
		}
}

void Field::Draw(RenderWindow &window)
{
	for (int i = 0; i < blocks.size(); i++)
		for(int j = 0; j < blocks[i].size(); j++)
			window.draw(blocks[i][j]);
}
