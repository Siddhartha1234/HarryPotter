#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
//#include "GLTexture.h"

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
	void init(std::string name, glm::vec2 pos, int person,glm::vec2 dim);
	void draw(SpriteBatch& spriteBatch);
	void moveUP();
	void moveDOWN();
	void moveRIGHT();
	void moveLEFT();
private:
	//GLTexture _texture;
	glm::vec2 _position,_dim;
	std::string _name;
	int _person;
	int _texId;
	float _speed;

	std::string _filePaths[3] = {"Textures/harryPotter/Harry/harry.png","Textures/harryPotter/Ron/ron.png","Textures/harryPotter/Hermoine/hermoine.png" };
};

