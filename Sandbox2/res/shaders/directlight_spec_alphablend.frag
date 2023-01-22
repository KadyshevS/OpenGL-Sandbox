#version 330 core
	
out vec4 fragColor;

in vec3 crntPos;
in vec3 gColor;
in vec3 gNormal;
in vec2 gTexCoord;

uniform sampler2D diffuse0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
// ambient lighting
	float ambient = 0.20f;

// diffuse lighting
	vec3 normal = normalize(gNormal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(abs(dot(normal, lightDirection)), 0.0f);

// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
	float specular = specAmount * specularLight;

	if (texture(diffuse0, gTexCoord).a < 0.1)
		discard;

	fragColor = (texture(diffuse0, gTexCoord) * (diffuse + ambient) + specular) * lightColor;
}