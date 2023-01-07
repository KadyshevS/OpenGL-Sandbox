#version 460

in vec4 outliningColor;

out vec4 fragColor;

void main()
{
	fragColor = outliningColor;
}