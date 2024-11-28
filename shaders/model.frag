#version 410 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material{
	//sampler2D texture_diffuse;
	//sampler2D texture_specular;
    sampler2D diffuse;
	sampler2D specular;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

vec3 direction = vec3(-0.2f,-1.0f,-0.5f);

float constant = 1.0f;
float linear = 0.09f;
float quadratic = 0.032f;
float cutOff = cos(radians(12.5f));
float outerCutOff = cos(radians(17.5f));

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(lightDir, norm) ,0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0f) , 64.0f);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	// Attenuation
	float Distance = length(light.position - FragPos);
	float attenuation = 1.0f / (constant + linear * Distance + quadratic * pow(Distance ,2));

	ambient *= attenuation ;
	diffuse *= attenuation ;
	specular *= attenuation;

	
	vec3 result = (ambient  + diffuse + specular);

	FragColor =  vec4(result, 1.0f);
}
