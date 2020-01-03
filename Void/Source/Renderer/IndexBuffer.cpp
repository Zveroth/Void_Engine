#include "vdpch.h"

#include "IndexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"


IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::OpenGL:
		return new OpenGLIndexBuffer(indices, count);
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating an index buffer!");
	return nullptr;
}