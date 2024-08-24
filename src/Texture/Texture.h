#pragma once
#include <string>
#include <fstream>

#include <stb_image.h>
#include "../utility/Renderer.h"

class Texture
{
public: 
	Texture(const std::string& filename);
	~Texture();

	void Bind(unsigned int slot = 0 /*Texture Unit*/) const;
	void Unbind();

private:
	unsigned int m_RendererID;
	std::string m_filePath;
	unsigned char* m_data;
	int m_width, m_height;
	int m_BPP;

};

