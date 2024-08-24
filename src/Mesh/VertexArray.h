#pragma once
#include "../utility/Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_Renderer;
	unsigned int m_Index;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;

};

