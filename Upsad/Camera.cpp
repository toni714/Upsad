#include "Camera.h"

#include <glm/trigonometric.hpp>
#include "Keys.h"
#include "CurrentGameStata.h"

glm::vec3 Camera::calculateForward(float amount)
{
	return position+glm::vec3(amount * sin(-rotation.y), position.y, amount * (-cos(rotation.y)));
}

glm::vec3 Camera::calculateRight(float amount)
{
	return position+glm::vec3(amount * cos(rotation.y), position.y, amount * (-sin(rotation.y)));;
}

void Camera::move() {
	if (Keys::FORWARD.isPressed()) {
		glm::vec3 next= calculateForward(0.1f);
		if (CurrentGameState::world->isSpaceFree(next)) {
			//__debugbreak();
			position = next;
		}
	}
	if (Keys::BACKWARD.isPressed()) {
		glm::vec3 next = calculateForward(-0.1f);
		if (CurrentGameState::world->isSpaceFree(next)) {
			position = next;
		}
	}
	if (Keys::LEFT.isPressed()) {
		glm::vec3 next = calculateRight(-0.1f);
		if (CurrentGameState::world->isSpaceFree(next)) {
			position = next;
		}
	}
	if (Keys::RIGHT.isPressed()) {
		glm::vec3 next = calculateRight(0.1f);
		if (CurrentGameState::world->isSpaceFree(next)) {
			position = next;
		}
	}
	if (Keys::TURN_LEFT.isPressed()) {
		rotation += glm::vec3(0, glm::radians(1.f), 0);
	}
	if (Keys::TURN_RIGHT.isPressed()) {
		rotation += glm::vec3(0, glm::radians(-1.f), 0);
	}
}

void Camera::update()
{
	move();
}
