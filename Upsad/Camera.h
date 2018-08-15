#pragma once

#include "Object3D.h"
#include <glm/trigonometric.hpp>
#include <iostream>

struct Camera : public Object3D{
	Camera(const glm::vec3& position, const glm::vec3& rotation) :Object3D(position, rotation) {}
	void moveForward(const float& amount);
	void moveSideways(const float& amount);
};