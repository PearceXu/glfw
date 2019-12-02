#pragma once

#ifndef  TEXTURE_H
#define  TEXTURE_H
#include <glad/gl.h>
#include "stb_image.h"
#include <iostream>
#include <assimp/Importer.hpp>


class Texture
{
public:
	Texture();
	~Texture();
public:
	std::string type;
	int textureId;
	aiString path;
public:
	static unsigned int loadTexture(const char* path);
};
#endif // ! TEXTURE;
