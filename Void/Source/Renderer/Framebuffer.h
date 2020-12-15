#pragma once
#include "Void/Core/Core.h"



struct FramebufferSpecification
{
	uint32_t Width;
	uint32_t Height;
	uint32_t Samples = 1;

	bool SwapChainTarget = false;
};

class Framebuffer
{

public:

	virtual ~Framebuffer() {}

	static Ref<Framebuffer> Create(const FramebufferSpecification& Spec);

	virtual const FramebufferSpecification& GetSpecification() const = 0;
	virtual uint32_t GetColorAttachmentID() = 0;

	virtual void Bind() = 0;
	virtual void Unbind() = 0;

	virtual bool Resize(uint32_t Width, uint32_t Height) = 0;
};