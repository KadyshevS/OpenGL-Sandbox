#version 330 core
	
in vec2 texCoord;
in vec3 oNormal;
in vec3 crntPos;

out vec4 fragColor;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.20f;

	vec3 normal = normalize(oNormal);
	vec3 lightDir = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
	float specular = specAmount * specularLight;

	fragColor = texture(tex0, texCoord) * lightColor*2 * (diffuse + ambient) + texture(tex1, texCoord).r * specular;
}