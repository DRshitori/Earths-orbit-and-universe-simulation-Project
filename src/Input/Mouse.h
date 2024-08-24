#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>

class Mouse
{
public:
	Mouse();
	static void	cursorPosCallBack(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);

	static double GetDX();
	static double GetDY();

	static float GetScrollDY();
	float SetSensitivty(float sen)
	{
		sensitivity = sen;
	};

private:
	static double xPos;
	static double yPos;

	static double lastX;
	static double lastY;
	static float sensitivity;
	 
	static double dx;
	static double dy;

	static float scrollDY;

	static bool firstMove;
};

