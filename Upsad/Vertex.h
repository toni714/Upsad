#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <vector>

class Vertex {
public:
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 uvCoord;

	Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uvCoord)
		:pos(pos), normal(normal), uvCoord(uvCoord)
	{}

	bool operator==(const Vertex &other) const {
		return pos == other.pos&&uvCoord == other.uvCoord&&normal == other.normal;
	}

};

namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const &vert) const {
			size_t h1 = hash<glm::vec3>()(vert.pos);
			size_t h2 = hash<glm::vec2>()(vert.uvCoord);
			size_t h3 = hash<glm::vec3>()(vert.normal);

			return ((h1 ^ (h2 << 1)) >> 1) ^ h3;
		}
	};
}