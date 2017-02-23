#include "Gun.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>



Gun::Gun(int fireRate, int bulletsPerShot, float spread,int damage,int speed,int lifeTime,int bulletTex)
{
	m_frameCounter = 0;
	m_fireRate = fireRate;
	m_bulletsPerShot = bulletsPerShot;
	m_spread = spread;
	m_bulletDamage = damage;
	m_bulletSpeed = speed;
	m_bulletLifeTime = lifeTime;
	m_bulletTex = bulletTex;
}

Gun::~Gun()
{
}

void Gun::update()
{	
	m_frameCounter++;	
}

void Gun::fireGun(const glm::vec2& direction, std::vector<Bullet>& bullets, const glm::vec2& position)
{
	if (m_frameCounter > m_fireRate)
	{
		static std::mt19937 randomEngine(time(nullptr));
		std::uniform_real_distribution<float> randRotate(-m_spread, m_spread);
		for (int i = 0; i < m_bulletsPerShot; i++)
		{
			bullets.emplace_back(position, glm::rotate(direction, randRotate(randomEngine)), m_bulletSpeed, m_bulletLifeTime, m_bulletTex, m_bulletDamage);
		}
		m_frameCounter = 0;
	}
}
