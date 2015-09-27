#include "InputManager.h"



InputManager::InputManager()
{

}


InputManager::~InputManager()
{

}

void InputManager::init(GLFWwindow *window)
{

	m_window = window;
}

void InputManager::update()
{
	// Loop throug _keyMap using a for each loop, and copy it over to _previousKeyMap
	for (auto& it : _keyMap)
	{
		_previousKeyMap[it.first] = it.second;
	}
	updateMouse();
	updateKeys();
}

void InputManager::updateKeys()
{
	if (glfwGetKey(m_window, GLFW_KEY_0) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_0);
	}
	else
	{
		releaseKey(KEYS::NUM_1);
	}
	if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_1);
	}
	else
	{
		releaseKey(KEYS::NUM_1);
	}

	if (glfwGetKey(m_window, GLFW_KEY_2) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_2);
	}
	else
	{
		releaseKey(KEYS::NUM_2);
	}
	if (glfwGetKey(m_window, GLFW_KEY_3) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_3);
	}
	else
	{
		releaseKey(KEYS::NUM_3);
	}
	if (glfwGetKey(m_window, GLFW_KEY_4) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_4);
	}
	else
	{
		releaseKey(KEYS::NUM_4);
	}
	if (glfwGetKey(m_window, GLFW_KEY_5) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_5);
	}
	else
	{
		releaseKey(KEYS::NUM_5);
	}
	if (glfwGetKey(m_window, GLFW_KEY_6) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_6);
	}
	else
	{
		releaseKey(KEYS::NUM_6);
	}
	if (glfwGetKey(m_window, GLFW_KEY_7) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_7);
	}
	else
	{
		releaseKey(KEYS::NUM_7);
	}
	if (glfwGetKey(m_window, GLFW_KEY_8) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_8);
	}
	else
	{
		releaseKey(KEYS::NUM_8);
	}
	if (glfwGetKey(m_window, GLFW_KEY_9) == GLFW_PRESS)
	{
		pressKey(KEYS::NUM_9);
	}
	else
	{
		releaseKey(KEYS::NUM_9);
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		pressKey(KEYS::A);
	}
	else
	{
		releaseKey(KEYS::A);
	}
	if (glfwGetKey(m_window, GLFW_KEY_B) == GLFW_PRESS)
	{
		pressKey(KEYS::B);
	}
	else
	{
		releaseKey(KEYS::B);
	}
	if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS)
	{
		pressKey(KEYS::C);
	}
	else
	{
		releaseKey(KEYS::C);
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		pressKey(KEYS::D);
	}
	else
	{
		releaseKey(KEYS::D);
	}
	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
	{
		pressKey(KEYS::E);
	}
	else
	{
		releaseKey(KEYS::E);
	}
	if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
	{
		pressKey(KEYS::F);
	}
	else
	{
		releaseKey(KEYS::F);
	}
	if (glfwGetKey(m_window, GLFW_KEY_G) == GLFW_PRESS)
	{
		pressKey(KEYS::G);
	}
	else
	{
		releaseKey(KEYS::G);
	}
	if (glfwGetKey(m_window, GLFW_KEY_H) == GLFW_PRESS)
	{
		pressKey(KEYS::H);
	}
	else
	{
		releaseKey(KEYS::H);
	}
	if (glfwGetKey(m_window, GLFW_KEY_I) == GLFW_PRESS)
	{
		pressKey(KEYS::I);
	}
	else
	{
		releaseKey(KEYS::I);
	}	if (glfwGetKey(m_window, GLFW_KEY_J) == GLFW_PRESS)
	{
		pressKey(KEYS::J);
	}
	else
	{
		releaseKey(KEYS::J);
	}	if (glfwGetKey(m_window, GLFW_KEY_K) == GLFW_PRESS)
	{
		pressKey(KEYS::K);
	}
	else
	{
		releaseKey(KEYS::K);
	}
	if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS)
	{
		pressKey(KEYS::L);
	}
	else
	{
		releaseKey(KEYS::L);
	}
	if (glfwGetKey(m_window, GLFW_KEY_M) == GLFW_PRESS)
	{
		pressKey(KEYS::M);
	}
	else
	{
		releaseKey(KEYS::M);
	}
	if (glfwGetKey(m_window, GLFW_KEY_N) == GLFW_PRESS)
	{
		pressKey(KEYS::N);
	}
	else
	{
		releaseKey(KEYS::N);
	}
	if (glfwGetKey(m_window, GLFW_KEY_O) == GLFW_PRESS)
	{
		pressKey(KEYS::O);
	}
	else
	{
		releaseKey(KEYS::O);
	}
	if (glfwGetKey(m_window, GLFW_KEY_P) == GLFW_PRESS)
	{
		pressKey(KEYS::P);
	}
	else
	{
		releaseKey(KEYS::P);
	}
	if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		pressKey(KEYS::Q);
	}
	else
	{
		releaseKey(KEYS::Q);
	}
	if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
	{
		pressKey(KEYS::R);
	}
	else
	{
		releaseKey(KEYS::R);
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pressKey(KEYS::S);
	}
	else
	{
		releaseKey(KEYS::S);
	}
	if (glfwGetKey(m_window, GLFW_KEY_T) == GLFW_PRESS)
	{
		pressKey(KEYS::T);
	}
	else
	{
		releaseKey(KEYS::T);
	}
	if (glfwGetKey(m_window, GLFW_KEY_U) == GLFW_PRESS)
	{
		pressKey(KEYS::U);
	}
	else
	{
		releaseKey(KEYS::U);
	}
	if (glfwGetKey(m_window, GLFW_KEY_V) == GLFW_PRESS)
	{
		pressKey(KEYS::V);
	}
	else
	{
		releaseKey(KEYS::V);
	}
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pressKey(KEYS::W);
	}
	else
	{
		releaseKey(KEYS::W);
	}
	if (glfwGetKey(m_window, GLFW_KEY_X) == GLFW_PRESS)
	{
		pressKey(KEYS::X);
	}
	else
	{
		releaseKey(KEYS::X);
	}
	if (glfwGetKey(m_window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		pressKey(KEYS::Y);
	}
	else
	{
		releaseKey(KEYS::Y);
	}
	if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		pressKey(KEYS::Z);
	}
	else
	{
		releaseKey(KEYS::Z);
	}
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		pressKey(KEYS::ESC);
	}
	else
	{
		releaseKey(KEYS::ESC);
	}
	if (glfwGetKey(m_window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		pressKey(KEYS::TAB);
	}
	else
	{
		releaseKey(KEYS::TAB);
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		pressKey(KEYS::LFET_SHIFT);
	}
	else
	{
		releaseKey(KEYS::LFET_SHIFT);
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		pressKey(KEYS::LEFT_COTROL);
	}
	else
	{
		releaseKey(KEYS::LEFT_COTROL);
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		pressKey(KEYS::LEFT_ALT);
	}
	else
	{
		releaseKey(KEYS::LEFT_ALT);
	}
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		pressKey(KEYS::SPACE);
	}
	else
	{
		releaseKey(KEYS::SPACE);
	}
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
	{
		pressKey(KEYS::RIGHT_ALT);
	}
	else
	{
		releaseKey(KEYS::RIGHT_ALT);
	}
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
	{
		pressKey(KEYS::RIGHT_CONTROL);
	}
	else
	{
		releaseKey(KEYS::RIGHT_CONTROL);
	}
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
	{
		pressKey(KEYS::RIGHT_SHIFT);
	}
	else
	{
		releaseKey(KEYS::RIGHT_SHIFT);
	}
	if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		pressKey(KEYS::ENTER);
	}
	else
	{
		releaseKey(KEYS::ENTER);
	}
	if (glfwGetKey(m_window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
	{
		pressKey(KEYS::BACKSPACE);
	}
	else
	{
		releaseKey(KEYS::BACKSPACE);
	}
	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		pressKey(KEYS::UP);
	}
	else
	{
		releaseKey(KEYS::UP);
	}
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		pressKey(KEYS::DOWN);
	}
	else
	{
		releaseKey(KEYS::DOWN);
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		pressKey(KEYS::LEFT);
	}
	else
	{
		releaseKey(KEYS::LEFT);
	}
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		pressKey(KEYS::RIGHT);
	}
	else
	{
		releaseKey(KEYS::RIGHT);
	}
	if (glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_PRESS)
	{
		pressKey(KEYS::F1);
	}
	else
	{
		releaseKey(KEYS::F1);
	}
	if (glfwGetKey(m_window, GLFW_KEY_F2) == GLFW_PRESS)
	{
		pressKey(KEYS::F2);
	}
	else
	{
		releaseKey(KEYS::F2);
	}
	if (glfwGetKey(m_window, GLFW_KEY_F3) == GLFW_PRESS)
	{
		pressKey(KEYS::F3);
	}
	else
	{
		releaseKey(KEYS::F3);
	}
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		pressKey(KEYS::MOUSE_LEFT);
	}
	else
	{
		releaseKey(KEYS::MOUSE_LEFT);
	}
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		pressKey(KEYS::MOUSE_MIDDLE);
	}
	else
	{
		releaseKey(KEYS::MOUSE_MIDDLE);
	}
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		pressKey(KEYS::MOUSE_RIGHT);
	}
	else
	{
		releaseKey(KEYS::MOUSE_RIGHT);
	}

}
void InputManager::updateMouse()
{
	m_lastMouseCoords = m_currentMouseCoords;
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	m_currentMouseCoords.x = (float)x;
	m_currentMouseCoords.y = (float)y;
}
void InputManager::pressKey(unsigned int keyID)
{
	_keyMap[keyID] = true;

}
void InputManager::releaseKey(unsigned int keyID)
{
	_keyMap[keyID] = false;

}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end())
	{
		return it->second;
	}

	else
	{
		return false;
	}
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	// Check if it is pressed this frame, and not the last one
	if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
	{
		return true;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end())
	{
		return it->second;
	}
	else
	{
		return false;
	}
}







