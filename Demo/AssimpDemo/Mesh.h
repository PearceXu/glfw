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
	/*  网格数据  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	/*  函数  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader* shader);
private:
	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;
	/*  函数  */
	void setupMesh();

};
#endif // !MESH
