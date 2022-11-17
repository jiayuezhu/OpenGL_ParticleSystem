#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, GLenum drawType)
{
    // vertex buffer
    glGenBuffers(1, &m_RendererID);
    // choose a buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // the one that is currently bound is going to be drawn
    // specify the buffer data
    glBufferData(GL_ARRAY_BUFFER, size, data, drawType);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
