#pragma once

#include <glad\glad.h>
#include <vector>

class RawModel
{
private:
	GLuint vaoID;
	int vertexCount;

public:
	RawModel(GLuint vaoID, int vertexCount);
	~RawModel();//TODO delete vao + vbos and remove this model from Loader

	GLuint getVaoID() const;
	int getVertexCount() const;
};

