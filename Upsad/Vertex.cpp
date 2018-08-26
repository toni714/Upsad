#include "Vertex.h"

Vertex::Vertex(const glm::vec3 & position, const glm::vec2 & uv_coordinates, const glm::vec3 & normal)
	:position(position), uv_coordinates(uv_coordinates), normal(normal)
{
}

bool Vertex::operator==(const Vertex& other) const {
	return other.position == position && other.uv_coordinates == uv_coordinates && other.normal == normal;
}