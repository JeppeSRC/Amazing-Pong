#version 430 core
#define MAX_LIGHTS 20

layout (location = 0) out vec4 glColor;

uniform vec2 light_pos[MAX_LIGHTS];
uniform vec4 light_col[MAX_LIGHTS];
uniform float light_range[MAX_LIGHTS];
uniform float light_damper[MAX_LIGHTS];
uniform int totalLights = 0;
uniform bool tex = false;
uniform sampler2D sampler;

in vec3 vert_pos;
in vec2 texCoord;
in vec4 color;

void main() {

	
	vec4 lightCol = vec4(0, 0, 0, 0);
	if (totalLights == 0) lightCol = vec4(1, 1, 1, 1);
	
	for (int i = 0; i < totalLights; i++)
		lightCol += (light_col[i] * (light_range[i] / (length(vert_pos.xy - light_pos[i]) * light_damper[i])));
	
	if (!tex)
		glColor = color * lightCol;
	else
		glColor = texture2D(sampler, texCoord) * lightCol;

}