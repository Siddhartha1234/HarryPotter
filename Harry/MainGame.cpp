#include "MainGame.h"
#include "Error.h"
#include <iostream>
#include"ResourceManager.h"


MainGame::MainGame():	_screenWidth(1024),
						_screenHeight(768),
						_gameState(GameState::PLAY),
						_time(0.0f),
						_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}


MainGame::~MainGame()
{
}

void MainGame::initSystems()
{	
	initialiseSDL();
	_window.createWindow("Game Engine", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
	_fpsLimiter.setMaxFPS(_maxFPS);

	//rahul.init("Rahul", glm::vec2(0.0f, 0.0f), 1, glm::vec2(30, 30));
	//sid.init("SID", glm::vec2(60.0f, 0.0f), 0, glm::vec2(30, 30));
	
}

void MainGame::initialiseSDL()
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//avoids flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("../Harry/Shaders/colorShading.vert", "../Harry/Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::run()
{
	initSystems();	
	gameLoop();
}

void MainGame::gameLoop()
{
	while (_gameState!=GameState::EXIT)
	{
		_fpsLimiter.begin();
		processInput();
		_camera.update();

		/*for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].update())
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			i++;
		}*/

		drawGame();		
		_fps = _fpsLimiter.end();		
		
	}
}

void MainGame::displayFPS()
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

void MainGame::processInput()
{
	SDL_Event evnt;
	const float CAMERA_SPEED = 1.0f;
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
		default:
			break;
		}		
	}
	if (_inputManager.isKeyPressed(SDLK_w))
		sid.moveUP();
		//_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));

	if (_inputManager.isKeyPressed(SDLK_s))
		sid.moveDOWN();
		//_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
		
	if (_inputManager.isKeyPressed(SDLK_a))
		sid.moveLEFT();
		//_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		
	if (_inputManager.isKeyPressed(SDLK_d))
		sid.moveRIGHT();
		//_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));

	if (_inputManager.isKeyPressed(SDLK_UP))
		rahul.moveUP();
	//_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));

	if (_inputManager.isKeyPressed(SDLK_DOWN))
		rahul.moveDOWN();
	//_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));

	if (_inputManager.isKeyPressed(SDLK_LEFT))
		rahul.moveLEFT();
	//_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));

	if (_inputManager.isKeyPressed(SDLK_RIGHT))
		rahul.moveRIGHT();
	//_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
		
	if (_inputManager.isKeyPressed(SDLK_q))
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
		
	if (_inputManager.isKeyPressed(SDLK_e))
		_camera.setScale(_camera.getScale() - SCALE_SPEED);		
	
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	//use the first texture
	glActiveTexture(GL_TEXTURE0);

	//send unifrom varibales
	GLint textureLocation = _colorProgram.getUnifromLocation("mySampler");
	glUniform1i(textureLocation, 0);

	//GLint timeLocation = _colorProgram.getUnifromLocation("time");
	//glUniform1f(timeLocation, _time);

	GLint pLocation =_colorProgram.getUnifromLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation,1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();
	//do the drawing
	
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Color color = { 255,255,255,255 };

	//Background
	glm::vec4 bgPos(-_screenWidth/2,-_screenHeight/2,_screenWidth, _screenHeight);
	static GLTexture backGroundTexture = ResourceManager::getTexture("../Harry/Textures/harryPotter/Background/34.png");

	_spriteBatch.draw(bgPos, uv, backGroundTexture.id, -10.0f, color);
	rahul.draw(_spriteBatch);
	sid.draw(_spriteBatch);
	
	//std::cout << backGroundTexture.id<<std::endl;

	//characters
	
	
	

	/*
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBatch);
	} */
	
	_spriteBatch.end();
	_spriteBatch.renderBatch();	
	

	//unbind
	glBindTexture(GL_TEXTURE_2D,0);
	_colorProgram.unuse();

	_window.swapBuffer();
}
