#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv_coordinates;
	glm::vec3 normal;
	Vertex(const glm::vec3& position, const glm::vec2& uv_coordinates, const glm::vec3& normal)
		:position(position), uv_coordinates(uv_coordinates), normal(normal)
	{
	}
	bool operator==(const Vertex& other) const {
		return other.position == position && other.uv_coordinates == uv_coordinates && other.normal == normal;
	}
};