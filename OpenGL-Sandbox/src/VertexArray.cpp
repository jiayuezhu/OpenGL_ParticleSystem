#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i=0; i<elements.size(); ++i)
	{
		const auto& ele = elements[i];
		// specify the vertex attribute pointer, the layout of data
		glEnableVertexAttribArray(i);
		unsigned int tmp = layout.GetStride();
		glVertexAttribPointer(i, ele.count, ele.type, ele.normalized, layout.GetStride(), (const void*)offset);
		offset += ele.count * VBLayoutElement::GetSizeOfType(ele.type);
	}
}
