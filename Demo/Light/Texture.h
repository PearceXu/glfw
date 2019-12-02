#pragma once

#ifndef  TEXTURE
#define  TEXTURE
#include <glad/gl.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
public:
	Texture();
	~Texture();
public:
	static unsigned int loadTexture(const char* path);
};
#endif // ! TEXTURE;
