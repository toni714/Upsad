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

GLuint OpenGLHelper::createTexture()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	return textureID;
}
