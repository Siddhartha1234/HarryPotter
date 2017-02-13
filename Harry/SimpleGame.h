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
	
	
	int _screenWidth, _screenHeight;
	GameState _gameState;
	int _currentLevel;

	Window _window;
	GLSLProgram _textureProgram;
	SpriteBatch _spriteBatch;
	
	InputManager _inputManager;
	Camera2D _camera;
	
	FpsLimiter _fpsLimiter;
	float _maxFPS;
	float _fps;

	std::vector<Level*> _levels;

	Character rahul, sid;
};

