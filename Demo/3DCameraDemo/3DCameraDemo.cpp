// Triangle.cpp: 定义控制台应用程序的入口点。
//

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"

#include <Glm/glm.hpp>
#include <Glm/gtc/matrix_transform.hpp>
#include <Glm/gtc/type_ptr.hpp>


#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )


unsigned int mProgram;
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int texture;
unsigned int texture2;		
Shader* shader;



float vertices[] = {
	//下     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // 右上
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 右下
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // 左下
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f ,   // 左上

	// 上
	0.5f,  0.5f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // 右上
	0.5f, -0.5f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 右下
	-0.5f, -0.5f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // 左下
	-0.5f,  0.5f, 1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f ,   // 左上

	// 左
	-0.5f,  0.5f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,   // 左下
	-0.5f, -0.5f, 1.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f,    // 左上
	-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // 右下
	-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f ,  // 右上

	// 右
	0.5f,  0.5f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,   // 左下
	0.5f, -0.5f, 1.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f,    // 左上
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // 右下
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f ,  // 右上
	// 前
	-0.5f, -0.5f, 1.0f,   1.0f, 1.0f, 0.0f,  1.0f, 0.0f,     // 左上
	0.5f, -0.5f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // 左下
	0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 右上
	-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f ,  // 右下
	

	// 后
	-0.5f, 0.5f, 1.0f,   1.0f, 1.0f, 0.0f,  1.0f, 0.0f,     // 左上
	0.5f, 0.5f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // 左下
	0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 右上
	-0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f ,  // 右下
	};
unsigned int indices[] = {
	0, 1, 2, // first triangle
	0, 3, 2,  // second triangle

	4, 5, 6,
	4, 7, 6,

	8, 9, 10,
	8, 11,10,

	12,13,14,
	12,15,14,

	16,17,18,
	16,19,18,

	20,21,22,
	20,23,22
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


glm::vec3 camera_position = glm::vec3(0.0,0.0f,3.0f);
glm::vec3 camera_front = glm::vec3(0.0, 0.0f, -1.0f);
glm::vec3 camera_up = glm::vec3(0.0, 1.0f, 0.0f);
float speed = 0.01f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// 窗口事件
void processInput(GLFWwindow *window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	// 前
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera_position += camera_front * speed;
	}
	// 后
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera_position -= camera_front * speed;
	}
	// 左
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		// 向量叉乘获取垂直于两个向量的第三个向量
		camera_position -= glm::normalize(glm::cross(camera_front, camera_up)) * speed;
	}
	// 右
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera_position += glm::normalize(glm::cross(camera_front, camera_up)) * speed;
	}

	// 视野上
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{

	}
	// 视野下
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{

	}
	// 视野左(放大)
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{

	}
	// 视野右(缩小)
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{

	}

}
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera_front = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}
// 渲染
void render()
{
	// 背景色
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// 开启深度缓冲区
	glEnable(GL_DEPTH_TEST);
	// 清除颜色与深度缓冲
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 图形变换model
	glm::mat4 model,view,projection;
	//model = glm::rotate(model, glm::radians(00.0f), glm::vec3(0.0, 1.0, 0.0));
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0, 1.0, 0.0));
	GLint modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// 图形变换view
	float radius = 6.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
	GLint viewLoc = glGetUniformLocation(shader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// 图形变换projection
	projection = glm::perspective(glm::radians(fov), 200.0f / 150.0f, 0.1f, 100.0f);
	//projection = glm::ortho(0.0f, 200.0f, 0.0f, 150.0f, 0.1f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(shader->ID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		GLint modelLoc = glGetUniformLocation(shader->ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//draw	
	glBindVertexArray(0);
}


// 初始化
void init()
{

	//VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 位置指向
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 颜色指向
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 纹理
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 创建纹理1
	int width, height, channelinFile;
	unsigned char *data = stbi_load("imgs/container.jpg", &width, &height, &channelinFile, 0);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLint format = channelinFile == 1 ? GL_RED : channelinFile == 3 ? GL_RGB : channelinFile == 4 ? GL_RGBA : 0;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	// 创建纹理2
	data = stbi_load("imgs/awesomeface.png", &width, &height, &channelinFile, 0);
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1); // 在绑定纹理之前先激活纹理单元
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	format = channelinFile == 1 ? GL_RED : channelinFile == 3 ? GL_RGB : channelinFile == 4 ? GL_RGBA : 0;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// 图形变换
	//glm::mat4 trans;
	//trans = glm::rotate(trans, (float)glfwGetTime(),glm::vec3(0.0,0.0,1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	//GLint transformLoc = glGetUniformLocation(shader->ID,"transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

// 释放资源
void release()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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
	// 鼠标事件
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	// 滚轮事件
	glfwSetScrollCallback(window, scroll_callback);
	gladLoadGL(glfwGetProcAddress);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 编译顶点渲染器，片元着色器
	//Shader shader("shaders/shader.vs", "shaders/shader.fs");
	shader = new Shader("shaders/shader.vs", "shaders/shader.fs");
	shader->use();
	shader->setInt("outTexture", 0); // 或者使用着色器类设置
	shader->setInt("outTexture2", 1); // 或者使用着色器类设置

	init();

	// 创建着色器程序
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		glfwSwapBuffers(window);
		render();
	}
	delete shader;
	shader = NULL;
	release();
	glfwTerminate();
	return 0;
}

