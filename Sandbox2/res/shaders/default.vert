#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 tex;

out vec3 crntPos;
out vec3 oColor;
out vec3 oNormal;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(position, 1.0f));
	oColor = color;
	oNormal = normal;
	texCoord = tex;
	gl_Position = camMatrix * model * vec4(crntPos, 1.0);
}