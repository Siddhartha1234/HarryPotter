#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>
#include "Camera2D.h"

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
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFPS();

	SDL_Window* _window;
	int _width, _height;
	GameState _gameState;
	std::vector<Sprite*> _sprites;
	GLSLProgram _colorProgram;
	float _time;
	float _fps;
	float _frameTime;
	float _maxFPS;

	Camera2D _camera;
};

