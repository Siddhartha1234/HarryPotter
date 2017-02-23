#include "SimpleGame.h"
#include"ResourceManager.h"
#include <cmath>
#include <iostream>



SimpleGame::SimpleGame():m_screenWidth(1020),
						m_screenHeight(720),
						m_maxFPS(60.0f),
						m_gameState(GameState::PLAY),
						m_fps(0.0f),
						m_currentLevel(0)
{
	m_playerDim = glm::vec2(15.0f, 15.0f);
	m_bulletDim = glm::vec2(5.0f, 5.0f);
}


SimpleGame::~SimpleGame()
{
	for (unsigned int i = 0; i < m_levels.size(); i++)
	{
		delete m_levels[i];
	}
}

void SimpleGame::run()
{
	initSystems();
	
	gameLoop();
}

void SimpleGame::initSystems()
{
	initialiseSDL();
	m_window.createWindow("Game Engine", m_screenWidth, m_screenHeight, 0);
	initShaders();
	m_camera.init(m_screenWidth, m_screenHeight);
	m_camera.setScale(4);
	initialiseLevel(m_currentLevel);
	m_spriteBatch.init();
	m_fpsLimiter.setMaxFPS(m_maxFPS);

	m_leveldata = m_levels[m_currentLevel]->getLevelData();
	m_mainPlayer.init("Rahul", glm::vec2(80.0f,80.0f), 0,glm::vec2(15,15),1, m_leveldata);
	sid.init("SID", glm::vec2(100.0f, 100.0f), 2, glm::vec2(15, 15),1, m_leveldata);
	//m_chars.push_back(&sid);
	m_bulletTexID = ResourceManager::getTexture("../Harry/Textures/bullet.png").id;
	Gun magnum(30, 1, 0.1f, 30, 4.0f, 100, m_bulletTexID); //int fireRate, int bulletsPerShot, float spread,int damage,float speed,int lifeTime,int bulletTex
	Gun shotgun(40, 20, 0.3f, 4, 4.0f, 100, m_bulletTexID);
	Gun mp5(5, 1, 0.2f, 20, 4.0f, 100, m_bulletTexID);
	m_mainPlayer.addGun(magnum);
	m_mainPlayer.addGun(shotgun);
	m_mainPlayer.addGun(mp5);
}

void SimpleGame::initialiseLevel(int level)
{
	m_levels.push_back(new Level("../Harry/Levels/level" + std::to_string(level+1) + ".txt", m_screenWidth, m_screenHeight));
}

void SimpleGame::initialiseSDL()
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//avoids flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void SimpleGame::initShaders()
{
	m_textureProgram.compileShaders("../Harry/Shaders/colorShading.vert", "../Harry/Shaders/colorShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
}

void SimpleGame::gameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		m_fpsLimiter.begin();

		processInput();
		m_camera.setPosition(m_mainPlayer.getPosition());
		m_camera.update();
		updateChars();
		updateBullets();
		drawGame();

		m_fps = m_fpsLimiter.end();
		//displayFPS();
	}
}
void SimpleGame::updateChars()
{
	m_mainPlayer.update();

}

void SimpleGame::updateBullets()
{
	for (unsigned int i = 0; i < m_bullets.size(); )
	{
		glm::vec2 bulPos = m_bullets[i].getPosition();
		glm::vec2 playerPos=sid.getPosition();
		if(abs(bulPos.x-playerPos.x)<(m_playerDim.x/2+m_bulletDim.x/2) && 
			abs(bulPos.y - playerPos.y) < (m_playerDim.y / 2 + m_bulletDim.y / 2))
		{
			sid.damageTaken(m_bullets[i].getDamage());
			m_bullets[i] = m_bullets.back();
			m_bullets.pop_back();
			continue;
		}
		if (m_bullets[i].update(m_leveldata))
		{
			m_bullets[i] = m_bullets.back();
			m_bullets.pop_back();
		}
		else
			i++;
	}
}

void SimpleGame::processInput()
{
	SDL_Event evnt;
	const float SCALE_SPEED = 0.01f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				m_inputManager.pressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_inputManager.releaseKey(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_inputManager.pressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_inputManager.releaseKey(evnt.button.button);
				break;
		}
	}
	if (m_inputManager.isKeyPressed(SDLK_w))
		sid.moveUP();
	if (m_inputManager.isKeyPressed(SDLK_s))
		sid.moveDOWN();

	if (m_inputManager.isKeyPressed(SDLK_a))
		sid.moveLEFT();

	if (m_inputManager.isKeyPressed(SDLK_d))
		sid.moveRIGHT();

	if (m_inputManager.isKeyPressed(SDLK_UP))
		m_mainPlayer.moveUP();

	if (m_inputManager.isKeyPressed(SDLK_DOWN))
		m_mainPlayer.moveDOWN();

	if (m_inputManager.isKeyPressed(SDLK_LEFT))
		m_mainPlayer.moveLEFT();

	if (m_inputManager.isKeyPressed(SDLK_RIGHT))
		m_mainPlayer.moveRIGHT();

	if (m_inputManager.isKeyPressed(SDLK_q))
		m_camera.setScale(m_camera.getScale() + SCALE_SPEED);
	if (m_inputManager.isKeyPressed(SDLK_e))
		m_camera.setScale(m_camera.getScale() - SCALE_SPEED);

	if (m_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 direction = m_camera.convertScreenToWorld(m_inputManager.getMouseCoords()) - m_mainPlayer.getPosition();
		direction = glm::normalize(direction);
		m_mainPlayer.shoot(direction, m_bullets);
	}
	else
		m_mainPlayer.stopShoot();

	if (m_inputManager.isKeyPressed(SDLK_1))
	{
		m_mainPlayer.selectGun(0);
	}
	if (m_inputManager.isKeyPressed(SDLK_2))
	{
		m_mainPlayer.selectGun(1);
	}
	if (m_inputManager.isKeyPressed(SDLK_3))
	{
		m_mainPlayer.selectGun(2);
	}
}

void SimpleGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set background color
	glClearColor(211.0f/255, 211.0f / 255, 211.0f / 255, 1.0f);

	m_textureProgram.use();
	//use the first texture
	glActiveTexture(GL_TEXTURE0);

	//send unifrom varibales

	//Get location
	GLint textureLocation = m_textureProgram.getUnifromLocation("mySampler");
	//upload the mySampler(Indicates which texture to use)
	glUniform1i(textureLocation, 0);

	//Get location
	GLint pLocation = m_textureProgram.getUnifromLocation("P");
	//grab the camera matrix
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
	//upload the camera matrix
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_levels[m_currentLevel]->draw();


	m_spriteBatch.begin();

	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i].draw(m_spriteBatch);
	}
	m_mainPlayer.draw(m_spriteBatch);
	sid.draw(m_spriteBatch);
	
	m_spriteBatch.end();
	m_spriteBatch.renderBatch(); 	
	
	glBindTexture(GL_TEXTURE_2D, 0);
	m_textureProgram.unuse();
	m_window.swapBuffer();	
}


void SimpleGame::displayFPS()
{
	//Use when we need to display fps
	static int frameCounter = 0;
	frameCounter++;
	if (frameCounter == 100)
	{
		std::cout << m_fps << std::endl;
		frameCounter = 0;
	}
}