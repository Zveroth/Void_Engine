#include "vdpch.h"
#include "Framebuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"


Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& Spec)
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::API::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return CreateRef<OpenGLFramebuffer>(Spec);
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating a framebuffer!");
	return nullptr;
}