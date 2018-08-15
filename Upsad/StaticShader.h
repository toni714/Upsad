#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"
#include "Light.h"
#include "Camera.h"

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
	virtual void getAllUniformLocations();
	void loadModelMatrix(const glm::mat4& mat);
	void loadProjectionMatrix(const glm::mat4& mat);
	void loadLight(const Light& light);
	void loadCamera(const Camera& camera);
};
