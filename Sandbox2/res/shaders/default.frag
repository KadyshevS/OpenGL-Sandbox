#version 330 core
	
in vec3 fragColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D tex0;

void main()
{
	color = texture(tex0, texCoord);
}