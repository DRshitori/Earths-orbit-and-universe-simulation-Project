#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <vector>

#pragma once
class MyGui
{
private:
	bool m_FullScreen;
	std::vector<float> m_lights;
	ImVec4 m_clear_color;
	///*ImGuiIO*/ m_io;

public:
	float m_mouseSensitivy;
	float m_speed;
	void Init(GLFWwindow *window,const char* glsl_version);
	void Update();
	void Render();
	void ShutDown();
	std::vector<float> GetLightVector(){ return m_lights; }
	ImVec4 GetClearColor() { return m_clear_color; }
	void setFullScreen(bool isFull);
	bool isFullScreen();
	MyGui();
	~MyGui();
};

