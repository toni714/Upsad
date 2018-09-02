#pragma once

#include <glad/glad.h>
#include <vector>
#include "Vertex.h"
#include "LimitBox.h"

struct ModelData {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	LimitBox bounding;
	ModelData(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const LimitBox& bounding)
		:vertices(vertices), indices(indices), bounding(bounding) {}
};