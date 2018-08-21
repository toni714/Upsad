#pragma once

#include <glm/vec3.hpp>

struct Object3D {
	Object3D(const glm::vec3& position, const glm::vec3& rotation) :position(position), rotation(rotation) {}
	glm::vec3 position;
	glm::vec3 rotation;
};