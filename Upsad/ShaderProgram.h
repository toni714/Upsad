#pragma once

#include <glad\glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>

#include "FileUtil.h"

class ShaderProgram
{
protected:
	GLuint vertexID;
	GLuint fragmentID;

	GLuint programID;

	static GLuint loadShader(const GLchar* source, GLenum type);
	void bindAttribute(GLuint index, const GLchar* attribute);
	GLint getUnifromLocation(const GLchar* name);
	void loadMatrix(GLint location, const glm::mat4& mat);
	void loadVec3(GLint location, const glm::vec3& vec);
	void linkProgram();
	virtual void bindAttributes();//all baseclasses need to overwrite this!!
	virtual void getAllUniformLocations();//all baseclasses need to overwrite this!!
public:
	ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);
	~ShaderProgram();
	void start();
	void stop();
};
