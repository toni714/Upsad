#include "RawModel.h"



RawModel::RawModel(GLuint vaoID, int vertexCount)
	:vaoID(vaoID),vertexCount(vertexCount)
{
}

RawModel::~RawModel()
{
}

GLuint RawModel::getVaoID()
{
	return vaoID;
}

int RawModel::getVertexCount()
{
	return vertexCount;
}
