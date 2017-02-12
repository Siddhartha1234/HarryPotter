#include "Character.h"
#include "ResourceManager.h"
#include <iostream>
#include "GLTexture.h"



Character::Character()
{
	
}

void Character::init(std::string name, glm::vec2 pos, int person)
{
	_name = name;
	_position = pos;
	_person = person;
	
}


Character::~Character()
{
}

void Character::draw(SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Color color = { 255,255,255,255 };
	glm::vec4 posSize = glm::vec4(_position.x, _position.y, 50, 100);
	static GLTexture _texture[2] = { ResourceManager::getTexture(_filePaths[0]),ResourceManager::getTexture(_filePaths[1]) };
	spriteBatch.draw(posSize, uv, _texture[_person].id, 0.0f, color);
	//std::cout << _texture.id << std::endl;
}
void Character::moveUP()
{
	_position += glm::vec2(0.0f,1.0f);
	return;
}
void Character::moveDOWN()
{
	_position += glm::vec2(0.0f ,-1.0f);
	return;
}
void Character::moveLEFT()
{
	_position += glm::vec2(-1.0f, 0);
	return;
}
void Character::moveRIGHT()
{
	_position += glm::vec2(1.0f, 0);
	return;
}
void Character::update()
{
	return;
}