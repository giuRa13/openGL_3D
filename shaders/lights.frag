#version 410 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 normal;
in vec3 fragPos;

struct Material{

	sampler2D diffuse;
	vec3 specular;
	//sampler2D specular;

	float shininess;
};

struct DirectionalLight{
    vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float linear;
	float constant;
	float quadratic;
};
struct SpotLight{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float linear;
	float constant;
	float quadratic;

	float cutOff;
	float outerCutOff;
};

uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[4];
uniform SpotLight spotLight;
uniform vec3 viewPos;
uniform float shininess;
uniform float ambientStrength;

vec3 CalcDirLight(DirectionalLight light, vec3 norm, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fragpos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 fragpos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

	// Directional Light 
	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	// Point Light 
	//for(int i = 0; i < 4; i++)
	//	result += CalcPointLight(pointLights[i], norm ,fragPos, viewDir);
	
    // Spot Light 
	result += CalcSpotLight(spotLight,norm ,fragPos,viewDir);

	FragColor = vec4(result, 1.0f);

}


vec3 CalcDirLight(DirectionalLight light, vec3 norm, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse
    float diffuseIntensity = max(dot(norm, lightDir), 0.0f);
    // Specular
    vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * material.specular;

    return ambient + diffuse + specular;
}


vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fragpos, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.position - fragpos);
    // Diffuse
    float diffuseIntensity = max(dot(norm, lightDir), 0.0f);
    // Specular
    vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
    // Attenuation
    float Distance = length(light.position - fragpos);
	float attenuation = 1.0f / (light.constant + light.linear * Distance + light.quadratic * pow(Distance ,2));

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * material.specular;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

    return ambient + diffuse + specular;
}	


vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 fragpos, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.position - fragpos);
    // Diffuse
    float diffuseIntensity = max(dot(norm, lightDir), 0.0f);
    // Specular
    vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
    // Attenuation
    float Distance = length(light.position - fragpos);
	float attenuation = 1.0f / (light.constant + light.linear * Distance + light.quadratic * pow(Distance ,2));
    //Intensity
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0f,1.0f);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diffuseIntensity * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * material.specular;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

    return ambient + diffuse + specular;
}	