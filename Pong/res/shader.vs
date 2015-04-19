#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 4) in vec4 colors;

uniform mat4 projection;
uniform mat4 model;

out vec3 vert_pos;
out vec2 texCoord;
out vec4 color;

void main() {

	
	gl_Position = projection * model * vec4(position, 1);
	vert_pos = (model * vec4(position, 1)).xyz;
	
	color = colors;
	texCoord = texCoords;
}