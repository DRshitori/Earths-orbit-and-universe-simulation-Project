#include "Texture.h"


#include <iostream>
#include <stdexcept>

Texture::Texture(const std::string& filename) : m_filePath(filename), m_BPP(0), m_width(0), m_height(0), 
												m_data(nullptr), m_RendererID(0)
{
	if (!std::ifstream(filename.c_str()))
	{
		std::cout << "unable to read";
		std::string message = "FILE ERROR : the file you privided for the texture does not exist !" + filename;
		throw std::runtime_error(message.c_str());
	}

	stbi_set_flip_vertically_on_load(GL_TRUE);
	m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_BPP, 0);
	
	
	unsigned int internalFormat;
	unsigned int imageFormat;
	if (m_BPP == 1)
	{
			internalFormat = GL_RED;
			imageFormat = GL_RED;
	}
	else if (m_BPP == 3)
	{
		internalFormat = GL_RGB8;
		imageFormat = GL_RGB;
	}
	else if (m_BPP == 4)
	{
		internalFormat = GL_RGBA8;
		imageFormat = GL_RGBA;
	}

		


	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	glGenerateMipmap(GL_TEXTURE_2D);

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, imageFormat, GL_UNSIGNED_BYTE, m_data));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));


	if (m_data)
		stbi_image_free(m_data);

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}