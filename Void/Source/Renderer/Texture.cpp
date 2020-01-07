#include "vdpch.h"
#include "Texture.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"



Ref<Texture2D> Texture2D::Create(const std::string& path)
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::API::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLTexture2D>(path);
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating a texture!");
	return nullptr;
}