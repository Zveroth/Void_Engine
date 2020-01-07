#include "vdpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


Shader* Shader::Create(const std::string& FilePath)
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::API::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return new OpenGLShader(FilePath);
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating a shader!");
	return nullptr;
}

Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::API::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return new OpenGLShader(vertexSource, fragmentSource);
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating a shader!");
	return nullptr;
}