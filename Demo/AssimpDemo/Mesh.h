#ifndef MESH_H
#define MESH_H
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
using namespace std;
class Mesh
{
public:
	Mesh();
	~Mesh();

public:
	/*  ��������  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	/*  ����  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader* shader);
private:
	/*  ��Ⱦ����  */
	unsigned int VAO, VBO, EBO;
	/*  ����  */
	void setupMesh();

};
#endif // !MESH
