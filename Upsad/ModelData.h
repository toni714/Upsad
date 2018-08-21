#pragma once

#include <glad/glad.h>
#include <vector>
#include "Vertex.h"

struct ModelData {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	ModelData(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
		:vertices(vertices), indices(indices) {}
};