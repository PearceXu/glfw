#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
uniform vec3 viewPos;
in vec2 outTextureCoord;
#define NR_POINT_LIGHTS 4
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
uniform SpotLight spotLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;


// function prototypes
vec3 caculatDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 caculatSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 caculatPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

	// properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = caculatDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += caculatPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
    result += caculatSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
} 

vec3 caculatDirLight(DirLight light,vec3 normal,vec3 viewDir)
{
  vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, outTextureCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTextureCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, outTextureCoord));
    return (ambient + diffuse + specular);
}

vec3 caculatSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
 vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, outTextureCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTextureCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, outTextureCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

vec3 caculatPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, outTextureCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTextureCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, outTextureCoord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}