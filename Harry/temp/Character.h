#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
enum Person
{
	HARRY=0,
	RON=1,
	HERMOINE=2
};
class Character
{
public:
	Character(std::string name,glm::vec2 pos, Person person);
	~Character(); 
	void draw(SpriteBatch& spriteBatch);
private:
	glm::vec2 _position;
	std::string _name;
	Person _person;
	std::string _filePaths[3] = {"Textures/harryPotter/Harry/harry.png","Textures/harryPotter/Harry/ron.png","Textures/harryPotter/Harry/hermoine.png" };
};

