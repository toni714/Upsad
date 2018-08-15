#include "Camera.h"

#include <glm/trigonometric.hpp>
#include "Keys.h"

void Camera::moveForward(const float & amount)
{
	position.x += amount*sin(-rotation.y);
	position.z += amount*(-cos(rotation.y));
}

void Camera::moveSideways(const float & amount)
{
	position.x += amount * cos(rotation.y);
	position.z += amount * (-sin(rotation.y));
}

void Camera::update() {
	if (Keys::FORWARD.isPressed()) {
		moveForward(0.1f);
	}
	if (Keys::BACKWARD.isPressed()) {
		moveForward(-0.1f);
	}
	if (Keys::LEFT.isPressed()) {
		moveSideways(-0.1f);
	}
	if (Keys::RIGHT.isPressed()) {
		moveSideways(0.1f);
	}
	if (Keys::TURN_LEFT.isPressed()) {
		rotation += glm::vec3(0, glm::radians(1.f), 0);
	}
	if (Keys::TURN_RIGHT.isPressed()) {
		rotation += glm::vec3(0, glm::radians(-1.f), 0);
	}
}