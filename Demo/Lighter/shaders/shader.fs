#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
uniform vec3 viewPos;
in vec2 outTextureCoord;

struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float cutoff;
	float outCutOff;

	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform Light light;

void main()
{
	// attenuation π‚æ‡¿Î¥´µ›À•ºı
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	//
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 spotDir = normalize(-light.direction);
	float theta = dot(spotDir,lightDir);
	float epsilon = light.cutoff - light.outCutOff;
	// π‚∫·œÚÀ•ºı
	float intensity = clamp((theta - light.outCutOff)/epsilon,0.0,1.0);
	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, outTextureCoord).rgb;	
	// diffuse
	vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = intensity * light.diffuse * diff * texture(material.diffuse,outTextureCoord).rgb;
	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = intensity * light.specular * spec *  texture(material.specular,outTextureCoord).rgb;  
	// result
	vec3 result = (ambient + diffuse + specular) * attenuation;
    FragColor = vec4(result, 1.0);
} 