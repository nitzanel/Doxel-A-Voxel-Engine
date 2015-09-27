#include "Window.h"
#include "EasyErrors.h"

Window::Window(int width, int height, char* title) : 
m_width(width),
m_height(height),
m_title(title)
{
	/*glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL */
	m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
	if (m_window == nullptr)
	{
		Debug_Log("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);


}


Window::~Window()
{
	glfwDestroyWindow(m_window);
	Debug_Log("Window Terminated")
	glfwTerminate();
}

void Window::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::setWindowClose()
{
	glfwSetWindowShouldClose(m_window,GL_TRUE);
	Debug_Log("Window set to close");
}

bool Window::shouldWindowClose()
{
	if (glfwWindowShouldClose(m_window) == 1)
	{
		return true;
	}
	else
	{
		return false; 
	}
}