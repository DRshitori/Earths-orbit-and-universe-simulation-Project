#pragma once
#include <vector>
#include <string>

#include "../utility/Renderer.h"
#include <glm/glm.hpp>

#include "../utility/Shader.h"
#include "../Input/Camera.h"

#include "../Mesh/VertexArray.h"
#include "../Mesh/VertexBuffer.h"
#include "../Mesh/VertexBufferLayout.h"

class SkyBox
{
private:
	std::vector<std::string> m_cubeFaces;
	std::vector<unsigned int> m_RendererID;
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	VertexBufferLayout m_Layout;
public:
	SkyBox() = default;
	SkyBox(std::vector<std::string>& faces);
	void loadTextureFaces(std::vector<std::string> faces = {});
	void loadCubeMap1();
	void loadCubeMap2();

	void Bind(unsigned int slot = 0,bool skyBoxExtra = false) const;
	void Unbind() const;
	void Render(Shader &shader, Camera& cam);

	void Init();


};

