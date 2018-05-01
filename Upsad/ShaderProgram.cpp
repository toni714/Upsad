#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

GLuint ShaderProgram::loadShader(const GLchar * source, GLenum type)
{
	GLuint shaderID;
	shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	GLint stat;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &stat);
	if (stat == GL_FALSE) {
		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		GLchar* log;
		log = (GLchar*)malloc(length);

		glGetShaderInfoLog(shaderID, length, &length, log);
		std::cerr << "Error: Compile Shader..." << std::endl;
		std::cerr << log << std::endl;
		free(log);
		throw std::runtime_error("Failed to Compile Shader.");
	}
	return shaderID;
}

void ShaderProgram::bindAttribute(GLuint index, const GLchar * attribute)
{
	glBindAttribLocation(programID, index, attribute);
}

void ShaderProgram::bindAttributes()
{
}

void ShaderProgram::linkProgram()
{
	programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);


	bindAttributes();

	glLinkProgram(programID);

	GLint stat;
	glGetProgramiv(programID, GL_LINK_STATUS, &stat);
	if (stat == GL_FALSE) {
		GLint length;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);

		GLchar* log;
		log = (GLchar*)malloc(length);

		glGetProgramInfoLog(programID, length, &length, log);
		std::cerr << "Error: Link Shader-Program..." << std::endl;
		std::cerr << log << std::endl;
		free(log);
		throw std::runtime_error("Failed to Link Shader-Program.");
	}
}
