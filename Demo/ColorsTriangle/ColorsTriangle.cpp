// Triangle.cpp: 定义控制台应用程序的入口点。
//

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <Glm/glm.hpp>
#include <iostream>



#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

}
unsigned int mProgram;
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
float vertices_rentangle_index[] = {
	-0.5f,-0.5f,0.0f,
	-0.5f,0.5f,0.0f,
	0.5f,0.5f,0.0f,
	0.5f,-0.5f,0.0f

};

float vertices_color_rentangle_index[] = {
	-0.5f,-0.5f,0.0f,  1.0f,0.0f,0.0f,1.0f,
	-0.5f,0.5f,0.0f,   0.0f,1.0f,0.0f,1.0f,
	0.5f,0.5f,0.0f,	   0.0f,0.0f,1.0f,1.0f,	
	0.5f,-0.5f,0.0f,    1.0f,1.0f,1.0f,1.0f

};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

float vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

float vertices_retangle[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};


const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

unsigned int vertexShader;

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 vColor;\n"
"void main()\n"
"{\n"
"   FragColor = vColor;\n"
"}\n\0";
unsigned int fragmentShader;

// 渲染
void render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	//use program
	glUseProgram(mProgram);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


	// 填充颜色
	int vColor = glGetUniformLocation(mProgram, "vColor");
	float time = glfwGetTime();
	float value = sin(time) / 2.0f + 0.5f;
	glUniform4f(vColor, 0.5f, value, 0, 1.0f);

	//draw
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);
	glBindVertexArray(0);

	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glBindVertexArray(0);
}
// 查询错误
void glGetShaderCompileError(int shaderId)
{
	int ret = -1;
	char info[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &ret);
	if (!ret)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, info);
		std::cout << "gl shader compile error:\n" << info << std::endl;
	}
}

// 查询链接错误
void glGetProgramCompileError(int program)
{
	int ret = -1;
	char info[512];
	glGetProgramiv(program, GL_LINK_STATUS, &ret);
	if (!ret)
	{
		glGetProgramInfoLog(program, 512, NULL, info);
		std::cout << "gl link shader error:\n" << info << std::endl;
	}
}

// 初始化渲染器
void initShader()
{
	// 创建着色器程序
	mProgram = glCreateProgram();

	// vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderCompileError(vertexShader);

	//fragment shader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderCompileError(fragmentShader);

	// link shader
	glAttachShader(mProgram, vertexShader);
	glAttachShader(mProgram, fragmentShader);
	glLinkProgram(mProgram);
	glGetProgramCompileError(mProgram);
	// 删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 填充颜色
	//glUseProgram(mProgram);


	//VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_retangle), vertices_retangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//EBO
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



}

// 释放资源
void release()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(200, 150, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL(glfwGetProcAddress);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 编译顶点渲染器，片元着色器
	initShader();
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		glfwSwapBuffers(window);
		render();
	}
	release();
	glfwTerminate();
	return 0;
}

