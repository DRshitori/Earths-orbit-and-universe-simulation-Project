#pragma once
#include "../utility/Renderer.h"
#include <vector>
#include <stdexcept>

struct VertexElementLayout
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4 ;
		case GL_UNSIGNED_INT: 
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexElementLayout> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		std::runtime_error(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexElementLayout::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexElementLayout::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE	,count,GL_FALSE });
		m_Stride += count * VertexElementLayout::GetSizeOfType(GL_UNSIGNED_BYTE);

	}

	inline unsigned int GetStride() const { return m_Stride; };
	inline const std::vector<VertexElementLayout> GetElements() const { return m_Elements; };
};

