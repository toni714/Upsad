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
