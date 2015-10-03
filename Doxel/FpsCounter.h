#pragma once
/*
An fps counter class.
*/
class FpsCounter
{
public:
	/*
	Create a FpsCounter object.
	*/
	FpsCounter();
	/*
	Destroy a FpsCounter object.
	*/
	~FpsCounter();
	/*
	Start counting the fps.
	*/
	void start();
	/*
	calculate the fps and print it.
	*/
	void end();
	

private:
	double m_currentTime, m_lastTime;
	int m_numFrames = 0;
};

