#pragma once
class FpsLimiter
{
public:
	FpsLimiter();
	void init(float maxFPS);
	void begin();
	float end();
	void setMaxFPS(float maxFPS);
private:
	void calculateFPS();

	float _fps;
	float _frameTime;
	float _maxFPS;
	unsigned int _startTicks;

};