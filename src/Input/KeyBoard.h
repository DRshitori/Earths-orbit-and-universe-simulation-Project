#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include <vector>
#include <map>

class KeyBoard
{
public:
	static void handleKeys(GLFWwindow* winodw, int key, int scancode, int action, int mods);
	static std::vector<bool> _Keys;
	static bool extra;
};

