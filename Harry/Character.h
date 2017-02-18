#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include <string>
#include <vector>
const int MIN_WALL_DISTANCE = 2;

enum Person
{
	HARRY=0,
	RON=1,
	HERMOINE=2,
	GINNY=3,
	MALFOY=4,
	LUNA=5
};
class Character
{
public:
	Character();
	~Character(); 
	void init(std::string name, glm::vec2 pos, int person,glm::vec2 dim,int speed, const std::vector<std::string>& levelData);
	void draw(SpriteBatch& spriteBatch);
	void moveUP();
	void moveDOWN();
	void moveRIGHT();
	void moveLEFT();
	glm::vec2 getPosition() { return _position; }
private:
	//GLTexture _texture;
	glm::vec2 _position,_dim;
	std::string _name;
	int _person;
	int _texId;
	int _speed;
	std::vector<std::string> _levelData;

	std::string _filePaths[6] = {"../Harry/Textures/harryPotter/Harry/harry.png","../Harry/Textures/harryPotter/Ron/ron.png","../Harry/Textures/harryPotter/Hermoine/hermoine.png","../Harry/Textures/harryPotter/Ginny/ginny.png","../Harry/Textures/harryPotter/Malfoy/malfoy.png","../Harry/Textures/harryPotter/Luna/luna.png" };
};

