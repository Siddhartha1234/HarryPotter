#include "Character.h"
#include "ResourceManager.h"
#include <iostream>
#include "GLTexture.h"
#include"Level.h"
#include <cmath>



Character::Character() :m_currentGunIndex(-1)
{
	
}

void Character::init(std::string name, glm::vec2 pos, int person, glm::vec2 dim,int speed,const std::vector<std::string>& levelData)
{
	m_health = 200;
	m_name = name;
	m_position = pos;
	m_person = person;
	m_dim = dim;
	m_texId[NOTSHOOTING] = ResourceManager::getTexture(m_filePaths[m_person]).id;
	m_texId[SHOOTING] = ResourceManager::getTexture(m_filePaths2[m_person]).id;
	m_speed = speed;
	m_levelData = levelData;
	m_state = NOTSHOOTING;
}


Character::~Character()
{
}

void Character::draw(SpriteBatch& spriteBatch)
{
	spriteBatch.draw(glm::vec4(m_position.x, m_position.y, m_dim.x, m_dim.y), m_uv, m_texId[m_state], 0.0f, m_color);
}

void Character::update()
{
	m_guns[m_currentGunIndex].update();
}

void Character::addGun(Gun gun)
{
	m_guns.push_back(gun);
	if (m_currentGunIndex == -1)
		m_currentGunIndex = 0;
}

void Character::nextGun()
{
	m_currentGunIndex = (m_currentGunIndex + 1) % m_guns.size();
}

void Character::selectGun(int n)
{
	if (m_guns.size() >= n)
		m_currentGunIndex = n;
}

void Character::shoot(const glm::vec2& direction, std::vector<Bullet>& bullets)
{
	m_guns[m_currentGunIndex].fireGun(direction, bullets, m_position+ glm::vec2(m_dim.x / 2, m_dim.y / 2));
	m_state = SHOOTING;
}

void Character::stopShoot()
{
	m_state = NOTSHOOTING;
}

void Character::respawn()
{
	m_health = 200;
}

bool Character::damageTaken(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		std::cout << "PLAYER DEAD" << std::endl;
		respawn();
		return true;
	}
	return false;
}

void Character::moveUP()
{
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][ceil((m_position.y + m_dim.y) / (float)TILE_WIDTH)] != '.') ||
		(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][ceil((m_position.y + m_dim.y) / (float)TILE_WIDTH)] != '.'))		//wall above somewhere
	{
		float distance=((int)(m_position.y+m_dim.y))%TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE)
			return;
	}		
	m_position += glm::vec2(0.0f,m_speed);
	return;
}
void Character::moveDOWN()
{
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)-1] != '.') ||
		(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)-1] != '.')) //wall below somewhere
	{
		float distance = ((int)(m_position.y)) % TILE_WIDTH;
		if ( distance < MIN_WALL_DISTANCE)
			return;
	}
	m_position += glm::vec2(0.0f,- m_speed);
	return;
}
void Character::moveLEFT()
{
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH)-1][floor((m_position.y+m_dim.y) / (float)TILE_WIDTH)] != '.') ||
		(m_levelData[floor((m_position.x) / (float)TILE_WIDTH)-1][floor((m_position.y) / (float)TILE_WIDTH)] != '.'))
	{
		float distance = ((int)(m_position.x)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
			return;
	}
	m_position += glm::vec2(-m_speed, 0);
	return;
}
void Character::moveRIGHT()
{
	if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] != '.') ||
		(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] != '.'))
	{
		float distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE)
			return;
	}
	m_position += glm::vec2(m_speed, 0);
	return;
}