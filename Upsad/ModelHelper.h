#pragma once

#include <glad\glad.h>
#include <vector>

#include "RawModel.h"

class ModelHelper {
private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;
	GLuint createVAO();
	GLuint createVBO(const GLenum& target);
	template<typename T>
	void bufferData(std::vector<T> data, const int& attribute, const int& dimensions, const GLenum& type);
public:
	RawModel * loadToVAO(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
	GLuint loadTexture(GLuint width, GLuint height, uint8_t* data);
	~ModelHelper();
};