#pragma once
#include <GLCore.h>
class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size, GLenum drawType = GL_STATIC_DRAW);
	~VertexBuffer();

	void Bind() const;
	void UnBind()const;
};

