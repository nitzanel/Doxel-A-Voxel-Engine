#pragma once

#include <unordered_map>
#include <glm\vec2.hpp>
#include <GLFW\glfw3.h>
#include "Window.h"
enum KEYS
{
	A, B, C, D, E, F, f, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
	ESC, TAB, LFET_SHIFT, LEFT_COTROL, LEFT_ALT, SPACE, RIGHT_ALT, RIGHT_CONTROL, RIGHT_SHIFT, ENTER, BACKSPACE,
	UP, DOWN, LEFT, RIGHT,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	MOUSE_RIGHT, MOUSE_MIDDLE, MOUSE_LEFT
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void init(GLFWwindow *window);
	void update();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	/// Returns true if the key is held down
	bool isKeyDown(unsigned int keyID);

	/// Returns true if the key was just pressed
	bool isKeyPressed(unsigned int keyID);

	//setters

	//getters
	glm::vec2 getCurrentMouseCoords() const { return m_currentMouseCoords; }
	glm::vec2 getlastMouseCoords() const { return m_lastMouseCoords; }



private:
	/// Returns true if the key is held down
	bool wasKeyDown(unsigned int keyID);
	void updateKeys();
	void updateMouse();
	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previousKeyMap;

	glm::vec2 m_currentMouseCoords;
	glm::vec2 m_lastMouseCoords;
	GLFWwindow* m_window;

};



