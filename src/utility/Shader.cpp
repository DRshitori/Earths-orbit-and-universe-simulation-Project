#include "Shader.h"
#include <algorithm>

Shader::Shader(const std::string& vertexFile,const std::string& fragFile, const std::string& geomFile) : m_Renderer(0)
{
	
	ParseShader(vertexFile);
	ParseShader(fragFile);
	ParseShader(geomFile);
	m_Renderer = CreateShader(m_ShaderSource[0], m_ShaderSource[1], m_ShaderSource[2]);
}



Shader::~Shader()
{

	GLCall(glDeleteProgram(m_Renderer));
}

int Shader::GetUniform(const std::string& uniName)
{
	if (m_ShaderLocation.find(uniName) != m_ShaderLocation.end())
		return m_ShaderLocation[uniName];


	GLCall(int location = glGetUniformLocation(m_Renderer, uniName.c_str()));
	ASSERT(location != -1);

	return m_ShaderLocation[std::string(uniName)] = location;
}

void Shader::SetMaxtrix4xf(const std::string& uniName, const glm::mat4& mat4x, bool isTranspose)
{
	GLCall(glUniformMatrix4fv(GetUniform(uniName), 1, isTranspose, glm::value_ptr(mat4x)));

}
void Shader::setInt(const std::string& uniName, int value)
{
	GLCall(glUniform1i(GetUniform(uniName),value));

}

void Shader::SetFloat(const std::string& uniName, float value)
{
	GLCall(glUniform1f(GetUniform(uniName), value));
}

void Shader::SetVec3(const std::string& uniName, glm::vec3 vec3)
{
	GLCall(glUniform3fv(GetUniform(uniName), 1, glm::value_ptr(vec3)));
}

void Shader::Bind()
{
	GLCall(glUseProgram(m_Renderer));
}

void Shader::Unbind()
{
	GLCall(glUseProgram(0));
}

void Shader::ParseShader(const std::string& filename)
{
	if (filename != "")
	{
		std::ifstream file(filename);
		if (!file)
		{
			std::runtime_error("[SHADER : UNABLE TO READ FROM FILE]");
		}

		m_ShaderSource.push_back("");
		int size = m_ShaderSource.size();
		std::string line{};
		while (std::getline(file, line))
		{
			m_ShaderSource[size - 1] += line + "\n";
		}

		if (m_ShaderSource.empty())
			std::runtime_error("[SHADER : GLSL IS EMPTY]");
	}
	else
	{
		m_ShaderSource.push_back("");
	}
}


unsigned int Shader::CompileShader(const std::string& srcShader, unsigned int shaderType)
{
	unsigned int shaderID = glCreateShader(shaderType);
	const char* src = srcShader.c_str();

	GLCall(glShaderSource(shaderID, 1, &src, nullptr));
	GLCall(glCompileShader(shaderID));

	int result{};
	GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length{};
		GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length));

		char* message = (char*)alloca(length);
		GLCall(glGetShaderInfoLog(shaderID, length, &length, message));

		std::cout << "OPENGL :" << (shaderType == GL_VERTEX_SHADER ? " Vertex" : " Fragment") << " shader compilation error.\nmessage : " << message << '\n';
		GLCall(glDeleteShader(shaderID));
		return 0;
	}

	return shaderID;
}

unsigned int Shader::CreateShader(const std::string& VertexSrc, const std::string& FragementSrc, const std::string& GeometrySrc)
{
	GLCall(unsigned int programID = glCreateProgram());
	unsigned int vs = CompileShader(VertexSrc, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(FragementSrc, GL_FRAGMENT_SHADER);
	unsigned int gs = 0;
	if (GeometrySrc != "")
	{
		gs = CompileShader(GeometrySrc, GL_GEOMETRY_SHADER);
	}

	GLCall(glAttachShader(programID, vs));
	GLCall(glAttachShader(programID, fs));
	if (gs != 0)
	{
		GLCall(glAttachShader(programID, gs));
	}
	GLCall(glLinkProgram(programID));

	int result{};
	GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &result));

	if (!result)
	{
		int length{};
		GLCall(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length);

		GLCall(glGetProgramInfoLog(programID, length, &length, message));
		std::cout << "OPENGL : Program Linking error!" << message << std::endl;
		GLCall(glDeleteProgram(programID));

		return 0;
	}

	GLCall(glValidateProgram(programID));
	GLCall(glGetProgramiv(programID, GL_VALIDATE_STATUS, &result));

	if (!result)
	{
		int length{};
		GLCall(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length);

		GLCall(glGetProgramInfoLog(programID, length, &length, message));

		std::cout << "OPENGL : Program Validating error!" << message << std::endl;
		GLCall(glDeleteProgram(programID));

		return 0;
	}

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
	if (gs != 0)
	{
		GLCall(glDeleteShader(gs));
	}

	return programID;
}
