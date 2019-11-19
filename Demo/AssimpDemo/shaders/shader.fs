#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
uniform vec3 viewPos;
//uniform sampler2D texture_diffuse1;

struct Material{
	vec3 ambient;
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
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
	// attenuation 光距离传递衰减
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	// ambient
	vec3 ambient = light.ambient *  texture(material.texture_diffuse1, TexCoords).rgb;
	// diffuse
	vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(-light.direction);// 平行光
	vec3 lightDir = normalize(light.position - FragPos);// 点光源
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1,TexCoords).rgb;
	// specular
    lightDir = normalize(light.position - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular  * spec *  texture(material.texture_specular1,TexCoords).rgb;  

	vec3 result = ( ambient + diffuse + specular);
	FragColor = vec4(result,1.0);
    //FragColor = texture(texture_diffuse1, TexCoords);
}