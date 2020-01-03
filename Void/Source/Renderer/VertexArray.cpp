#include "vdpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"


VertexArray* VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::API::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return new OpenGLVertexArray();
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating a vertex array!");
	return nullptr;
}