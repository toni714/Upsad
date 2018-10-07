#pragma once

#include <glad\glad.h>
struct RawModel
{
	RawModel(GLuint vaoID, int vertexCount, GLuint positionBufferID, GLuint uvBufferID, GLuint normalBufferID)
		:vaoID(vaoID), vertexCount(vertexCount), positionBufferID(positionBufferID), uvBufferID(uvBufferID), normalBufferID(normalBufferID){}
	const GLuint vaoID;
	const int vertexCount;
	const GLuint positionBufferID;
	const GLuint uvBufferID;
	const GLuint normalBufferID;

	~RawModel();
};
