#version 330 core
	
layout (location = 0) in vec3 inPosition;

out vec4 color;

uniform mat4 model;
uniform mat4 camMatrix;
uniform vec4 lightColor;

void main()
{
	gl_Position = camMatrix * model * vec4(inPosition, 1.0);
	color = lightColor;
}