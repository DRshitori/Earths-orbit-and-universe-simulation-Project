#pragma once
#include "../utility/Renderer.h"

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	IndexBuffer() = default;
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void Set(unsigned int* indices, unsigned int count) ;

	inline unsigned int GetCount() const { return m_Count; };
};

