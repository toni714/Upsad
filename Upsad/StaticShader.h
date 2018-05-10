#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "ShaderProgram.h"

class StaticShader:public virtual ShaderProgram
{
private:
	const GLchar* vertexSource=
		"#version 400\n"
		"in  vec3 pos;\n"
		"uniform mat4 MVP;\n"
		"out vec3 out_color;\n"
		"void main(void) {\n"
		"	gl_Position = MVP*vec4(pos, 1.0);\n"
		"	out_color = vec3((pos.x+1)/2.0, (pos.y+1)/2.0, (pos.z+1)/2.0);\n"
		"}"
		;
	const GLchar* fragmentSource=
		"#version 400\n"
		"in  vec3 out_color;\n"
		"out vec4 gl_FragColor;\n"
		"void main(void) {\n"
		"	gl_FragColor = vec4(out_color, 1.0);\n"
		"}"
		;
	GLint location_MVP;
	void bindAttributes();
public:
	StaticShader();
	~StaticShader();
	void getAllUniformLocations();
	void loadMVPMatrix(const glm::mat4& mvp);
};

