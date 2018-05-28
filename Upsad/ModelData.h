#pragma once

#include <glad/glad.h>
#include <vector>

struct ModelData {
	const std::vector<GLfloat> vertices;
	const std::vector<GLfloat> uvs;
	const std::vector<GLfloat> normals;
	const std::vector<GLuint> indices;
};