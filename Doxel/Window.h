#pragma once
#include <GLFW\glfw3.h>

#define DEFAULT_TITLE "Doxel Engine"

class Window
{
public:
	/*
	Create a window object.
	Note: this call doesn't initialize the window, it only creates the object.
	*/
	Window();
	/*
	Destroy the window, call dipose() instead.
	*/
	~Window();
	/*
	Initialize the window.
	Input:
		- int width - the width of the desired window.
		- int height - the height of the desired window.
		- char* title - the title of the desired window. will be set to DEFAULT_TITLE if empty.
	*/
	void init(int width, int height, char* title = DEFAULT_TITLE);
	/*
	This Function will dispose the window.
	Note: this doesn't terminate glfw, remember to call glfwTerminate you are no longer in need of glfw.
	*/
	void dispose();
	/*
	This function updates the window.
	* swap the buffers.
	* poll events.
	*/
	void update();

	/*
	This function will set the window to close.
	*/
	void setWindowClose();
	/*
	This function will return true when the window needs to close
	*/
	bool shouldWindowClose();
	/*
	This function will return the aspect ratio of the screen.
	*/
	float getAspectRatio() { return (float)(m_width / m_height); }

	GLFWwindow *getGlfwWindow() { return m_window; }

private:
	GLFWwindow* m_window = nullptr;
	int m_width = 0, m_height = 0;
	char* m_title;

};

