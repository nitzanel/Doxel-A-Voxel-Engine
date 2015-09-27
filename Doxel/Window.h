#pragma once
#include <GLFW\glfw3.h>
class Window
{
public:
	Window(int width, int height, char* title);
	~Window();

	void update();


	void setWindowClose();
	bool shouldWindowClose();

	GLFWwindow *getGlfwWindow() { return m_window; }
private:
	GLFWwindow* m_window = nullptr;
	int m_width, m_height;
	char* m_title;

};

