#include "Bullet.h"
#include "GLTexture.h"
#include "ResourceManager.h"



Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime, int textureID, int damage)
{
	m_position = pos;
	m_dim = glm::vec2(5.0f, 5.0f);
	m_speed = speed;
	m_direction = dir;
	m_lifeTime = lifeTime;
	m_textureID = textureID;
	m_damage = damage;
}


Bullet::~Bullet()
{
}
void Bullet::draw(SpriteBatch& spriteBatch)
{	
	spriteBatch.draw(glm::vec4(m_position.x-m_dim.x/2, m_position.y - m_dim.y / 2,m_dim.x,m_dim.y), m_uv, m_textureID, 0.0f, m_color);
}

bool Bullet::update(const std::vector<std::string>& levelData)
{
	m_position += m_direction*m_speed;
	m_lifeTime--;
	if (m_lifeTime == 0)
		return true;

	if (levelData[(m_position.x / TILE_WIDTH)][(m_position.y / TILE_WIDTH)] != '.')
		return true;
	if (levelData[((m_position.x+m_dim.x) / TILE_WIDTH)][(m_position.y / TILE_WIDTH)] != '.')
		return true;
	if (levelData[(m_position.x / TILE_WIDTH)][((m_position.y+m_dim.y) / TILE_WIDTH)] != '.')
		return true;
	if (levelData[((m_position.x+m_dim.x) / TILE_WIDTH)][((m_position.y +m_dim.y)/ TILE_WIDTH)] != '.')
		return true;


	return false;
}
