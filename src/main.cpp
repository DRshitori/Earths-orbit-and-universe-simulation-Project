#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "./Mesh/VertexBuffer.h"
#include "./Mesh/IndexBuffer.h"
#include "./Mesh/VertexArray.h"
#include "./Input/Window.h"

#include "./Input/Camera.h"
#include "./utility/Shader.h"
#include "./utility/CubeSphere.h"
#include "./Texture/Texture.h"
#include "./Texture/SkyBox.h"
#include <objload.hpp>

extern unsigned int Width = 1100, Height = 800;

int main()
{

	using std::chrono::system_clock;

	Window mainWindow(Width, Height, "MY OpenGL Engine");
	{	
		std::vector<std::string> faces = { 
			"res/textures/Cubemap/space_right.png",
			"res/textures/Cubemap/space_left.png",
			"res/textures/Cubemap/space_bottom.png",
			"res/textures/Cubemap/space_up.png",
			"res/textures/Cubemap/space_back.png",
			"res/textures/Cubemap/space_front.png",

			"res/textures/Cubemap/bkg1_right.png",
			"res/textures/Cubemap/bkg1_left.png",
			"res/textures/Cubemap/bkg1_bot.png",
			"res/textures/Cubemap/bkg1_top.png",
			"res/textures/Cubemap/bkg1_front.png",
			"res/textures/Cubemap/bkg1_back.png",
			
		/*	"res/textures/Cubemap/corona_rt.png",
			"res/textures/Cubemap/corona_lf.png",
			"res/textures/Cubemap/corona_dn.png",
			"res/textures/Cubemap/corona_up.png",
			"res/textures/Cubemap/corona_bk.png",
			"res/textures/Cubemap/corona_ft.png",*/

		};

		SkyBox skybox(faces);

		
		CubeSphere earth(6);
		earth.createCubeSphere();
		earth.CreateMesh();
	
		skybox.Init();

		Texture textureEarth("res/textures/planets/earth.jpg");
		textureEarth.Bind(0);
		Texture textureEarthHeight("res/textures/planets/heightMap.png");
		textureEarth.Bind(1);
		Texture textureSpecularMap("res/textures/planets/specularMap.png");
		textureEarth.Bind(2);


		skybox.loadCubeMap1();
		skybox.loadCubeMap2();
		
		glm::vec3 lightPos = glm::vec3(0.3f, 0.1f, 2.0f);

		Shader shaderProgram("src/shader/shader.vert", "src/shader/shader.frag", "src/shader/shader.geom");
		Shader SkyBoxShader("src/shader/Skybox.vert", "src/shader/skybox.frag", "");

		Camera Camera(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f));


		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);


		float curAngle = 0.0f;

		system_clock::time_point currentTime{};
		system_clock::time_point lastFrameTime{};

		shaderProgram.Bind();
		shaderProgram.setInt("earth", 0);
		shaderProgram.setInt("earth_height", 1);
		shaderProgram.setInt("specularMap", 2);
		shaderProgram.SetVec3("lightPos", lightPos);

		shaderProgram.SetFloat("constant", .8f);
		shaderProgram.SetFloat("linear", 0.045f);
		shaderProgram.SetFloat("quadratic", 0.0075f);


		SkyBoxShader.Bind();
		SkyBoxShader.setInt("skybox", 0);

		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		while (!mainWindow.IsRun())
		{

			mainWindow.PollEvents();
			currentTime = system_clock::now();
			auto deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
			
			
			mainWindow.Clear();

			shaderProgram.Bind();
			Camera.Update(deltaTime,const_cast<GLFWwindow*>(mainWindow.GetWindow()));

			curAngle += 0.01f;
			if (curAngle >= 360.0f)
				curAngle = -360.0f;

			
		
			view = Camera.GetViewMatrix();
			projection = Camera.GetProjection();

			std::vector<float> lights = mainWindow.m_Gui.GetLightVector();
			ImVec4 vColor = mainWindow.m_Gui.GetClearColor();
			Camera.setSpeed(mainWindow.m_Gui.m_speed);
			glm::mat4 MVP = projection * view * model;
			shaderProgram.SetMaxtrix4xf("model", model, false);
			shaderProgram.SetMaxtrix4xf("view", view, false);
			shaderProgram.SetMaxtrix4xf("projection", projection, false);
			shaderProgram.SetFloat("ambientStrength", lights[0]);
			shaderProgram.SetFloat("diffuseStrength", lights[1]);
			shaderProgram.SetFloat("specularStrength", lights[2]);
			shaderProgram.SetVec3("vColor", glm::vec3(vColor.x, vColor.y, vColor.z));

			textureEarth.Bind(0);
			textureEarthHeight.Bind(1);
			textureSpecularMap.Bind(2);

			earth.render();

			model = glm::rotate(model, glm::radians(curAngle * deltaTime), glm::vec3(0.0f, 1.0f, 1.0f));
			skybox.Render(SkyBoxShader, Camera);

			mainWindow.render();
			lastFrameTime = currentTime;
		}

	}

	mainWindow.Close();
	glfwTerminate();
	return 0;
}




