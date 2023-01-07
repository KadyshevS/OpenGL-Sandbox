#version 460 core
	
layout (location = 0) in vec3 position;

out vec4 color;

uniform mat4 model;
uniform mat4 camMatrix;
uniform vec4 lightColor;

void main()
{
	gl_Position = camMatrix * model * vec4(position, 1.0);
	color = lightColor;
}