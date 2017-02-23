#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include <string>
#include <vector>
#include "Gun.h"
#include "Bullet.h"
const int MIN_WALL_DISTANCE = 2;

enum State
{
	NOTSHOOTING= 0,
	SHOOTING= 1
};
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
	void update();
	void addGun(Gun gun);
	void nextGun();
	void selectGun(int n);
	void shoot(const glm::vec2& direction, std::vector<Bullet>& bullets);
	void stopShoot();
	void moveUP();
	void moveDOWN();
	void moveRIGHT();
	void moveLEFT();
	glm::vec2 getPosition() { return (m_position+glm::vec2(m_dim.x/2,m_dim.y/2)); }
	glm::vec2 getDim() { return m_dim; }
	bool damageTaken(int damage);
private:
	void respawn();
	glm::vec2 m_position,m_dim;
	glm::vec4 m_uv=glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	Color m_color = { 255,255,255,255 };
	std::string m_name;
	int m_person;
	int m_texId[2];
	int m_state;
	int m_speed;
	int m_health;
	std::vector<std::string> m_levelData;
	std::vector<Gun> m_guns;
	int m_currentGunIndex;
	std::string m_filePaths[6] = {"../Harry/Textures/harryPotter/Harry/harry.png","../Harry/Textures/harryPotter/Ron/ron.png","../Harry/Textures/harryPotter/Hermoine/hermoine.png","../Harry/Textures/harryPotter/Ginny/ginny.png","../Harry/Textures/harryPotter/Malfoy/malfoy.png","../Harry/Textures/harryPotter/Luna/luna.png" };
	std::string m_filePaths2[6] = { "../Harry/Textures/harryPotter/Harry/harry2.png","../Harry/Textures/harryPotter/Ron/ron2.png","../Harry/Textures/harryPotter/Hermoine/hermoine2.png","../Harry/Textures/harryPotter/Ginny/ginny2.png","../Harry/Textures/harryPotter/Malfoy/malfoy2.png","../Harry/Textures/harryPotter/Luna/luna2.png" };
};

