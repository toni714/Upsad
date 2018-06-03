#version 400

in vec3 pos;
in vec2 uv;
in vec3 normal;

out vec2 uv_frag;
out vec3 normal_frag;
out vec3 lightVector;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPos;

void main(void) {
	vec4 worldPos=modelMatrix*vec4(pos, 1.0);
	gl_Position = projectionMatrix*viewMatrix*worldPos;
	uv_frag=uv;
	normal_frag=(modelMatrix*vec4(normal, 0.0)).xyz;
	lightVector=lightPos-worldPos.xyz;
}