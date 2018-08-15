#include "StaticShader.h"

#include <glm/gtc/matrix_transform.hpp>

void StaticShader::bindAttributes()
{
	bindAttribute(0, "pos");
	bindAttribute(1, "uv");
	bindAttribute(2, "normal");
}

StaticShader::StaticShader()
	:ShaderProgram("shader.vert", "shader.frag")
{
	getAllUniformLocations();
}

void StaticShader::getAllUniformLocations()
{
	start();
	location_modelMatrix = getUnifromLocation("modelMatrix");
	location_viewMatrix = getUnifromLocation("viewMatrix");
	location_projectionMatrix = getUnifromLocation("projectionMatrix");
	location_lightPos = getUnifromLocation("lightPos");
	location_lightColor = getUnifromLocation("lightColor");
}

void StaticShader::loadModelMatrix(const glm::mat4& mat)
{
	loadMatrix(location_modelMatrix, mat);
}

void StaticShader::loadProjectionMatrix(const glm::mat4 & mat)
{
	loadMatrix(location_projectionMatrix, mat);
}

void StaticShader::loadLight(const Light & light)
{
	loadVec3(location_lightPos, light.position);
	loadVec3(location_lightColor, light.color);
}

void StaticShader::loadCamera(const Camera & camera)
{
	start();//TODO shader always needs to be started for this;
	glm::mat4 view=glm::mat4(1);
	glm::vec3 rotation = -camera.rotation;
	view = glm::rotate(view, rotation.x, glm::vec3(1, 0, 0));
	view = glm::rotate(view, rotation.y, glm::vec3(0, 1, 0));
	view = glm::rotate(view, rotation.z, glm::vec3(0, 0, 1));
	view = glm::translate(view, -camera.position);
	loadMatrix(location_viewMatrix, view);

}
