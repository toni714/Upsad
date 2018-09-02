#include "Camera.h"

#include <glm/trigonometric.hpp>
#include "Keys.h"

glm::vec3 Camera::calculateForward(float amount)
{
	return glm::vec3(amount * sin(-rotation.y), position.y, amount * (-cos(rotation.y)));
}

glm::vec3 Camera::calculateSideways(float amount)
{
	return glm::vec3(amount * cos(rotation.y), position.y, amount * (-sin(rotation.y)));;
}

glm::vec3 Camera::getNextPosition() {
	//TODO return  projected next position
	glm::vec3 moveBy=glm::vec3(0,0,0);
	if (Keys::FORWARD.isPressed()) {
		moveBy += calculateForward(0.1f);
	}
	if (Keys::BACKWARD.isPressed()) {
		moveBy += calculateForward(-0.1f);
	}
	if (Keys::LEFT.isPressed()) {
		moveBy += calculateSideways(-0.1f);
	}
	if (Keys::RIGHT.isPressed()) {
		moveBy += calculateSideways(0.1f);
	}
	if (Keys::TURN_LEFT.isPressed()) {
		rotation += glm::vec3(0, glm::radians(1.f), 0);
	}
	if (Keys::TURN_RIGHT.isPressed()) {
		rotation += glm::vec3(0, glm::radians(-1.f), 0);
	}
	return (position + moveBy);
}

void Camera::update()
{
}
