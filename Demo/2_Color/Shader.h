#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>
#include <Glm/glm.hpp>
#include <Glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


class Shader
{
public:
	// ����ID
	unsigned int ID;
	// colorshader
	ifstream mColorShader;
	ifstream mVertexShader;


	// ʹ��/�������
	void use();
	// uniform���ߺ���
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name,glm::mat4 matrix);
	void setVec3(const std::string &name,glm::vec3 vec);
public:
	// ��������ȡ��������ɫ��
	explicit Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
};

#endif // !SHADER_H;
