#pragma once

#include <glad\glad.h>
struct RawModel
{
	RawModel(const GLuint vaoID, const int vertexCount) :vaoID(vaoID), vertexCount(vertexCount) {}
	const GLuint vaoID;
	const int vertexCount;
	~RawModel();
};
