#pragma once
#include <SDL/SDL.h>
#include "Window.h"
#include "SpriteBatch.h"
#include "Timing.h"
#include "InputManager.h"
#include "Character.h"
#include "GLTexture.h"
#include "GLSLProgram.h"
#include "Level.h"
#include "Camera2D.h"
#include "Bullet.h"


enum class GameState { PLAY, EXIT };

class SimpleGame
{
public:
	SimpleGame();
	~SimpleGame();
	void run();

private:
	void initSystems();
	void initialiseSDL();
	void initShaders();
	void initialiseLevel(int currentLevel);
	void gameLoop();	
	void processInput();
	void drawGame();
	void displayFPS();

	void updateBullets();
	void updateChars();
	
	
	int m_screenWidth, m_screenHeight;
	GameState m_gameState;
	int m_currentLevel;
	std::vector<std::string> m_leveldata;

	Window m_window;
	GLSLProgram m_textureProgram;
	SpriteBatch m_spriteBatch;
	
	InputManager m_inputManager;
	Camera2D m_camera;
	
	FpsLimiter m_fpsLimiter;
	float m_maxFPS;
	float m_fps;

	std::vector<Level*> m_levels;
	std::vector<Bullet> m_bullets;

	glm::vec2 m_playerDim, m_bulletDim;
	//std::vector<Character*> m_chars;
	Character m_mainPlayer, sid;
	int m_bulletTexID;
};

