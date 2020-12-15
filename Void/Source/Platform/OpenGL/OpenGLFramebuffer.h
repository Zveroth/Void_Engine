#pragma once
#include "Renderer/Framebuffer.h"



class OpenGLFramebuffer : public Framebuffer
{

public:

	OpenGLFramebuffer(const FramebufferSpecification& Spec);
	virtual ~OpenGLFramebuffer();

	virtual const FramebufferSpecification& GetSpecification() const override { return m_Spec; }
	virtual uint32_t GetColorAttachmentID() override { return m_ColorAttachment; }

	void Create();

	virtual void Bind() override;
	virtual void Unbind() override;

	virtual bool Resize(uint32_t Width, uint32_t Height) override;

private:

	uint32_t m_RendererID = 0;
	uint32_t m_ColorAttachment = 0;
	uint32_t m_DepthAttachment = 0;
	FramebufferSpecification m_Spec;

	static const uint32_t s_MaxFramebufferSize = 8192;
};