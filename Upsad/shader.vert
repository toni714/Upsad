#version 400

in vec3 pos;
in vec2 uv;

uniform mat4 MVP;

out vec2 uv_frag;

void main(void) {
	gl_Position = MVP*vec4(pos, 1.0);
	uv_frag=uv;
}