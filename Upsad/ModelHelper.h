#pragma once

#include <glad\glad.h>
#include <vector>

#include "RawModel.h"

class ModelHelper {
private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
public:
	RawModel * loadToVAO(std::vector<GLfloat> vertices);
	~ModelHelper();
};