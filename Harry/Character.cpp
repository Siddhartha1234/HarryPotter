#include "Character.h"
#include "ResourceManager.h"
#include <iostream>
#include "GLTexture.h"



Character::Character()
{
	
}

void Character::init(std::string name, glm::vec2 pos, int person, glm::vec2 dim)
{
	_name = name;
	_position = pos;
	_person = person;
	_dim = dim;
	_texId = ResourceManager::getTexture(_filePaths[_person]).id;
	_speed = 1.0f;
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
	_position += glm::vec2(0.0f,_speed);
	return;
}
void Character::moveDOWN()
{
	_position += glm::vec2(0.0f ,-_speed);
	return;
}
void Character::moveLEFT()
{
	_position += glm::vec2(-_speed, 0);
	return;
}
void Character::moveRIGHT()
{
	_position += glm::vec2(_speed, 0);
	return;
}