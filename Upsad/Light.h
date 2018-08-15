#pragma once

#include <glm/vec3.hpp>

struct Light {
	Light(const glm::vec3& position, const glm::vec3& color) :position(position), color(color) {}
	glm::vec3 position;
	glm::vec3 color;
};