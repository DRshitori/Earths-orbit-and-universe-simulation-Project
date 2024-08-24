#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "../Input/KeyBoard.h"
#include "../Input/Mouse.h"

#include "../utility/Renderer.h"
#include "MyGui.h"

class Window
{
private:
	GLFWwindow* m_Window;

	unsigned int m_height;
	unsigned int m_width;
	std::string m_title;
	bool m_FullScreen;
	bool m_Closed;
	bool m_IsRunning;

	const GLFWvidmode* m_VideMode;

	bool init();
public:
	MyGui m_Gui;
	Window(unsigned int Width, unsigned int Height, const char* title);
	~Window();

	void PollEvents();
	void ToggleScreen();
	void SetWindowCallBacks();
	void Close();
	bool IsRun();
	void Clear();
	void ProcessInput();

	void render();

	static void handleKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void frameBuffer_size_callback(GLFWwindow* window, int width, int height);
	void CursoInputMode(GLenum value);

	const GLFWwindow* GetWindow() const;
};

