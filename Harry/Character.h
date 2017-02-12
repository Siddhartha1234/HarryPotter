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
	Character();
	~Character(); 
	void init(std::string name, glm::vec2 pos, int person);
	void draw(SpriteBatch& spriteBatch);
	void update();
	void moveUP();
	void moveDOWN();
	void moveRIGHT();
	void moveLEFT();
private:
	glm::vec2 _position;
	std::string _name;
	int _person;

	std::string _filePaths[3] = {"Textures/harryPotter/Harry/harry.png","Textures/harryPotter/Ron/ron.png","Textures/harryPotter/Hermoine/hermoine.png" };
};

