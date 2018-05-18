#include "StaticShader.h"

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

StaticShader::~StaticShader()
{
}

void StaticShader::getAllUniformLocations()
{
	start();
	location_modelMatrix = getUnifromLocation("modelMatrix");
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
	loadVec3(location_lightPos, light.getPos());
	loadVec3(location_lightColor, light.getColor());
}
