#version 400
#define MAX_NUM_LIGHTS 30
in vec3 normal;
in vec3 f_pos;
in vec2 TexCoord;
out vec4 frag_colour;

struct Material {
	sampler2D texture;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	bool haveTexture;
};

struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight {
	vec3 position;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct LightsInfo{
	DirLight dirLight;
	PointLight pointLights[MAX_NUM_LIGHTS];
	SpotLight spotLights[MAX_NUM_LIGHTS];
	int numPLights;
	int numSLights;
};
uniform Material material;
uniform LightsInfo lights;
uniform vec3 campos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 ambient;
	vec3 diffuse;
	if(material.haveTexture){
		ambient = light.ambient * vec3(texture(material.texture, TexCoord));
		diffuse = light.diffuse * diff * vec3(texture(material.texture, TexCoord));
	}else{
		ambient = light.ambient * material.ambient;
		diffuse = light.diffuse * diff * material.diffuse;
	}
	vec3 specular = light.specular * spec * material.specular;
	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
	light.quadratic * (distance * distance));
	vec3 ambient;
	vec3 diffuse;
	if(material.haveTexture){
		ambient = light.ambient * vec3(texture(material.texture, TexCoord));
		diffuse = light.diffuse * diff * vec3(texture(material.texture, TexCoord));
	}else{
		ambient = light.ambient * material.ambient;
		diffuse = light.diffuse * diff * material.diffuse;
	}
	vec3 specular = light.specular * spec * material.specular;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 result;
	float theta = dot(lightDir, normalize(-light.direction));
	if (theta > light.cutOff)
	{
		vec3 ambient;
		if(material.haveTexture){
			ambient = light.ambient * vec3(texture(material.texture, TexCoord));
		}else{
			ambient = light.ambient * material.ambient;
		}
		vec3 norm = normalize(normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse;
		if(material.haveTexture){
			diffuse = light.diffuse * diff * vec3(texture(material.texture, TexCoord));
		}else{
			diffuse = light.diffuse * diff * material.diffuse;
		}		
		vec3 viewDir = normalize(campos - fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * material.specular;
		float distance = length(light.position - fragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic* (distance * distance));
		diffuse *= attenuation;
		specular *= attenuation;
		result = ambient + diffuse + specular;
	}
	else
	{
		if(material.haveTexture){
			result = light.ambient * vec3(texture(material.texture, TexCoord));
		}else{
			result = light.ambient * material.ambient;
		}	
	}
	return result;
}

void main () {
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(campos - f_pos);
	vec3 result = CalcDirLight(lights.dirLight, norm, viewDir);
	for (int i = 0; i < lights.numPLights; i++)
	result += CalcPointLight(lights.pointLights[i], norm, f_pos, viewDir);
	for (int i = 0; i < lights.numSLights; i++)
	result += CalcSpotLight(lights.spotLights[i], norm, f_pos, viewDir);
	frag_colour = vec4(result, 1.0);
}
