#include "Timing.h"
#include <SDL\SDL.h>
FpsLimiter::FpsLimiter()
{

}
void FpsLimiter::begin()
{
	m_startTicks = SDL_GetTicks();
}
float FpsLimiter::end()
{
	calculateFPS();
	float frameTicks = SDL_GetTicks() - m_startTicks;
	if (1000.0f / m_maxFPS > frameTicks)
		SDL_Delay((Uint32)(1000.0f / m_maxFPS - frameTicks));
	return m_fps;
}
void FpsLimiter::setMaxFPS(float maxFPS)
{
	m_maxFPS = maxFPS;
}
void FpsLimiter::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;



	static float prevTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();
	m_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame++%NUM_SAMPLES] = m_frameTime;

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
		m_fps = 1000.0f / frameTimeAverage;
	else
		m_fps = 60.0f;	//default faulty value

	prevTicks = currentTicks;
}