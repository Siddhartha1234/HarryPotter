#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "Timing.h"
#include "Window.h"
#include "Character.h"
#include "Bullet.h"

enum class GameState {PLAY,EXIT};
class MainGame
{
public:
	MainGame();
	~MainGame();

	
	void run();

private:
	void initSystems();
	void initShaders();
	void initialiseSDL();
	void gameLoop();
	void processInput();
	void drawGame();
	void displayFPS();
	//void updateCharacters();

	Window _window;
	int _screenWidth, _screenHeight;
	GameState _gameState;

	GLSLProgram _colorProgram;

	SpriteBatch _spriteBatch;

	InputManager _inputManager;
	FpsLimiter _fpsLimiter;

	float _time;
	float _fps;
	float _maxFPS;

	Camera2D _camera;
	std::vector<Bullet> _bullets;

	//Character rahul, sid;
};

