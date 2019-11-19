#version 330 core
out vec4 FragColor;
in vec3 outColor;
in vec2 outTextureCoord;
uniform sampler2D outTexture;
uniform sampler2D outTexture2;
void main()
{
   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   //FragColor = texture(outTexture,outTextureCoord);
   FragColor = mix(texture(outTexture,outTextureCoord),texture(outTexture2,outTextureCoord),0.2);
}