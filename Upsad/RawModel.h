#pragma once

#include <glad\glad.h>
#include "CollisionShape.h"
struct RawModel
{
	RawModel(GLuint vaoID, int vertexCount, GLuint positionBufferID, GLuint uvBufferID, GLuint normalBufferID, const CollisionShape* bounding)
		:vaoID(vaoID), vertexCount(vertexCount), positionBufferID(positionBufferID), uvBufferID(uvBufferID), normalBufferID(normalBufferID), bounding(bounding){}
	const GLuint vaoID;
	const int vertexCount;
	const GLuint positionBufferID;
	const GLuint uvBufferID;
	const GLuint normalBufferID;
	const CollisionShape* bounding;

	~RawModel();
};
