#include "OpenGLHelper.h"

GLuint OpenGLHelper::createVAO() {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	return vaoID;
}

GLuint OpenGLHelper::createVBO(GLenum target) {
	GLuint vboID;
	glGenBuffers(1, &vboID);
	return vboID;
}