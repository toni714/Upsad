#include "StaticShader.h"

void StaticShader::bindAttributes()
{
	bindAttribute(0, "pos");
}

StaticShader::StaticShader()
{
	vertexID = loadShader(vertexSource, GL_VERTEX_SHADER);
	fragmentID = loadShader(fragmentSource, GL_FRAGMENT_SHADER);
	linkProgram();
}


StaticShader::~StaticShader()
{
}

void StaticShader::getAllUniformLocations()
{
	location_MVP = getUnifromLocation("MVP");
}

void StaticShader::loadMVPMatrix(const glm::mat4& mvp)
{
	glUniformMatrix4fv(location_MVP, 1, GL_FALSE, glm::value_ptr(mvp));
}
