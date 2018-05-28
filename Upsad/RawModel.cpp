#include "RawModel.h"
#include "FileUtil.h"

RawModel::RawModel(const GLuint& vaoID, const int& vertexCount)
	:vaoID(vaoID), vertexCount(vertexCount)
{
}

RawModel * RawModel::loadFromOBJ(const char * filename)
{
	return ModelHelper::getModelFromFile(filename);
}

RawModel * RawModel::createModel(const GLuint & vaoID, const int & vertexCount)
{
	return new RawModel(vaoID, vertexCount);
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