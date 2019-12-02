#ifndef CAMERA_H
#define CAMERA_H

#include <glad/gl.h>
#include <Glm/glm.hpp>
#include <Glm/gtc/matrix_transform.hpp>
#include <vector>

class Camera
{
public:
	Camera();
	void moveFont();
	void moveBack();
	void moveleft();
	void moveRight();

	void lookAt(float x,float y);

	void yawLeft();
	void yawRight();
	
	void pitchUp();
	void pitchDown();

	void rollClockWise();
	void rollinClockWise();
	glm::mat4 lookAt();

public:
	glm::vec3 camera_position;
	glm::vec3 camera_font;
	glm::vec3 camera_up;

	float mSpeed = 0.05;
	float mSenity = 0.1;
	float fov = 45.0;


	float pitch = 0.0f;
	float yaw = -90.0f;
	float roll = 0.0f;

	float lastX;
	float lastY;
	bool firstMouse = true;
};


#endif