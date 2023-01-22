#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec2 inTexCoord;

out vec3 crntPos;
out vec3 Color;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 camMatrix;
uniform mat4 model;

uniform mat4 mTransform;

void main()
{
	crntPos = vec3(model * mTransform * vec4(inPosition, 1.0f));
	Color = inColor;
	Normal = inNormal;
	TexCoord = inTexCoord;
	gl_Position = camMatrix * model * vec4(crntPos, 1.0);
}