#pragma once
#include <glm\glm.hpp>
#include "Bullet.h"
#include <vector>
class Gun
{
public:
	Gun(int fireRate,int bulletsPerShot,float spread,int damage, int speed, int lifeTime, int bulletTex);
	~Gun();
	void update();
	void Gun::fireGun(const glm::vec2& direction, std::vector<Bullet>& bullets, const glm::vec2& position);
private:
	int m_fireRate;
	int m_bulletsPerShot;
	int m_bulletDamage;
	int m_bulletSpeed;
	int m_bulletLifeTime;
	float m_spread;
	int m_frameCounter;
	glm::vec2 m_position;
	int m_bulletTex;
};

