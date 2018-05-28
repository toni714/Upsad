#pragma once

#include <glad\glad.h>
#include <vector>

class RawModel
{
private:
	GLuint vaoID;
	int vertexCount;
	RawModel(const GLuint& vaoID, const int& vertexCount);
public:
	RawModel() = delete;
	static RawModel* loadFromOBJ(const char* filename);
	static RawModel* createModel(const GLuint& vaoID, const int& vertexCount);
	~RawModel();//TODO delete vao + vbos and remove this model from Loader

	GLuint getVaoID() const;
	int getVertexCount() const;
};
