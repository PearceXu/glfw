// Triangle.cpp: 定义控制台应用程序的入口点。
//

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <Glm/glm.hpp>
#include <Glm/gtc/matrix_transform.hpp>
#include <Glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "stb_image.h"
#include "Texture.h"

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
}

unsigned int VBO;
unsigned int Object_VAO;
unsigned int Light_VAO;
unsigned int EBO;

Shader* mObjectShader;
Shader* mLightShader;
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
};

int indices[] = {
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

glm::vec3 lightPos(0.0f, 0.0f, 1.3f);
glm::vec3 lightDirction(0.0f, 0.0f, -1.3f);
// positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};
// 渲染
void render()
{
	// 背景色
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
	glm::vec3 object_specular(0.5f, 0.5f, 0.5f);

	glm::vec3 light_ambient = lightColor * 0.2f;
	glm::vec3 light_diffuse = lightColor * 0.5f;
	glm::vec3 light_specular = glm::vec3(1.0f);

	float shining = 32.0f;

	mObjectShader->setMat4("model", model);
	mObjectShader->setMat4("view", view);
	mObjectShader->setMat4("projection", projection);

	mObjectShader->setVec3("viewPos", camera.camera_position);

	mObjectShader->setInt("material.diffuse", 1);
	mObjectShader->setInt("material.specular", 2);
	mObjectShader->setFloat("material.shininess", shining);
/////////////////////////////////////////////////
	mObjectShader->setVec3("light.ambient", light_ambient);
	mObjectShader->setVec3("light.diffuse", light_diffuse);
	mObjectShader->setVec3("light.specular", light_specular);
	mObjectShader->setVec3("light.direction", camera.camera_font);
	mObjectShader->setFloat("light.cutoff", glm::cos(glm::radians(12.5f)));//切光角
	mObjectShader->setFloat("light.outCutOff", glm::cos(glm::radians(17.5f)));//切光角outCutOff

																			  //light
	mObjectShader->setVec3("light.position", camera.camera_position);
	mObjectShader->setFloat("light.constant", 1.0f);
	mObjectShader->setFloat("light.linear", 0.09f);
	mObjectShader->setFloat("light.quadratic", 0.032);
//////////////////////////////////////////////////////////////
// directional light
	mObjectShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	mObjectShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	mObjectShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	mObjectShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	mObjectShader->setVec3("pointLights[0].position", pointLightPositions[0]);
	mObjectShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	mObjectShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	mObjectShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	mObjectShader->setFloat("pointLights[0].constant", 1.0f);
	mObjectShader->setFloat("pointLights[0].linear", 0.09);
	mObjectShader->setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	mObjectShader->setVec3("pointLights[1].position", pointLightPositions[1]);
	mObjectShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	mObjectShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	mObjectShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	mObjectShader->setFloat("pointLights[1].constant", 1.0f);
	mObjectShader->setFloat("pointLights[1].linear", 0.09);
	mObjectShader->setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	mObjectShader->setVec3("pointLights[2].position", pointLightPositions[2]);
	mObjectShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	mObjectShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	mObjectShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	mObjectShader->setFloat("pointLights[2].constant", 1.0f);
	mObjectShader->setFloat("pointLights[2].linear", 0.09);
	mObjectShader->setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	mObjectShader->setVec3("pointLights[3].position", pointLightPositions[3]);
	mObjectShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	mObjectShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	mObjectShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	mObjectShader->setFloat("pointLights[3].constant", 1.0f);
	mObjectShader->setFloat("pointLights[3].linear", 0.09);
	mObjectShader->setFloat("pointLights[3].quadratic", 0.032);
	// spotLight
	mObjectShader->setVec3("spotLight.position", camera.camera_position);
	mObjectShader->setVec3("spotLight.direction", camera.camera_font);
	mObjectShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	mObjectShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	mObjectShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	mObjectShader->setFloat("spotLight.constant", 1.0f);
	mObjectShader->setFloat("spotLight.linear", 0.09);
	mObjectShader->setFloat("spotLight.quadratic", 0.032);
	mObjectShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	mObjectShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
/////////////////////////////////////////////////////////

	//draw
	glBindVertexArray(Object_VAO);
	for (int i = 0; i < 10; i++) {
		glm::mat4 model_test;
		model_test = glm::translate(model_test, cubePositions[i]);
		float angle = 20.0f * i;
		model_test = glm::rotate(model_test, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		mObjectShader->setMat4("model", model_test);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 8);
	}

	//glDrawElements(GL_TRIANGLES,sizeof(indices), GL_UNSIGNED_INT,0);
	mLightShader->use();
	model = glm::translate(model, glm::vec3(2.0f, 0.2f, -2.0f));
	mLightShader->setMat4("model", model);
	mLightShader->setMat4("view", view);
	mLightShader->setMat4("projection", projection);
	mLightShader->setVec3("lightColor", lightColor);
	glBindVertexArray(Light_VAO);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 8);
	//glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
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
	mObjectShader = new Shader("shaders/shader.vs", "shaders/shader.fs");
	mLightShader = new Shader("shaders/light_shader.vs", "shaders/light_shader.fs");
	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//VAO
	glGenVertexArrays(1, &Object_VAO);
	glBindVertexArray(Object_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// texture 
	glActiveTexture(GL_TEXTURE1);
	unsigned int diffuseTexture = Texture::loadTexture("imgs/container.jpg");
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	// texture2
	glActiveTexture(GL_TEXTURE2);
	unsigned int specularTexture = Texture::loadTexture("imgs/container2_specular.png");
	glBindTexture(GL_TEXTURE_2D, specularTexture);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//vao
	glGenVertexArrays(1, &Light_VAO);
	glBindVertexArray(Light_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//EBO
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

// 释放资源
void release()
{
	glDeleteBuffers(1, &Light_VAO);
	glDeleteBuffers(1, &Object_VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
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
