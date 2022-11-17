#include "IndexBuffer.h"
#include <GLCore.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    // vertex buffer
    glGenBuffers(1, &m_RendererID);
    // choose a buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // the one that is currently bound is going to be drawn
    // specify the buffer data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
