#include "KeyBoard.h"
#include <algorithm>

std::vector <bool> KeyBoard::_Keys(1024, false);
bool KeyBoard::extra = false;
void KeyBoard::handleKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	glfwPollEvents();
	Window* mainWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			mainWindow->Close();
			break;

		case GLFW_KEY_F5:
			mainWindow->ToggleScreen();
			break;
		case GLFW_KEY_F1:
			mainWindow->CursoInputMode(GLFW_CURSOR_DISABLED);
			break;
		case GLFW_KEY_F2:
			mainWindow->CursoInputMode(GLFW_CURSOR_NORMAL);
			break;
		case GLFW_KEY_E:
			extra = !extra;
			break;
		default:
			_Keys.at(key) = true;
			break;
		}
		
	}
	else
	{
		_Keys.at(key) = false;
	}
}
