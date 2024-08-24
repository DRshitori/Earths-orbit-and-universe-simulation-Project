#include "Window.h"

Window::Window(unsigned int Width, unsigned int Height, const char* title) : m_FullScreen(false)
{
	m_width = Width;
	m_height = Height;
	m_title = std::string(title);
	m_IsRunning = true;

	init();
}

Window::~Window()
{
	if (!m_Window)
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "[GLFW: Intialiastion Failed!]";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);




	ASSERT((m_Window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr)) && "[GLFW: Window Creation Failed!]");
	glfwSetWindowPos(m_Window, (int)(glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 4), (int)(glfwGetVideoMode(glfwGetPrimaryMonitor())->height / 5));

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	glfwSetWindowUserPointer(m_Window, reinterpret_cast<Window*>(this));
	SetWindowCallBacks();
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	m_Gui.Init(m_Window,"#version 330");
	if (glewInit() != GLEW_OK)
	{
		std::cout << " GLEW : API Intialisation failed!";
		this->Close();
		glfwTerminate();
	}

	glewExperimental = GL_TRUE;
	glEnable(GL_DEPTH_TEST);

}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::ToggleScreen()
{
	m_FullScreen = !m_FullScreen;
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	
	if (m_Gui.isFullScreen())
	{
		glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->width, mode->refreshRate);

	}
	else
		glfwSetWindowMonitor(m_Window, nullptr, (int)(mode->width / 4), (int)(mode->height / 4), m_width, m_height, 0);

}

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, true);
}

void Window::SetWindowCallBacks()
{
	glfwSetFramebufferSizeCallback(m_Window, frameBuffer_size_callback);
	glfwSetKeyCallback(m_Window, KeyBoard::handleKeys);
	glfwSetCursorPosCallback(m_Window, Mouse::cursorPosCallBack);
	glfwSetScrollCallback(m_Window, Mouse::scrollCallBack);
}


void Window::frameBuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::CursoInputMode(GLenum value)
{
	glfwSetInputMode(m_Window, GLFW_CURSOR, value);
}

const GLFWwindow* Window::GetWindow() const
{
	return m_Window;
}

bool Window::IsRun()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::Clear()
{
	GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	m_Gui.Update();
}

void Window::ProcessInput()
{
	//glfwPollEvents();
	if (KeyBoard::_Keys[GLFW_KEY_F5])
		this->ToggleScreen();
	else if (KeyBoard::_Keys[GLFW_KEY_ESCAPE])
		this->Close();
}

void Window::render()
{
	m_Gui.Render();
	glfwSwapBuffers(m_Window);
}


void glEnable()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}