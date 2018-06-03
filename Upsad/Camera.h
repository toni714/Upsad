#pragma once

#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

class Camera {
private:
	glm::vec3 position;
	glm::vec3 rotation;
public:
	Camera(const glm::vec3& position, const glm::vec3 rotation);
	glm::vec3 getRotation()const;
	glm::vec3 getPosition()const;
	void rotateBy(const glm::vec3& rotation);
	void moveBy(const glm::vec3& movement);
	void moveForward(const float& amount);
	void moveSideways(const float& amount);
};