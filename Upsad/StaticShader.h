#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FileUtil.h"
#include "ShaderProgram.h"

class StaticShader:public virtual ShaderProgram
{
private:
	const char* vertexFile="shader.vert";
	const char* fragmentFile="shader.frag";
	GLint location_MVP;
	void bindAttributes();
public:
	StaticShader();
	~StaticShader();
	void getAllUniformLocations();
	void loadMVPMatrix(const glm::mat4& mvp);
};

