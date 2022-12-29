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

vec4 pointLight()
{
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 1.0f;
	float b = 0.04f;
	float inten = 1.0f / (1 * dist * dist + b * dist + 1.0f);

	float ambient = 0.20f;

	vec3 normal = normalize(oNormal);
	vec3 lightDir = normalize(lightVec);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}
vec4 directionalLight()
{
	float ambient = 0.20f;

	vec3 normal = normalize(oNormal);
	vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse + ambient) + texture(tex1, texCoord).r * specular) * lightColor;
}
vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	float ambient = 0.20f;

	vec3 normal = normalize(oNormal);
	vec3 lightDir = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}

void main()
{	
	fragColor = pointLight();
}