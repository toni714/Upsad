#include "RawModel.h"

RawModel::RawModel(GLuint vaoID, int vertexCount)
	:vaoID(vaoID),vertexCount(vertexCount)
{
}

RawModel::~RawModel()
{
}

GLuint RawModel::getVaoID()const
{
	return vaoID;
}

int RawModel::getVertexCount()const
{
	return vertexCount;
}
