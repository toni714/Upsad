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
	vec4 result_color=vec4(diffuse, 1.0)*texture(textureSampler, uv_frag);
	float nColors=32;
	result_color.x=max(floor(result_color.x*nColors)/nColors, 0.02);
	result_color.y=max(floor(result_color.y*nColors)/nColors, 0.02);
	result_color.z=max(floor(result_color.z*nColors)/nColors, 0.02);
	
	gl_FragColor=result_color;
}