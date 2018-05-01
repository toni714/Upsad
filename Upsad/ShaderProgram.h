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
	void linkProgram();
	virtual void bindAttributes();//all baseclasses need to overwrite this!!
public:
	ShaderProgram();
	~ShaderProgram();
	void start();
	void stop();

};

