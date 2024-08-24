#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_Renderer));
	GLCall(glBindVertexArray(m_Renderer));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_Renderer));
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	this->Bind();
	vbo.Bind();
	unsigned int Stride = layout.GetStride();
	
	const auto Elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0 ; i < Elements.size() ; i++)
	{
		const auto element = Elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, Stride, (const void*)offset));
		offset += element.count * VertexElementLayout::GetSizeOfType(element.type);;
	}

	vbo.Unbind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_Renderer));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}