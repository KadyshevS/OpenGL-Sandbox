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
// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(gNormal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	if (texture(diffuse0, gTexCoord).a < 0.1)
		discard;

	fragColor = (texture(diffuse0, gTexCoord) * (diffuse * inten + ambient) + texture(specular0, gTexCoord).r * specular * inten) * lightColor;
	
//	Fog effect (depth buffer)
//	vec4 pointLight = (texture(diffuse0, gTexCoord) * (diffuse * inten + ambient) + texture(specular0, gTexCoord).r * specular * inten) * lightColor;
//	float depth = logisticDepth(gl_FragCoord.z, 0.9f, 3.0f);
//	fragColor = pointLight * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
}