#include "RawModel.h"

RawModel::~RawModel()
{
	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(1, &positionBufferID);
	glDeleteBuffers(1, &uvBufferID);
	glDeleteBuffers(1, &normalBufferID);
}