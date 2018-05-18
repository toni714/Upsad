#version 400

in vec2 uv_frag;
in vec3 normal_frag;
in vec3 lightVector;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

out vec4 gl_FragColor;

void main(void) {
	//gl_FragColor=vec4(normal_frag, 1.0);
	
	vec3 unitNormal=normalize(normal_frag);
	vec3 unitLight=normalize(lightVector);

	float nDot1=dot(unitNormal, unitLight);
	float brightness=max(nDot1, 0);
	vec3 diffuse=brightness*lightColor;
	gl_FragColor=vec4(diffuse, 1.0)*texture(textureSampler, uv_frag);
}