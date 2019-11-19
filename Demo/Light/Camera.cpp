#include "Camera.h"

Camera::Camera()
{
	camera_font = glm::vec3(0.0,0,-1.0f);
	camera_position = glm::vec3(0, 0, 4.0f);
	camera_up = glm::vec3(0,1.0f,0);
}

void Camera::moveFont()
{
	camera_position += camera_font * mSpeed;
}

void Camera::moveBack()
{
	camera_position -= camera_font * mSpeed;
}

void Camera::moveleft()
{
	glm::vec3 left = glm::normalize(glm::cross(camera_font,camera_up));
	float x = left.x;
	float y = left.y;
	float z = left.z;
	camera_position -= left * mSpeed;
}

void Camera::moveRight()
{
	glm::vec3 right = glm::normalize(glm::cross(camera_font, camera_up));
	float x = right.x;
	float y = right.y;
	float z = right.z;
	camera_position += right * mSpeed;
}

void Camera::lookAt(float x, float y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y; // reversed since y-coordinates go from bottom to top
	lastX = x;
	lastY = y;

	float sensitivity = 0.01f; // change this value to your liking
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
	camera_font = glm::normalize(front);
}

void Camera::yawLeft()
{
}

void Camera::yawRight()
{
}

void Camera::pitchUp()
{
}

void Camera::pitchDown()
{
}

void Camera::rollClockWise()
{
}

void Camera::rollinClockWise()
{
}


glm::mat4 Camera::lookAt()
{
	return glm::lookAt(camera_position, camera_position + camera_font, camera_up);
}
