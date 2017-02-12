#include "Character.h"
#include "GLTexture.h"
#include "ResourceManager.h"



Character::Character(std::string name, glm::vec2 pos, Person person)
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
	static GLTexture texture = ResourceManager::getTexture(_filePaths[_person]);
	glm::vec4 posSize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posSize, uv, texture.id, 0.0f, color);
}
