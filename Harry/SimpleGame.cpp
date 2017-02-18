#include "SimpleGame.h"
#include"ResourceManager.h"
#include <iostream>



SimpleGame::SimpleGame():_screenWidth(1020),
						_screenHeight(720),
						_maxFPS(60.0f),
						_gameState(GameState::PLAY),
						_fps(0.0f),
						_currentLevel(0)
{
}


SimpleGame::~SimpleGame()
{
	for (int i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
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
	_window.createWindow("Game Engine", _screenWidth, _screenHeight, 0);
	initShaders();
	_camera.init(_screenWidth, _screenHeight);
	_camera.setScale(4);
	initialiseLevel(_currentLevel);
	_spriteBatch.init();
	_fpsLimiter.setMaxFPS(_maxFPS);


	rahul.init("Rahul", glm::vec2(80.0f,80.0f), 0,glm::vec2(15,15),1,_levels[_currentLevel]->getLevelData());
	sid.init("SID", glm::vec2(100.0f, 100.0f), 2, glm::vec2(15, 15),1, _levels[_currentLevel]->getLevelData());
}

void SimpleGame::initialiseLevel(int level)
{
	_levels.push_back(new Level("Levels/level" + std::to_string(level+1) + ".txt", _screenWidth, _screenHeight));
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
	_textureProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();
}

void SimpleGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.begin();

		processInput();
		_camera.setPosition(rahul.getPosition());
		_camera.update();
		drawGame();

		_fps = _fpsLimiter.end();
		//displayFPS();
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
				_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				_inputManager.pressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.releaseKey(evnt.key.keysym.sym);
				break;
		}
	}
	if (_inputManager.isKeyPressed(SDLK_w))
		sid.moveUP();
	if (_inputManager.isKeyPressed(SDLK_s))
		sid.moveDOWN();

	if (_inputManager.isKeyPressed(SDLK_a))
		sid.moveLEFT();

	if (_inputManager.isKeyPressed(SDLK_d))
		sid.moveRIGHT();

	if (_inputManager.isKeyPressed(SDLK_UP))
		rahul.moveUP();

	if (_inputManager.isKeyPressed(SDLK_DOWN))
		rahul.moveDOWN();

	if (_inputManager.isKeyPressed(SDLK_LEFT))
		rahul.moveLEFT();

	if (_inputManager.isKeyPressed(SDLK_RIGHT))
		rahul.moveRIGHT();
	if (_inputManager.isKeyPressed(SDLK_q))
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	if (_inputManager.isKeyPressed(SDLK_e))
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
}

void SimpleGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set background color
	glClearColor(211.0f/255, 211.0f / 255, 211.0f / 255, 1.0f);

	_textureProgram.use();
	//use the first texture
	glActiveTexture(GL_TEXTURE0);

	//send unifrom varibales

	//Get location
	GLint textureLocation = _textureProgram.getUnifromLocation("mySampler");
	//upload the mySampler(Indicates which texture to use)
	glUniform1i(textureLocation, 0);

	//Get location
	GLint pLocation = _textureProgram.getUnifromLocation("P");
	//grab the camera matrix
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	//upload the camera matrix
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_levels[_currentLevel]->draw();


	_spriteBatch.begin();

	rahul.draw(_spriteBatch);
	sid.draw(_spriteBatch);
	
	_spriteBatch.end();
	_spriteBatch.renderBatch(); 	
	
	glBindTexture(GL_TEXTURE_2D, 0);
	_textureProgram.unuse();
	_window.swapBuffer();	
}


void SimpleGame::displayFPS()
{
	//Use when we need to display fps
	static int frameCounter = 0;
	frameCounter++;
	if (frameCounter == 100)
	{
		std::cout << _fps << std::endl;
		frameCounter = 0;
	}
}