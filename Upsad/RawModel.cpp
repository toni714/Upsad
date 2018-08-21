#include "RawModel.h"

RawModel::~RawModel()
{
	glDeleteVertexArrays(1, &vaoID);
}