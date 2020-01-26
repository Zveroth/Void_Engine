#include "vdpch.h"

#include "VertexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"


Ref<VertexBuffer> VertexBuffer::Create(const void* vertices, uint32_t size)
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::API::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating a vertex buffer!");
	return nullptr;
}