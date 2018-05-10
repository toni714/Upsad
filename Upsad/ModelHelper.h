#pragma once

#include <glad\glad.h>
#include <vector>

#include "RawModel.h"

class ModelHelper {
private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	GLuint createVAO();
	GLuint createVBO(const GLenum& target);
	template<typename T>
	void bufferData(std::vector<T> data, const int& attribute, const int& dimensions, const GLenum& type);
public:
	RawModel * loadToVAO(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
	~ModelHelper();
};