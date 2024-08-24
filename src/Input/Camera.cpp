#include "Camera.h"
#include <iostream>
#include <chrono>

void Camera::SetDirection(Direction dir)
{

}
Camera::Camera(glm::vec3 positionStart, glm::vec3 target) :m_position(positionStart), m_target(target), m_yaw(-90.0f), m_pitch(0.0f), m_speed(4.5f)
{
	m_front = glm::normalize(positionStart - target);

	glm::vec3 Worldup = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::normalize(glm::cross(m_front, Worldup));

	m_up = glm::normalize(glm::cross(m_right, m_front));
	Update(0.f, nullptr);

}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_front + m_position, m_up);
}

glm::mat4 Camera::GetProjection() const
{
	return glm::perspective(glm::radians(Mouse::GetScrollDY()), (float)(800.f / 600.f), 0.1f, 100.f);

}


void Camera::Update(float dt, GLFWwindow* window)
{
	UpdateCameraOrientation(Mouse::GetDX(), Mouse::GetDY());
	UpdateCameraPos(dt, window);
}

void Camera::UpdateCameraOrientation(double _dx, double _dy)
{
	m_yaw += static_cast<float>(_dx);
	m_pitch += static_cast<float>(_dy);


	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	else if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	direction.y = glm::sin(glm::radians(m_pitch));
	direction.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));

	m_front = glm::normalize(direction);

	glm::vec3 Worldup = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::normalize(glm::cross(m_front, Worldup));

	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::UpdateCameraPos(float dt, GLFWwindow* window)
{
	if (!window)
		return;

	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_W))
		m_position += m_front * m_speed * dt;
	else if (glfwGetKey(window, GLFW_KEY_S))
		m_position -= m_front * m_speed * dt;
	else if (glfwGetKey(window, GLFW_KEY_D))
		m_position += m_right * m_speed * dt;
	else if (glfwGetKey(window, GLFW_KEY_A))
		m_position -= m_right * m_speed * dt;
}
