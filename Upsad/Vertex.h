#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv_coordinates;
	glm::vec3 normal;
	Vertex(const glm::vec3& position, const glm::vec2& uv_coordinates, const glm::vec3& normal);
	bool operator==(const Vertex& other) const;
};