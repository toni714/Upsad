#pragma once

#include "Object3D.h"
#include "ActiveObject.h"

struct Camera : public Object3D,public ActiveObject{
	Camera(const glm::vec3& position, const glm::vec3& rotation) :Object3D(position, rotation) {}
	void moveForward(const float& amount);
	void moveSideways(const float& amount);
	void update();
};