#version 460

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 oNormal;

uniform mat4 camMatrix;
uniform mat4 model;
uniform float outlining;
uniform vec3 outlineColor;

out vec4 outliningColor;

void main()
{
	vec3 crntPos = vec3( model * vec4(position + oNormal * outlining, 1.0f) );
	gl_Position = camMatrix * vec4(crntPos, 1.0f);
	outliningColor = vec4(outlineColor, 1.0f);
}