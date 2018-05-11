#version 400

in  vec3 pos;

uniform mat4 MVP;

out vec3 out_color;

void main(void) {
	gl_Position = MVP*vec4(pos, 1.0);
	out_color = vec3((pos.x+1)/2.0, (pos.y+1)/2.0, (pos.z+1)/2.0);
}