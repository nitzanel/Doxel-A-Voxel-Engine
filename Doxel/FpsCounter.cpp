#include "FpsCounter.h"
#include "EasyErrors.h"
#include <GLFW\glfw3.h>
#define MS = 1000.0;

FpsCounter::FpsCounter() 
{

}

FpsCounter::~FpsCounter()
{

}
void FpsCounter::start()
{
	m_lastTime = glfwGetTime();
}

void FpsCounter::end()
{
	m_currentTime = glfwGetTime();
	m_numFrames++;

	if (m_currentTime - m_lastTime >= 1.0)
	{
		Debug_Log(1000.0 / (double)m_numFrames << " ms for each frame.");
		m_numFrames = 0;
		m_lastTime = glfwGetTime();
	}
}

