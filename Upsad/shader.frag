#version 400

in vec2 uv_frag;

uniform sampler2D textureSampler;

out vec4 gl_FragColor;

void main(void) {
	gl_FragColor = texture(textureSampler, uv_frag);
}