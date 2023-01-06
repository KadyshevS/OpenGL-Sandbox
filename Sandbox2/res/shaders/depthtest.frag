#version 330 core
	
out vec4 fragColor;

in vec3 crntPos;
in vec3 oColor;
in vec3 oNormal;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

float near = 0.1f;
float far = 10.f;

float linearizeDepth(float depth)
{
	return (2.0f * near * far) / (far + near - (depth * 2.0f - 1.0f) * (far - near));
}
float logisticDepth(float depth, float steepness, float offset)
{
	float zVal = linearizeDepth(depth);
	return ( 1 / ( 1 + exp(-steepness * (zVal - offset) ) ) );
}

void main()
{
// ambient lighting
	float ambient = 0.20f;

// diffuse lighting
	vec3 normal = normalize(oNormal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	vec4 lightSource = (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
	float depth = logisticDepth(gl_FragCoord.z, 0.8f, 3.0f);
	fragColor = lightSource * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
}