#pragma once

#include "Vertex.h"
#include <unordered_map>

class OBJWrapper {
public:

	std::vector<Vertex> m_vertices = std::vector<Vertex>();
	std::vector<unsigned int> m_indices = std::vector<unsigned int>();

	OBJWrapper(const char* filename);

	std::vector<Vertex> getVertices();
	std::vector<unsigned int> getIndices();
};