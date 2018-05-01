#pragma once

#include<glad\glad.h>

#include "ShaderProgram.h"

class StaticShader:public virtual ShaderProgram
{
private:
	
	const GLchar* vertexSource=
		"#version 330\n"
		"in  vec3 pos;\n"
		"out vec3 out_color;\n"
		"void main(void) {\n"
		"	gl_Position = vec4(pos, 1.0);\n"
		"	out_color = vec3(1.0, 1.0, 1.0);\n"
		"}"
		;
	const GLchar* fragmentSource=
		"#version 330\n"
		"in  vec3 out_color;\n"
		"out vec4 gl_FragColor;\n"
		"void main(void) {\n"
		"	gl_FragColor = vec4(out_color, 1.0);\n"
		"}"
		;

	void bindAttributes();
public:
	StaticShader();
	~StaticShader();
};

