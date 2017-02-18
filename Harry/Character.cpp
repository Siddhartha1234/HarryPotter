#include "Character.h"
#include "ResourceManager.h"
#include <iostream>
#include "GLTexture.h"
#include"Level.h"
#include <cmath>



Character::Character()
{
	
}

void Character::init(std::string name, glm::vec2 pos, int person, glm::vec2 dim,int speed,const std::vector<std::string>& levelData)
{
	_name = name;
	_position = pos;
	_person = person;
	_dim = dim;
	_texId = ResourceManager::getTexture(_filePaths[_person]).id;
	_speed = speed;
	_levelData = levelData;
}


Character::~Character()
{
}

void Character::draw(SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Color color = { 255,255,255,255 };
	glm::vec4 posSize = glm::vec4(_position.x, _position.y, _dim.x, _dim.y);
	spriteBatch.draw(posSize, uv, _texId, 0.0f, color);
}
void Character::moveUP()
{
	if ((_levelData[floor(_position.x / (float)TILE_WIDTH)][ceil((_position.y + _dim.y) / (float)TILE_WIDTH)] != '.') ||
		(_levelData[floor((_position.x + _dim.x) / (float)TILE_WIDTH)][ceil((_position.y + _dim.y) / (float)TILE_WIDTH)] != '.'))		//wall above somewhere
	{
		float distance=((int)(_position.y+_dim.y))%TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE)
			return;
	}		
	_position += glm::vec2(0.0f,_speed);
	return;
}
void Character::moveDOWN()
{
	if ((_levelData[floor(_position.x / (float)TILE_WIDTH)][floor((_position.y) / (float)TILE_WIDTH)-1] != '.') ||
		(_levelData[floor((_position.x + _dim.x) / (float)TILE_WIDTH)][floor((_position.y) / (float)TILE_WIDTH)-1] != '.')) //wall below somewhere
	{
		float distance = ((int)(_position.y)) % TILE_WIDTH;
		if ( distance < MIN_WALL_DISTANCE)
			return;
	}
	_position += glm::vec2(0.0f,- _speed);
	return;
}
void Character::moveLEFT()
{
	if ((_levelData[floor(_position.x / (float)TILE_WIDTH)-1][floor((_position.y+_dim.y) / (float)TILE_WIDTH)] != '.') ||
		(_levelData[floor((_position.x) / (float)TILE_WIDTH)-1][floor((_position.y) / (float)TILE_WIDTH)] != '.'))
	{
		float distance = ((int)(_position.x)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
			return;
	}
	_position += glm::vec2(-_speed, 0);
	return;
}
void Character::moveRIGHT()
{
	if ((_levelData[ceil((_position.x + _dim.x) / (float)TILE_WIDTH)][floor((_position.y + _dim.y) / (float)TILE_WIDTH)] != '.') ||
		(_levelData[ceil((_position.x + _dim.x) / (float)TILE_WIDTH)][floor((_position.y) / (float)TILE_WIDTH)] != '.'))
	{
		float distance = ((int)(_position.x + _dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE)
			return;
	}
	_position += glm::vec2(_speed, 0);
	return;
}