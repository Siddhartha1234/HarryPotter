#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "Level.h"

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime, int textureID,int damage);
	~Bullet();
	void draw(SpriteBatch& spriteBatch);
	bool update(const std::vector<std::string>& levelData);//return true is bullet needs to be deleted
	glm::vec2 getPosition() { return m_position + glm::vec2(m_dim.x/ 2, m_dim.y / 2); }
	glm::vec2 getDim() { return m_dim; }
	int getDamage() { return m_damage; }
private:
	float m_speed;
	glm::vec2 m_direction;
	glm::vec2 m_position;
	glm::vec2 m_dim;
	int m_damage;
	int m_lifeTime;
	int m_textureID;
	glm::vec4 m_uv= glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	Color m_color = { 0,255,255,255 };
};

