#include "MainGame.h"
#include "Error.h"
#include <iostream>
#include"ResourceManager.h"
#include "Character.h"

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
	_fpsLimiter.init(_maxFPS);
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
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
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

		/*Use when we need to display fps 
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
		std::cout << _fps << std::endl;
		frameCounter = 0;
		} */
		
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
	if(_inputManager.isKeyPressed( SDLK_w))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));

	if (_inputManager.isKeyPressed(SDLK_s))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
		
	if (_inputManager.isKeyPressed(SDLK_a))
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		
	if (_inputManager.isKeyPressed(SDLK_d))
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
		
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
	static GLTexture backGroundTexture = ResourceManager::getTexture("Textures/harryPotter/Background/34.png");
	_spriteBatch.draw(bgPos, uv, backGroundTexture.id, -10.0f, color);

	//character
	glm::vec4 pos(0.0f, 0.0f, 50.0f, 100.0f);	
	static GLTexture texture = ResourceManager::getTexture("Textures/harryPotter/Harry/harry.png");
	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBatch);
	}
	
	_spriteBatch.end();
	_spriteBatch.renderBatch();	
	

	//unbind
	glBindTexture(GL_TEXTURE_2D,0);
	_colorProgram.unuse();

	_window.swapBuffer();
}
