#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex;

out vec3 fragColor;
out vec2 texCoord;

void main()
{
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);
	fragColor = color;
	texCoord = tex;
};