#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
	stop();
	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glDeleteProgram(programID);
}

void ShaderProgram::start()
{
	glUseProgram(programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
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

GLint ShaderProgram::getUnifromLocation(const GLchar * name)
{
	return glGetUniformLocation(programID, name);
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

//These are just to satisfy the linker (=0 dosen't work)

void ShaderProgram::bindAttributes()
{
}

void ShaderProgram::getAllUniformLocations()
{
}
