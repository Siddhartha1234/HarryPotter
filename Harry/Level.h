#pragma once
#include<string>
#include <vector>
#include "SpriteBatch.h"
const int TILE_WIDTH = 20;
class Level
{
public:
	Level(const std::string& fileName, int screenWidth, int screenHeight);
	~Level();

	void draw();
	std::vector<std::string> getLevelData() { return m_levelData; }

private:
	std::vector<std::string> m_levelData;
	SpriteBatch m_spriteBatch;
};

