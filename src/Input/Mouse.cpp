#include "Mouse.h"
#include <iostream>
#include "Camera.h"

bool Mouse::firstMove = true;

double Mouse::xPos = 0.0;
double Mouse::yPos = 0.0;

double Mouse::lastX = 0.0;
double Mouse::lastY = 0.0;

double Mouse::dx = 0.0;
double Mouse::dy = 0.0;

float Mouse::scrollDY = 45.f;

float Mouse::sensitivity = 0.05f;


void Mouse::cursorPosCallBack(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMove)
	{
		lastX = xpos;
		lastY = ypos;
		firstMove = false;
	}

	dx = xpos - lastX;
	dy = lastY - ypos;
	Window* mainWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

	float sen = mainWindow->m_Gui.m_mouseSensitivy;
	dx *= sen;
	dy *= sen;

	lastX = xpos;
	lastY = ypos;

}

void Mouse::mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
	

		}
	}
}

void Mouse::scrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollDY -= yoffset;

	if (scrollDY < 1.0f)
		scrollDY = 1.0f;
	else if (scrollDY > 45.0f)
		scrollDY = 45.0f;
}

double Mouse::GetDX()
{
	double _dx = dx;
	dx = 0.0;
	return _dx;
}

double Mouse::GetDY()
{
	double _dy = dy;
	dy = 0.0;
	return _dy;
}

float Mouse::GetScrollDY()
{
	return scrollDY;
}
