#pragma once
#include "../utility/Renderer.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, size_t size);
	VertexBuffer() = default;
	~VertexBuffer();

	void Set(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;
};

