#pragma once

#include "Renderer/VertexBuffer.h"


class OpenGLVertexBuffer : public VertexBuffer
{

public:

	OpenGLVertexBuffer(const void* vertices, uint32_t size);
	OpenGLVertexBuffer(uint32_t size);
	virtual ~OpenGLVertexBuffer();

	virtual void Bind() const override;

	virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	virtual const BufferLayout& GetLayout() const override { return m_Layout; }

	virtual void SetData(const void* data, uint32_t size) override;

private:

	uint32_t m_RendererID;
	BufferLayout m_Layout;
};