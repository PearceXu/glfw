#ifndef MODEL_H
#define MODEL_H
#include "Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model
{
public:
	/*  ����   */
	Model(const string* path);
	void Draw(Shader* shader);
private:
	/*  ģ������  */
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	/*  ����   */
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,string typeName);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

private:

};

#endif // !MODEL
