#include "SkyBox.h"
#include <iostream>
#include <stb_image.h>

#include "../Input/KeyBoard.h"

SkyBox::SkyBox(std::vector<std::string>& faces): m_VAO()
{
	
	m_cubeFaces = faces;
}


void SkyBox::loadTextureFaces(std::vector<std::string> faces)
{
	if (m_cubeFaces.empty())
		m_cubeFaces = faces;
	return;
}

void SkyBox::loadCubeMap1()
{
	m_RendererID.push_back(0);
	GLCall(glGenTextures(1, &m_RendererID[0]));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID[0]));
	int width, height, BPP;

	for (int i = 0; i < m_cubeFaces.size() / 2; i++)
	{
		unsigned char* data = stbi_load(m_cubeFaces[i].c_str(), &width, &height, &BPP, 0);

		unsigned int internalFormat;
		unsigned int imageFormat;
		switch (BPP)
		{
			case 3:
			{
				internalFormat = GL_RGB8;
				imageFormat = GL_RGB;
			}
					break;
			case 4:
			{
				internalFormat = GL_RGBA8;
				imageFormat = GL_RGBA;
			}
				break;
		}

		if (data)
		{
			GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data));
			stbi_image_free(data);
		}
	

	}
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

		
}

void SkyBox::loadCubeMap2()
{
	m_RendererID.push_back(0);
	
	int width, height, BPP;

	GLCall(glGenTextures(1, &m_RendererID[1]));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID[1]));

	int count = 0;
	for (int i = 6; i < m_cubeFaces.size(); i++)
	{
		unsigned char* data = stbi_load(m_cubeFaces[i].c_str(), &width, &height, &BPP, 0);
		unsigned int internalFormat;
		unsigned int imageFormat;
		switch (BPP)
		{
		case 3:
		{
			internalFormat = GL_RGB8;
			imageFormat = GL_RGB;
		}
		break;
		case 4:
		{
			internalFormat = GL_RGBA8;
			imageFormat = GL_RGBA;
		}
		break;
		}

		if (data)
		{
			GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + count, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data));
			stbi_image_free(data);
			++count;
		}


	}
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		
}

void SkyBox::Bind(unsigned int slot, bool skyBoxExtra) const
{
	if (!skyBoxExtra)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 ));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID[0]));

	}
	else
	{
		GLCall(glActiveTexture(GL_TEXTURE0 ));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID[1]));
	}
}

void SkyBox::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

}

void SkyBox::Init()
{
	float skyboxVertices[] = {
		           
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	m_VAO.Bind();
	m_VBO.Set(skyboxVertices, sizeof(skyboxVertices));
	m_Layout.Push<float>(3);
	m_VAO.AddBuffer(m_VBO, m_Layout);
	m_VBO.Unbind();
	m_VAO.Unbind();

}

void SkyBox::Render(Shader &shader, Camera& cam)
{
	GLCall(glDepthFunc(GL_LEQUAL));
	shader.Bind();

	glm::mat4 view = glm::mat4(glm::mat3(cam.GetViewMatrix()) );
	glm::mat4 projection = cam.GetProjection();


	shader.SetMaxtrix4xf("view", view, false);
	shader.SetMaxtrix4xf("projection", cam.GetProjection(), false);

	m_VAO.Bind();
	this->Bind(0,KeyBoard::extra);
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	m_VAO.Unbind();
	GLCall(glDepthFunc(GL_LESS));

}



