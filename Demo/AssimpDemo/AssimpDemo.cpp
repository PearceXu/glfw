// Triangle.cpp: 定义控制台应用程序的入口点。
//

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include <GLM\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "stb_image.h"
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
float view_width = 400.0f, view_height = 300.0f;
Camera camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	view_width = width;
	view_height = height;
	glViewport(0, 0, width, height);
}
// timing
float deltaTime = 0.01f;
float lastFrame = 0.01f;
float lastX = view_width / 2.0f;
float lastY = view_height / 2.0f;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.lookAt(xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//camera.ProcessKeyboard(FORWARD, deltaTime);
		camera.moveFont();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//camera.ProcessKeyboard(BACKWARD, deltaTime);
		camera.moveBack();

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//camera.ProcessKeyboard(LEFT, deltaTime);
		camera.moveleft();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//camera.ProcessKeyboard(RIGHT, deltaTime);
		camera.moveRight();
	}

	if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS){
		camera.moveUp();
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera.moveDown();
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.moveUp();
	}
}

Model* modelObject = NULL;
Shader* mObjectShader;

// 渲染
void render()
{
	// 背景色
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_POINT_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mObjectShader->use();

	glm::mat4 model, view, projection;

	projection = glm::perspective(glm::radians(45.0f), view_width / view_height, 0.1f, 100.0f);
	view = camera.lookAt();
	//view = glm::lookAt(glm::vec3(1.2f, 1.0f, 5), glm::vec3(0, 0.0f, 0), glm::vec3(0, 1, 0));

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	//lightColor.x = sin(glfwGetTime() * 2.0f);
	//lightColor.y = sin(glfwGetTime() * 0.7f);
	//lightColor.z = sin(glfwGetTime() * 1.3f);

	glm::vec3 object_ambient(1.0f, 0.5f, 0.31f);
	glm::vec3 object_diffuse(1.0f, 0.5f, 0.31f);
	glm::vec3 object_specular(0.5f, 0.5f, 1.0f);

	glm::vec3 light_ambient = lightColor * 0.2f;
	glm::vec3 light_diffuse = lightColor * 0.5f;
	glm::vec3 light_specular = glm::vec3(1.0f);

	float shining = 32.0f;

	mObjectShader->setMat4("model", model);
	mObjectShader->setMat4("view", view);
	mObjectShader->setMat4("projection", projection);
	mObjectShader->setInt("material.shininess",32.0f);

	mObjectShader->setVec3("light.ambient", light_ambient);
	mObjectShader->setVec3("light.diffuse", light_diffuse);
	mObjectShader->setVec3("light.specular", light_specular);
	//mObjectShader->setVec3("light.direction", camera.camera_font);
	mObjectShader->setVec3("light.direction", glm::vec3(0.0f, 0.0f,-10.f));
	//mObjectShader->setVec3("light.position", camera.camera_position);
	mObjectShader->setVec3("light.position", glm::vec3(0.0f,0.0f,10.f));
	mObjectShader->setFloat("light.constant", 1.0f);
	mObjectShader->setFloat("light.linear", 0.09f);
	mObjectShader->setFloat("light.quadratic", 0.032);

	mObjectShader->setVec3("viewPos",camera.camera_position);

	modelObject->Draw(mObjectShader);
	
}

void initModle()
{
	const std::string path("res/nanosuit.obj");
	modelObject = new Model(&path);
}

// 初始化渲染器
void initShader()
{
	mObjectShader = new Shader("shaders/shader.vs", "shaders/shader.fs");

}

// 释放资源
void release()
{

}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(view_width, view_height, "OpenGl", NULL, NULL);
	// 鼠标事件
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	initModle();
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

