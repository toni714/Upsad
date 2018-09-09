#pragma once

#include <glad/glad.h>
#include <vector>
#include "Vertex.h"
#include "CollisionShape.h"

struct ModelData {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	const CollisionShape* bounding;
	ModelData(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const CollisionShape* bounding)
		:vertices(vertices), indices(indices), bounding(bounding) {}
};