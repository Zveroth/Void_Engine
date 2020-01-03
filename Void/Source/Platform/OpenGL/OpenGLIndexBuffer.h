#pragma once

#include "Renderer/indexBuffer.h"


class OpenGLIndexBuffer : public IndexBuffer
{

public:

	OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
	virtual ~OpenGLIndexBuffer();

	inline virtual uint32_t GetCount() const override { return m_Count; }

	virtual void Bind() const override;

private:

	uint32_t m_RendererID;
	uint32_t m_Count;
};