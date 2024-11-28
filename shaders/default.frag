#version 410 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 ourColor;
in vec3 normal;
in vec3 fragPos;

struct Material{

	sampler2D texture_diffuse;
	//vec3 specular;
	sampler2D texture_specular;

	float shininess;
};
struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float quadratic;
	float linear;
	float constant;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

//uniform vec3 colors;
//uniform bool isTexture;
//uniform bool isColor;
uniform float shininess;
uniform float ambientStrength;
uniform int lightPower;


uniform sampler2D texture1;
uniform sampler2D texture_diffuse;


void main()
{
	// Ambient
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse, TexCoords));

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diffuseIntensity = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.texture_diffuse, TexCoords));

	//Specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
	//vec3 specular = light.specular * spec * material.specular;
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular, TexCoords));

	// Light Attenuation
	float Distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * Distance + light.quadratic * pow(Distance,lightPower));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);


	////////////////////////////////////////////////////////////////////
	/*if(isTexture && isColor)
		//FragColor = texture(texture1, TexCoords);
		FragColor = texture(texture1, TexCoords) * vec4(colors, 1.0f);
	else if(isTexture && !isColor)
		FragColor = texture(texture1, TexCoords);
	else if(!isTexture && isColor)
		FragColor = vec4(colors, 1.0f);
	else
		FragColor = vec4(1.0f);*/
}