#include "Bullet.h"
#include "GLTexture.h"
#include "ResourceManager.h"



Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::init(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime)
{
	_position = pos;
	_speed = speed;
	_direction = dir;
	_lifeTime = lifeTime;

}
void Bullet::draw(SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Color color = { 255,255,255,255 };
	static GLTexture texture = ResourceManager::getTexture("Textures/harryPotter/Harry/29.png");
	glm::vec4 posSize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posSize, uv, texture.id, 0.0f, color);

}

bool Bullet::update()
{
	_position = _direction*_speed;
	_lifeTime--;
	if (_lifeTime == 0)
		return true;
}
