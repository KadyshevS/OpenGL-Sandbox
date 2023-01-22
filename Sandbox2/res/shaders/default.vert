#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec2 inTexCoord;

out DATA
{
    vec3 dNormal;
	vec3 dColor;
	vec2 dTexCoord;
    mat4 dProjection;
} data_out;

uniform mat4 camMatrix;
uniform mat4 model;

uniform mat4 mTransform;

void main()
{
	gl_Position = model * mTransform * vec4(inPosition, 1.0f);
	data_out.dNormal = inNormal;
	data_out.dColor = inColor;
	data_out.dTexCoord = inTexCoord;
	data_out.dProjection = camMatrix;
}