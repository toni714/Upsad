#pragma once

#include <vector>
#include <glad/glad.h>

namespace OpenGLHelper {
	GLuint createVAO();
	GLuint createVBO(GLenum target);
	GLuint createTexture();
	template<typename T>
	void bufferData(GLuint vaoID, GLuint bufferID, std::vector<T> data, int attribute, int dimensions, GLenum type)
	{
		glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(attribute);
		glVertexAttribPointer(attribute, dimensions, type, GL_FALSE, 0, nullptr);
		glDisableVertexAttribArray(attribute);
	}
}