#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Light.h"

class StaticShader :public ShaderProgram
{
private:
	const std::string vertexFile = "shader.vert";
	const std::string fragmentFile = "shader.frag";
	GLint location_modelMatrix;
	GLint location_viewMatrix;
	GLint location_projectionMatrix;
	GLint location_lightPos;
	GLint location_lightColor;

	void bindAttributes();
public:
	StaticShader();
	~StaticShader();
	virtual void getAllUniformLocations();
	void loadModelMatrix(const glm::mat4& mat);
	void loadProjectionMatrix(const glm::mat4& mat);
	void loadLight(const Light& light);
};
