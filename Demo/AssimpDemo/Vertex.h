#ifndef VERTEX_H
#define VERTEX_H
#include <GLM\glm.hpp>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};
#endif