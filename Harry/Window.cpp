#include "Window.h"
#include "Error.h"
#include <iostream>



Window::Window()
{
}


Window::~Window()
{
}

int Window::createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (currentFlags & INVISIBLE)
		flags |= SDL_WINDOW_HIDDEN;
	if (currentFlags & FULLSCREEN)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (currentFlags & BORDERLESS)
		flags |= SDL_WINDOW_BORDERLESS;


	//Create Window;
	m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

	//Error Checking
	if (m_sdlWindow == nullptr)
		fatalError("SDL Window could not be created");

	//Creating context
	SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
	if (glContext == nullptr)
		fatalError("SDL_GL context could not be created");

	//Initialise GLEW
	GLenum error = glewInit();
	if (error != GLEW_OK)
		fatalError("Glew could not be initialised");

	std::cout << "**** OPEN GL Version: " << glGetString(GL_VERSION) << " ****" << std::endl;

	//Giving Background Color
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//set vsync
	SDL_GL_SetSwapInterval(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	

	return 0;
}
void  Window::swapBuffer()
{
	SDL_GL_SwapWindow(m_sdlWindow);

}