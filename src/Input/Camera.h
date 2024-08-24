#pragma once
#include <gl/glew.h>
#include <glfw/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Mouse.h"
#include "Window.h"

enum class Direction {
	NONE, RIGHT, LEFT, FORWARD, BACKWORD, UP, DOWN
};
class Camera
{

public:
	static void SetDirection(Direction dir);
	Camera(glm::vec3 positionStart, glm::vec3 target);
	void Update(float dt, GLFWwindow* window);
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjection() const;
	void setSpeed(float sp) { m_speed = sp; }

private:
	glm::vec3 m_position;

	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_up;

	glm::vec3 m_target;

	float m_speed;

	float m_yaw;
	float m_pitch;
	float m_fov;

	float speed;



	Direction m_direction;

private:
	void UpdateCameraOrientation(double _dx, double _dy);
	void UpdateCameraVectors();
	void UpdateCameraZoom();
	void UpdateCameraPos(float dt, GLFWwindow* window);
};

