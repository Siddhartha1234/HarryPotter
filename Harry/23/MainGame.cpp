#include "MainGame.h"
#include "Error.h"
#include <iostream>

MainGame::MainGame():	_window(nullptr),
						_width(1024),
						_height(768),
						_gameState(GameState::PLAY),
						_time(0.0f),
						_maxFPS(60.0f)
{
	_camera.init(_width, _height);
}


MainGame::~MainGame()
{
}

void MainGame::initSystems()
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//avoids flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Create Window;
	_window=SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL);

	//Error Checking
	if (_window == nullptr)
		fatalError("SDL Window could not be created");

	//Creating context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
		fatalError("SDL_GL context could not be created");

	//Initialise GLEW
	GLenum error =glewInit();
	if (error != GLEW_OK)
		fatalError("Glew could not be initialised");

	std::cout << "**** OPEN GL Version: " << glGetString(GL_VERSION) << " ****"<<std::endl;

	//Giving Background Color
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);



	//set vsync
	SDL_GL_SetSwapInterval(0);

	initShaders();
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

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f,0.0f,_width/2, _width / 2, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(_width / 2, 0.0f, _width / 2, _width / 2, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	gameLoop();

}

void MainGame::gameLoop()
{
	while (_gameState!=GameState::EXIT)
	{
		//used for frame time measuring
		float startTicks = SDL_GetTicks();


		processInput();
		_time += 0.01f;

		_camera.update();
		drawGame();
		calculateFPS();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks)
			SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	const float CAMERA_SPEED = 5.0f;
	const float SCALE_SPEED = 0.01f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
				break;
			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
				break;
			case SDLK_a:
				_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED,0.0));
				break;
			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED,0.0));
				break;
			case SDLK_q:
				_camera.setScale(_camera.getScale() + SCALE_SPEED );
				break;
			case SDLK_e:
				_camera.setScale(_camera.getScale() -SCALE_SPEED);
				break;
			default:
				break;
			}
		default:
			break;
		}		
	}
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

	GLint timeLocation = _colorProgram.getUnifromLocation("time");
	glUniform1f(timeLocation, _time);

	GLint pLocation =_colorProgram.getUnifromLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation,1, GL_FALSE, &(cameraMatrix[0][0]));

	for (unsigned int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}
	

	//unbind
	glBindTexture(GL_TEXTURE_2D,0);
	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}
void MainGame::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;
	


	static float prevTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();
	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame++%NUM_SAMPLES]=_frameTime;

	int count;
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0.0f;

	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage != 0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = 60.0f;	//default faulty value

	prevTicks = currentTicks;
}