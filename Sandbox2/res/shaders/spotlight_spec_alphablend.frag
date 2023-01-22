#version 330 core
	
out vec4 fragColor;

in vec3 crntPos;
in vec3 gColor;
in vec3 gNormal;
in vec2 gTexCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

// ambient lighting
	float ambient = 0.20f;

// diffuse lighting
	vec3 normal = normalize(gNormal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(abs(dot(normal, lightDirection)), 0.0f);

// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	if (texture(diffuse0, gTexCoord).a < 0.1)
		discard;

	fragColor = (texture(diffuse0, gTexCoord) * (diffuse * inten + ambient) + texture(specular0, gTexCoord).r * specular * inten) * lightColor;
}