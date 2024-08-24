#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#include "Renderer.h"


class Shader {

public:
	Shader(const std::string& vertexfile, const std::string& fragfile,const std::string& geomFile);
	~Shader();
	int GetUniform(const std::string& uniName);
	void SetMaxtrix4xf(const std::string& uniName, const glm::mat4& mat4x, bool istranspose);
	void setInt(const std::string& uniName, int value);
	void SetFloat(const std::string& uniName, float value);
	void SetVec3(const std::string& uniName, glm::vec3 vec3);
	void Bind();
	void Unbind();
	void ParseShader(const std::string& filename);
	unsigned int CompileShader(const std::string& srcshader, unsigned int shadertype);
	unsigned int CreateShader(const std::string& vertexsrc, const std::string& fragementsrc,const std::string& GeometrySrc);

private:
	unsigned int m_Renderer;
	std::vector<std::string> m_ShaderSource;
	std::map<std::string,int> m_ShaderLocation;
};
