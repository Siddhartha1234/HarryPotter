#include "Level.h"
#include "Error.h"
#include<fstream>
#include "ResourceManager.h"
#include <iostream>





Level::Level(const std::string& fileName,int screenWidth,int screenHeight)
{

	static int redTexid = ResourceManager::getTexture("Textures/red_bricks.png").id;
	static int glassTexid = ResourceManager::getTexture("Textures/glass.png").id;
	static int lightTexid = ResourceManager::getTexture("Textures/light_bricks.png").id;
	std::ifstream file;
	file.open(fileName);

	if (file.fail())
		fatalError("Failed to open " + fileName);

	std::string line;
	while (std::getline(file, line))
	{
		_levelData.push_back(line);
	}
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color color = { 255,255,255,255 };
	_spriteBatch.init();
	_spriteBatch.begin();
	for (int x = 0; x < _levelData.size(); x++)
	{
		for (int y = 0; y < _levelData[x].size(); y++)
		{
			char tile = _levelData[x][y];
			glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			switch (tile)
			{
			case 'R':
				_spriteBatch.draw(destRect,
									uvRect,
									redTexid,
									0.0f,
									color);
				break;
			case 'G':
				_spriteBatch.draw(destRect,
					uvRect,
					glassTexid,
					0.0f,
					color);
				break;
			case 'L':
				_spriteBatch.draw(destRect,
					uvRect,
					lightTexid,
					0.0f,
					color);
				break;
			case '.':
			case 'B':
			case '@':
				break;
			default:
				std::cout << "Unexpected symbol " << tile << " at (" << x << ", " << y << ")\n";
				break;
			}
		}
	}
	_spriteBatch.end();	
}


Level::~Level()
{
}

void Level::draw()
{
	_spriteBatch.renderBatch();
}
