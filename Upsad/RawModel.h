#pragma once

#include <glad\glad.h>
#include "LimitBox.h"
struct RawModel
{
	RawModel(GLuint vaoID, int vertexCount, GLuint positionBufferID, GLuint uvBufferID, GLuint normalBufferID, LimitBox bounding)
		:vaoID(vaoID), vertexCount(vertexCount), positionBufferID(positionBufferID), uvBufferID(uvBufferID), normalBufferID(normalBufferID), bounding(bounding){}
	const GLuint vaoID;
	const int vertexCount;
	const GLuint positionBufferID;
	const GLuint uvBufferID;
	const GLuint normalBufferID;
	const LimitBox bounding;

	~RawModel();
};
