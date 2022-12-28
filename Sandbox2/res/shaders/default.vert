#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 normal;

out vec2 texCoord;
out vec3 oNormal;
out vec3 crntPos;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(position, 1.0f));

	gl_Position = camMatrix * model * vec4(crntPos, 1.0);
	texCoord = tex;
	oNormal = normal;
}