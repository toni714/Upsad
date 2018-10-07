#pragma once

#include "Object3D.h"
#include "ActiveObject.h"

struct Camera : public Object3D, public ActiveObject {
	Camera(const glm::vec3& position, const glm::vec3& rotation) :Object3D(position, rotation) {}
	glm::vec3 calculateForward(float amount);
	glm::vec3 calculateSideways(float amount);
	glm::vec3 getNextPosition();
	void update();
};