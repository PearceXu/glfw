#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>
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
public:
	// ��������ȡ��������ɫ��
	explicit Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
};

#endif // !SHADER_H;
