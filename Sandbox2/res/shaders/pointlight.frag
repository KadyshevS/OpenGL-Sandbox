#version 330 core
	
out vec4 fragColor;

in vec3 crntPos;
in vec3 oColor;
in vec3 oNormal;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

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
	vec3 normal = normalize(oNormal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	fragColor = (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + specular * inten) * lightColor;
//	fragColor = vec4(vec3(gl_FragColor.z), 1.0f);
}