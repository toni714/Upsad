#pragma once

#include "Object3D.h"

struct Object3DScaled :public Object3D {
	Object3DScaled(const glm::vec3& position, const glm::vec3& rotation, float scale) :Object3D(position, rotation), scale(scale) {}
	float scale;
};