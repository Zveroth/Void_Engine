#include "vdpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"



OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	VD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Provided vertex buffer has no layout!");

	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();

	unsigned int index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GetComponenetCount(), GL_FLOAT, element.bNormalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
		index++;
	}

	
	m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;
}