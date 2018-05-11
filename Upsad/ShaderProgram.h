#pragma once

#include <glad\glad.h>
#include <iostream>
#include <stdexcept>

class ShaderProgram
{
protected:
	GLuint vertexID;
	GLuint fragmentID;

	GLuint programID;

	static GLuint loadShader(const GLchar* source, GLenum type);
	void bindAttribute(GLuint index, const GLchar* attribute);
	GLint getUnifromLocation(const GLchar* name);
	void linkProgram();
	virtual void bindAttributes();//all baseclasses need to overwrite this!!
	virtual void getAllUniformLocations();//all baseclasses need to overwrite this!!
public:
	ShaderProgram();
	~ShaderProgram();
	void start();
	void stop();
};
