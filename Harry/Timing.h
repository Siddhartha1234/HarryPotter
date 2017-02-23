#pragma once
class FpsLimiter
{
public:
	FpsLimiter();
	void begin();
	float end();
	void setMaxFPS(float maxFPS);
private:
	void calculateFPS();

	float m_fps;
	float m_frameTime;
	float m_maxFPS;
	unsigned int m_startTicks;

};