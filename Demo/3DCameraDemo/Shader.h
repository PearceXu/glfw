#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad\glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


class Shader
{
public:
	// 程序ID
	unsigned int ID;
	// colorshader
	ifstream mColorShader;
	ifstream mVertexShader;


	// 使用/激活程序
	void use();
	// uniform工具函数
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
public:
	// 构造器读取并构建着色器
	explicit Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
};

#endif // !SHADER_H;
