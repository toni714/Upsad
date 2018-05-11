#version 400

in  vec3 out_color;

out vec4 gl_FragColor;

void main(void) {
	gl_FragColor = vec4(out_color, 1.0);
}