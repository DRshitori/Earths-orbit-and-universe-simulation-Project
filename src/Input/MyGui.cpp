#include "MyGui.h"
#include <iostream>

void MyGui::Init(GLFWwindow* window, const char* glsl_version)
{
    m_FullScreen = false;
    m_lights.resize(3);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& m_io = ImGui::GetIO(); (void)m_io;
    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void MyGui::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    ImGui::Begin("MENU FOR OPENGL SAPCE PROJECT /");
    ImGui::Text("TO NAVIGATE THROUGH THE SCENE");
    ImGui::Text("Z  : MOVE FORWARD");
    ImGui::Text("S  : MOVE BACKWARD");
    ImGui::Text("Q  : MOVE LEFT");
    ImGui::Text("D  : MOVE RIGHT");
    ImGui::Text("E  : CHANGE CUBEMAP");
    ImGui::Text("ESC: EXIT");
    ImGui::Text("F1 : HIDE CURSOR ");
    ImGui::Text("F2 : SHOW CURSOR");
    ImGui::Text("F5 : FULLSCREEN");
    ImGui::Text("");


    static bool full = false;
    if (ImGui::Checkbox("FullScreen", &full))
    {
        if (full)
            m_FullScreen = true;
        else
        {

            m_FullScreen = false;
        }

    }
    ImGui::Text("");
    static float Sensitivity = 0.01f;
    ImGui::SliderFloat("Mouse Sensitivity", &Sensitivity, 0.01f, 0.1f);
    m_mouseSensitivy = Sensitivity;

    static float Speed = 1.0f;
    ImGui::SliderFloat("Movement speed", &Speed, 1.0f, 8.0f);
    m_speed = Speed;

    ImGui::Text("");
    static float ambientStrength = 0.0f;
    ImGui::SliderFloat("ambient Light", &ambientStrength, 0.0f, 1.0f);
    m_lights[0] = ambientStrength;

    static float diffuseStrength = 0.0f;
    ImGui::SliderFloat("diffuse Light", &diffuseStrength, 0.0f, 1.0f);
    m_lights[1] = diffuseStrength;
    
    static float specularStrength = 0.0f;
    ImGui::SliderFloat("specular Light", &specularStrength, 0.0f, 1.0f);
    m_lights[2] = specularStrength; 


    static ImVec4 clear_color;
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
    m_clear_color = clear_color;
    
    ImGui::Text("\nApplication average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

}

void MyGui::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MyGui::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void MyGui::setFullScreen(bool isFull)
{
    m_FullScreen = { isFull };
}

bool MyGui::isFullScreen()
{
    //if (m_FullScreen)
    //    //std::cout << "full" << std::endl;
    //else
    //    //std::cout << "Nofull" << std::endl;

    return m_FullScreen;
}


MyGui::~MyGui()
{
    this->ShutDown();
}

MyGui::MyGui()
{

}