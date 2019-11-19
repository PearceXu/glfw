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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, outTextureCoord).rgb;	
	// diffuse
	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,outTextureCoord).rgb;
	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec *  texture(material.specular,outTextureCoord).rgb;  
	// result
	vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
	//FragColor = texture(material.diffuse,outTextureCoord);
} 