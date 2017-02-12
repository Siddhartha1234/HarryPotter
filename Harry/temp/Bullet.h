#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
class Bullet
{
public:
	Bullet();
	~Bullet();
	void init(glm::vec2 pos,glm::vec2 dir,float speed, int lifeTime);
	void draw(SpriteBatch& spriteBatch);
	bool update();//return true is bullet needs to be deleted
private:
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
	int _lifeTime;
};

