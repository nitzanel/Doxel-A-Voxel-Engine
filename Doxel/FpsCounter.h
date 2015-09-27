#pragma once

class FpsCounter
{
public:
	FpsCounter();
	~FpsCounter();

	void start();
	void end();
	

private:
	double m_currentTime, m_lastTime;
	int m_numFrames = 0;
};

