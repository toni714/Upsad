#include "Keys.h"

Keys::Keys(const int& keyID) 
	:KEY_ID(keyID)
{
}

bool Keys::isPressed() const
{
	return glfwGetKey(WindowManager::getWindowReference(), KEY_ID);
}

const Keys Keys::FORWARD(GLFW_KEY_W);
const Keys Keys::BACKWARD(GLFW_KEY_S);
const Keys Keys::LEFT(GLFW_KEY_A);
const Keys Keys::RIGHT(GLFW_KEY_D);
const Keys Keys::TURN_LEFT(GLFW_KEY_Q);
const Keys Keys::TURN_RIGHT(GLFW_KEY_E);