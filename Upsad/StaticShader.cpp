#include "StaticShader.h"

StaticShader::StaticShader()
{
	//Load Vertex-Shader
	vertexID=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexSource, NULL);
	glCompileShader(vertexID);

	GLint stat;
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &stat);
	if (stat == GL_FALSE) {
		GLint length;
		glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &length);

		GLchar* log;
		log = (GLchar*)malloc(length);

		glGetShaderInfoLog(vertexID, length, &length, log);
		std::cerr << "Error: Compile Vertex-Shader..." << std::endl;
		std::cerr << log << std::endl;
		free(log);
		throw std::runtime_error("Failed to Compile Vertex-Shader.");
	}
	//Load Fragment-Shader

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentSource, NULL);
	glCompileShader(fragmentID);

	stat=NULL;
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &stat);
	if (stat == GL_FALSE) {
		GLint length;
		glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &length);

		GLchar* log;
		log = (GLchar*)malloc(length);

		glGetShaderInfoLog(fragmentID, length, &length, log);
		std::cerr << "Error: Compile Fragment-Shader..." << std::endl;
		std::cerr << log << std::endl;
		free(log);
		throw std::runtime_error("Failed to Compile Fragment-Shader.");
	}
	programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);

	glBindAttribLocation(programID, 0, "pos");
	//glBindAttribLocation(programID, 1, "uv");

	glLinkProgram(programID);

	stat = NULL;
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


StaticShader::~StaticShader()
{
}
