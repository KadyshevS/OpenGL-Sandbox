#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 2) in vec3 inNormal;

uniform mat4 camMatrix;
uniform mat4 model;
uniform float outlining;
uniform vec3 outlineColor;

out vec4 outliningColor;

void main()
{
	vec3 crntPos = vec3( model * vec4(inPos + inNormal * outlining, 1.0f) );
	gl_Position = camMatrix * vec4(crntPos, 1.0f);
	outliningColor = vec4(outlineColor, 1.0f);
}